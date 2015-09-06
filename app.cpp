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

GLuint tex;
App::App(int* argc, char** argv) {

  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Program OpenGL");
  glutDisplayFunc(DisplayFrameCallback);
  glutIdleFunc(NextFrameCallback);

  // Tutaj kod inicjujacy
  glewInit();
  glutKeyboardFunc(KeyDownCallback);
  glutKeyboardUpFunc(KeyUpCallback);
  glutSpecialFunc(KeySpecialDownCallback);
  glutSpecialUpFunc(KeySpecialUpCallback);

  glEnable(GL_DEPTH_TEST);

  std::cout << "<<start";
  for (auto it = bullet.level.getVec().begin();
       it != bullet.level.getVec().end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  // bullet.AddObject();
  bullet.AddLevel();

  std::cout << ">>start ";
  for (auto it = bullet.level.getVec().begin();
       it != bullet.level.getVec().end(); ++it) {
    std::cout << *(it) << " ";
  }
  std::cout << std::endl;
}

void App::DisplayFrame(void) {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  bullet.world->stepSimulation(1);
  glm::mat4 M;
  // std::cout <<  "<--" << cameraposition.x << ' ' << ' ' << cameraposition.y
  // << ' ' << cameraposition.z << std::endl;
  // std::cout << cameraposition.x << ' ' << ' ' << cameraposition.y << ' ' <<
  // cameraposition.z << std::endl;
  glm::mat4 V = glm::lookAt(cameraposition, cameraposition + cameratarget,
                            glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 P = glm::perspective(50.0f, 1.0f, 1.0f, 500.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(P));
  glMatrixMode(GL_MODELVIEW);

  M = glm::mat4(1.0f);
  glLoadMatrixf(glm::value_ptr(V * M));
  /*
          glEnableClientState(GL_VERTEX_ARRAY);
          glEnableClientState(GL_COLOR_ARRAY);

          glVertexPointer(3,GL_FLOAT,0,cubeVertices);
          glColorPointer(3,GL_FLOAT,0,cubeColors);

          glDrawArrays(GL_QUADS,0,cubeVertexCount);
      glDisableClientState(GL_VERTEX_ARRAY);
          glDisableClientState(GL_COLOR_ARRAY);
  */

  // bullet.gameobject->GetRigidBody()->getMotionState()->getWorldTransform(trans);
  bullet.getWorld()->debugDrawWorld();
  for (auto it = bullet.gameobject.begin(); it != bullet.gameobject.end();
       ++it) {

    btTransform trans;
    (*it)->GetTransform(trans);
    M = glm::mat4(1.0f);

/*
 //   btMatrix3x3 rmatrix= trans.getBasis();
    btMatrix3x3 rmatrix= btMatrix3x3(trans.getRotation());
   glm::mat4 R = glm::mat4(rmatrix.getRow(0).getX(),
                           rmatrix.getRow(0).getY(),
                           rmatrix.getRow(0).getZ(),
                           0,
                           rmatrix.getRow(1).getX(),
                           rmatrix.getRow(1).getY(),
                           rmatrix.getRow(1).getZ(),
                           0,
                           rmatrix.getRow(2).getX(),
                           rmatrix.getRow(2).getY(),
                           rmatrix.getRow(2).getZ(),
                           0,
                           0,0,0,1);
M=M*R;
M = glm::translate(M, glm::vec3(trans.getOrigin().getX(),
                                trans.getOrigin().getY(),
                                trans.getOrigin().getZ()));
    btScalar ryaw;
    btScalar rpitch;
    btScalar rroll;
    rmatrix.getEulerYPR(ryaw,rpitch,rroll);
*/
M = glm::translate(M, glm::vec3(trans.getOrigin().getX(),
                                trans.getOrigin().getY(),
                                trans.getOrigin().getZ()));
   btMatrix3x3 rotMatrix = trans.getBasis();
    float z,y,x;
            rotMatrix.getEulerZYX(z,y,x);
    M= glm::rotate(M,x,glm::vec3(1.0f,0.0f,0.0f));
    M= glm::rotate(M,y,glm::vec3(0.0f,1.0f,0.0f));
    M= glm::rotate(M,z,glm::vec3(0.0f,0.0f,1.0f));
   // M = glm::rotate(M, glm::vec3(trans.getBasis().getX(),
    //                                trans.getBasis().getY(),
     //                               trans.getBasis().getZ()));

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
