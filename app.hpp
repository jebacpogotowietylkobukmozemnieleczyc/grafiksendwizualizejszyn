#ifndef APP_HPP
#define APP_HPP

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h> //Przydatne do wypisywania komunikat�w na konsoli
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SOIL.h"

#include "bullet.hpp"
class App {
public:
  App(int* argc, char** argv);
  ~App();

  void DisplayFrame(void);
  void NextFrame(void);
  void KeySpecialDown(int c, int x, int y);
  void KeySpecialUp(int c, int x, int y);
  void KeyDown(unsigned char c, int x, int y);
  void KeyUp(unsigned char c, int x, int y);
  void MouseFunc(int button, int state, int x, int y);
  void MotionFunc(int x, int y);
  void ResetPointer();
  void CastShadow();
  void DrawShadow();
  int LoadTexture(int id, std::string filename);


private:
  float activatedpitch = 0;
  float activatedyaw = 0;
  int lastTime = 0;
  float yaw = 90;
  float pitch = 0;
  float mousesensivity = 60;
  float speed = 1;
  float moveforward = 0;
  float turn = 0;
  int mousex;
  int mousey;
  bool fullscreen = false;
  int height;
  int width;
  Bullet bullet;
  GLuint texture[2];
std::vector<GLfloat> shadow;
  glm::vec3 cameraposition = glm::vec3(0.0f, 0.0f, -25.0f);
  glm::vec3 cameratarget = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f);
};

extern App* app;
#endif // APP_HPP
