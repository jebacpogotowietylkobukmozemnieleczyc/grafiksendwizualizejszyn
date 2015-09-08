#include "app.hpp"
App* app;
static void DisplayFrameCallback(void) { app->DisplayFrame(); }
static void NextFrameCallback(void) { app->NextFrame(); }

static void KeyDownCallback(unsigned char c, int x, int y) {
  app->KeyDown(c, x, y);
}

static void KeyUpCallback(unsigned char c, int x, int y) {
  app->KeyUp(c, x, y);
}
static void KeySpecialDownCallback(int c, int x, int y) {
  app->KeySpecialDown(c, x, y);
}

static void KeySpecialUpCallback(int c, int x, int y) {
  app->KeySpecialUp(c, x, y);
}

static void MouseFuncCallback(int button, int state, int x, int y) {
  app->MouseFunc(button, state, x, y);
}
static void MotionFuncCallback(int x, int y) { app->MotionFunc(x, y); }
App::App(int* argc, char** argv) : width(800), height(800) {

  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Program OpenGL");
  glutDisplayFunc(DisplayFrameCallback);
  glutIdleFunc(NextFrameCallback);

  glewInit();
  glutKeyboardFunc(KeyDownCallback);
  glutKeyboardUpFunc(KeyUpCallback);
  glutSpecialFunc(KeySpecialDownCallback);
  glutSpecialUpFunc(KeySpecialUpCallback);
  glutMouseFunc(MouseFuncCallback);
  ResetPointer();
  glutSetCursor(GLUT_CURSOR_NONE);
  glutPassiveMotionFunc(MotionFuncCallback);

  GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

  glMaterialfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glMaterialfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_LIGHT0, GL_SPECULAR, specular);
  glMateriali(GL_FRONT, GL_SHININESS, 50);

  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);

  bullet.AddLevel();

  LoadTexture(0, "bricks.bmp");
  LoadTexture(1, "ntex.bmp");
}

void App::DisplayFrame(void) {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  bullet.getWorld()->stepSimulation(1);
  glm::mat4 M;
  glm::mat4 V = glm::lookAt(cameraposition, cameraposition + cameratarget,
                            glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 P = glm::perspective(50.0f, 1.0f, 1.0f, 500.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(P));
  glMatrixMode(GL_MODELVIEW);

  M = glm::mat4(1.0f);
  glLoadMatrixf(glm::value_ptr(V));
  float lightPos[] = { 0, -200, 0, 1 };
  GLfloat ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  GLfloat ambient2[] = { 0.0f, 0.0f, 0.1f, 1.0f };
  GLfloat diffuse2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
  GLfloat specular2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
  float lightPos2[] = { -20, -50, 0, 1 };
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);
  glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
  // static float staticx =0;
  //  M=glm::rotate(M,staticx+=0.01,glm::vec3(1.0f,0.0f,1.0f));
  glLoadMatrixf(glm::value_ptr(V * M));
  // bullet.getSolidSphere().draw(0,0,-10);
  bullet.getWorld()->debugDrawWorld();
  int texturenr = 0;
  for (auto it = bullet.getGameObject().begin();
       it != bullet.getGameObject().end(); ++it) {

    texturenr = texturenr == 1 ? 0 : 1;
    glBindTexture(GL_TEXTURE_2D, texture[texturenr]);
    btTransform trans;
    (*it)->GetTransform(trans);
    M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(trans.getOrigin().getX(),
                                    trans.getOrigin().getY(),
                                    trans.getOrigin().getZ()));
    btMatrix3x3 rotMatrix = trans.getBasis();
    float z, y, x;
    rotMatrix.getEulerZYX(z, y, x);
    M = glm::rotate(M, x, glm::vec3(1.0f, 0.0f, 0.0f));
    M = glm::rotate(M, y, glm::vec3(0.0f, 1.0f, 0.0f));
    M = glm::rotate(M, z, glm::vec3(0.0f, 0.0f, 1.0f));

    glLoadMatrixf(glm::value_ptr(V * M));

    (*it)->DrawShape();
  }

  glutSwapBuffers();
}

