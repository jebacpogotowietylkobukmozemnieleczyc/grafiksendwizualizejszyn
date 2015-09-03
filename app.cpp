#include "app.hpp"

int cubeVertexCount=24;

float cubeVertices[]={
    -1,-1,-1,
    -1, 1,-1,
     1, 1,-1,
     1,-1,-1,

    -1,-1, 1,
    -1, 1, 1,
     1, 1, 1,
     1,-1, 1,

    -1,-1,-1,
    -1,-1, 1,
     1,-1, 1,
     1,-1,-1,

    -1, 1,-1,
    -1, 1, 1,
     1, 1, 1,
     1, 1,-1,

    -1,-1,-1,
    -1,-1, 1,
    -1, 1, 1,
    -1, 1,-1,

     1,-1,-1,
     1,-1, 1,
     1, 1, 1,
     1, 1,-1
};


float cubeColors[]={
    1,0,0, 1,0,0, 1,0,0, 1,0,0,
    0,1,0, 0,1,0, 0,1,0, 0,1,0,
    0,0,1, 0,0,1, 0,0,1, 0,0,1,
    1,1,0, 1,1,0, 1,1,0, 1,1,0,
    0,1,1, 0,1,1, 0,1,1, 0,1,1,
    1,1,1, 1,1,1, 1,1,1, 1,1,1
};

auto rotx(glm::vec3 v, double a)
{
    return glm::vec3(v.x, v.y*cos(a) - v.z*sin(a), v.y*sin(a) + v.z*cos(a));
}

auto roty(glm::vec3 v, double a)
{
    return glm::vec3(v.x*cos(a) + v.z*sin(a), v.y, -v.x*sin(a) + v.z*cos(a));
}

auto rotz(glm::vec3 v, double a)
{
    return glm::vec3(v.x*cos(a) - v.y*sin(a), v.x*sin(a) + v.y*cos(a), v.z);
}

 App *app;
static void DisplayFrameCallback(void) {
    app->DisplayFrame();
}
 static void NextFrameCallback(void) {
     app->NextFrame();
 }

 static void KeyDownCallback(unsigned char c, int x, int y) {
     app->KeyDown(c,x,y);
 }

static void KeyUpCallback(unsigned char c, int x, int y) {
    app->KeyUp(c,x,y);
}
 static void KeySpecialDownCallback(int c, int x, int y) {
     app->KeySpecialDown(c,x,y);
 }

static void KeySpecialUpCallback(int c, int x, int y) {
    app->KeySpecialUp(c,x,y);
}

App::App(int* argc,char** argv)
{

    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Program OpenGL");
    glutDisplayFunc(DisplayFrameCallback);
    glutIdleFunc(NextFrameCallback);

	//Tutaj kod inicjujacy	
    glewInit();
    glutKeyboardFunc(KeyDownCallback);
    glutKeyboardUpFunc(KeyUpCallback);
    glutSpecialFunc(KeySpecialDownCallback);
    glutSpecialUpFunc(KeySpecialUpCallback);
	
	
    glEnable(GL_DEPTH_TEST);

    bullet.AddObject();
}


GLuint tex;

void App::DisplayFrame(void) {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //world->stepSimulation(1);
    glm::mat4 M;
    std::cout <<  "<--" << cameraposition.x << ' ' << ' ' << cameraposition.y << ' ' << cameraposition.z << std::endl;
    std::cout << cameraposition.x << ' ' << ' ' << cameraposition.y << ' ' << cameraposition.z << std::endl;
    glm::mat4 V=glm::lookAt(
                cameraposition,
                cameraposition + cameratarget,
		glm::vec3(0.0f,1.0f,0.0f));
	
	glm::mat4 P=glm::perspective(50.0f, 1.0f, 1.0f, 50.0f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	
		
	M=glm::mat4(1.0f);
    //M=glm::rotate(M,yaw,glm::vec3(0.0f,1.0f,0.0f));
    //M=glm::rotate(M,pitch,glm::vec3(1.0f,0.0f,0.0f));
	glLoadMatrixf(glm::value_ptr(V*M));

	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3,GL_FLOAT,0,cubeVertices);
	glColorPointer(3,GL_FLOAT,0,cubeColors);
		
	glDrawArrays(GL_QUADS,0,cubeVertexCount);
    glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

    bullet.getWorld()->debugDrawWorld();
	glutSwapBuffers();
}


void App::NextFrame(void) {
	int actTime=glutGet(GLUT_ELAPSED_TIME);
	int interval=actTime-lastTime;
	lastTime=actTime;
    pitch+=activatedpitch*interval/1000.0;
    yaw+=activatedyaw*interval/1000.0;
    if (yaw>360) yaw-=360;
    if (yaw<0) yaw+=360;
    if (pitch > 89.0f)
           pitch = 89.0f;
       if (pitch < -89.0f)
           pitch = -89.0f;
    cameratarget.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameratarget.y = sin(glm::radians(pitch));
    cameratarget.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameratarget = glm::normalize(cameratarget);


    cameraposition += moveforward * cameratarget;
    cameraposition +=glm::normalize(glm::cross(cameratarget, cameraup)) * turn;

    glutPostRedisplay();
}

void App::KeyDown(unsigned char c, int x, int y) {
  switch (c) {
    case 'w':
      moveforward=speed;
      break;
    case 's':
      moveforward=-speed;
      break;
    case 'a':
      turn=speed;
      break;
    case 'd':
      turn=-speed;
      break;
  }
}
void App::KeySpecialDown(int c, int x, int y) {
  switch (c) {
    case GLUT_KEY_LEFT: 
      activatedyaw=mousesensivity;
      break;
    case GLUT_KEY_RIGHT:
      activatedyaw=-mousesensivity;
      break;
    case GLUT_KEY_UP: 
      activatedpitch=-mousesensivity;
      break;
    case GLUT_KEY_DOWN:
      activatedpitch=mousesensivity;
      break;  
  }
}


void App::KeyUp(unsigned char c, int x, int y) {
  switch (c) {
    case 'w':
      moveforward=0;
      break;
    case 's':
      moveforward=0;
      break;
    case 'a':
      turn=0;
      break;
    case 'd':
      turn=-0;
      break;
  }
}
void App::KeySpecialUp(int c, int x, int y) {
  switch (c) {
    case GLUT_KEY_LEFT: 
      activatedyaw=0;
      break;
    case GLUT_KEY_RIGHT:
      activatedyaw=-0;
      break;
    case GLUT_KEY_UP: 
      activatedpitch=0;
      break;
    case GLUT_KEY_DOWN:
      activatedpitch=-0;
      break;  
  }
}