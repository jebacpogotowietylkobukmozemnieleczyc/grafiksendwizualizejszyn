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



 App *app;
static void DisplayFrameCallback(void) {
    app->DisplayFrame();
}
 static void NextFrameCallback(void) {
     app->NextFrame();
 }

 static void KeyDownCallback(int c, int x, int y) {
     app->KeyDown(c,x,y);
 }

static void KeyUpCallback(int c, int x, int y) {
    app->KeyUp(c,x,y);
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
    glutSpecialFunc(KeyDownCallback);
    glutSpecialUpFunc(KeyUpCallback);
	
	
    glEnable(GL_DEPTH_TEST);

    bullet.AddObject();
}


GLuint tex;

void App::DisplayFrame(void) {
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //world->stepSimulation(1);
	glm::mat4 M;
	glm::mat4 V=glm::lookAt(
        glm::vec3(0.0f,0.0f,-25.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f));
	
	glm::mat4 P=glm::perspective(50.0f, 1.0f, 1.0f, 50.0f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	
		
	M=glm::mat4(1.0f);
	M=glm::rotate(M,angle_y,glm::vec3(0.0f,1.0f,0.0f));
	M=glm::rotate(M,angle_x,glm::vec3(1.0f,0.0f,0.0f));
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
	angle_x+=speed_x*interval/1000.0;
	angle_y+=speed_y*interval/1000.0;
	if (angle_x>360) angle_x-=360;
	if (angle_x>360) angle_x+=360;
	if (angle_y>360) angle_y-=360;
	if (angle_y>360) angle_y+=360;
	
	glutPostRedisplay();
}

void App::KeyDown(int c, int x, int y) {
  switch (c) {
    case GLUT_KEY_LEFT: 
      speed_y=6;
      break;
    case GLUT_KEY_RIGHT:
      speed_y=-6;
      break;
    case GLUT_KEY_UP: 
      speed_x=6;
      break;
    case GLUT_KEY_DOWN:
      speed_x=-6;
      break;  
  }
}

void App::KeyUp(int c, int x, int y) {
  switch (c) {
    case GLUT_KEY_LEFT: 
      speed_y=0;
      break;
    case GLUT_KEY_RIGHT:
      speed_y=-0;
      break;
    case GLUT_KEY_UP: 
      speed_x=0;
      break;
    case GLUT_KEY_DOWN:
      speed_x=-0;
      break;  
  }
}