void App::NextFrame(void) {
  int actTime = glutGet(GLUT_ELAPSED_TIME);
  int interval = actTime - lastTime;
  lastTime = actTime;
  pitch += activatedpitch * interval / 1000.0;
  yaw += activatedyaw * interval / 1000.0;
  if (yaw > 360)
    yaw -= 360;
  if (yaw < 0)
    yaw += 360;
  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;
  cameratarget.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameratarget.y = sin(glm::radians(pitch));
  cameratarget.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  cameratarget = glm::normalize(cameratarget);

  cameraposition += moveforward * cameratarget;
  cameraposition += glm::normalize(glm::cross(cameratarget, cameraup)) * turn;

  glutPostRedisplay();
}
int App::LoadTexture(int nr, std::string filename) {
  texture[nr] = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO,
                                      SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  if (texture[nr] == 0)
    return false;
  glBindTexture(GL_TEXTURE_2D, texture[nr]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  return true;
}
void App::KeyDown(unsigned char c, int x, int y) {
  switch (c) {
    case 'w':
      moveforward = speed;
      break;
    case 's':
      moveforward = -speed;
      break;
    case 'a':
      turn = speed;
      break;
    case 'd':
      turn = -speed;
      break;
  }
}
void App::KeySpecialDown(int c, int x, int y) {
  switch (c) {
    case GLUT_KEY_LEFT:
      activatedyaw = mousesensivity;
      break;
    case GLUT_KEY_RIGHT:
      activatedyaw = -mousesensivity;
      break;
    case GLUT_KEY_UP:
      activatedpitch = -mousesensivity;
      break;
    case GLUT_KEY_DOWN:
      activatedpitch = mousesensivity;
      break;
  }
}

void App::KeyUp(unsigned char c, int x, int y) {
  switch (c) {
    case 'w':
      moveforward = 0;
      break;
    case 's':
      moveforward = 0;
      break;
    case 'a':
      turn = 0;
      break;
    case 'd':
      turn = -0;
      break;
    case 'k':
      bullet.AddObject(

          nullptr, 1, btVector3(0.2f, 0.6f, 0.6f),
          btVector3(cameraposition.x, cameraposition.y, cameraposition.z),
          btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), 50,
          btVector3(cameratarget.x, cameratarget.y, cameratarget.z));
      break;
    case 'l':
      bullet.AddObject(

          nullptr, 1, btVector3(0.2f, 0.6f, 0.6f),
          btVector3(cameraposition.x, cameraposition.y, cameraposition.z),
          btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), 200,
          btVector3(cameratarget.x, cameratarget.y, cameratarget.z));
      break;
    case 'f':
      if (fullscreen == false) {
        width = glutGet(GLUT_SCREEN_WIDTH);
        height = glutGet(GLUT_SCREEN_HEIGHT);
        glutPositionWindow(0, 0);
        glutReshapeWindow(width, height);
        glutFullScreen();
        fullscreen = true;
      } else {
        width = 800;
        height = 800;
        glutPositionWindow(0, 0);
        glutReshapeWindow(width, height);
        fullscreen = false;
      }
      break;
    case 'b':

      bullet.getDebugDrawer()->ToggleDebugFlag(btIDebugDraw::DBG_DrawWireframe);
      break;
    case 'n':

      bullet.getDebugDrawer()->ToggleDebugFlag(btIDebugDraw::DBG_DrawAabb);
      break;
    case 'm':

      bullet.getLevel().ToggleDebug();
      break;
  }
}
void App::KeySpecialUp(int c, int x, int y) {
  switch (c) {
    case GLUT_KEY_LEFT:
      activatedyaw = 0;
      break;
    case GLUT_KEY_RIGHT:
      activatedyaw = -0;
      break;
    case GLUT_KEY_UP:
      activatedpitch = 0;
      break;
    case GLUT_KEY_DOWN:
      activatedpitch = -0;
      break;
    case GLUT_KEY_F1:
      bullet.setShapetype(ShapeType::SPHERE);
      break;
    case GLUT_KEY_F2:
      bullet.setShapetype(ShapeType::CUBE);
      break;
    case GLUT_KEY_F3:
      bullet.setShapetype(ShapeType::CONE);
      break;
    case GLUT_KEY_F4:
      bullet.setShapetype(ShapeType::TEAPOT);
      break;
  }
}

void App::MouseFunc(int button, int state, int x, int y) {

  switch (button) {
    case GLUT_LEFT_BUTTON:

      if (state == GLUT_DOWN) {

        bullet.AddObject(

            nullptr, 1, btVector3(0.2f, 0.6f, 0.6f),
            btVector3(cameraposition.x, cameraposition.y, cameraposition.z),
            btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), 50,
            btVector3(cameratarget.x, cameratarget.y, cameratarget.z));
      }
      break;
    case GLUT_RIGHT_BUTTON:

      if (state == GLUT_DOWN) {

        bullet.AddObject(

            nullptr, 1, btVector3(0.2f, 0.6f, 0.6f),
            btVector3(cameraposition.x, cameraposition.y, cameraposition.z),
            btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), 200,
            btVector3(cameratarget.x, cameratarget.y, cameratarget.z));
      }
      break;
  }
}

void App::ResetPointer() {
  glutWarpPointer(width / 2, height / 2);
  mousex = width / 2;
  mousey = height / 2;
}

void App::MotionFunc(int x, int y) {

  yaw += (mousex - x) * mousesensivity * 0.0005;
  pitch += (y - mousey) * mousesensivity * 0.0005;
  if (fabs(width / 2 - x) > 25 || fabs(height / 2 - y) > 25) {
    ResetPointer();
  }
}

App::~App() {
  glDeleteTextures(1, &texture[0]);
  glDeleteTextures(1, &texture[2]);
}
