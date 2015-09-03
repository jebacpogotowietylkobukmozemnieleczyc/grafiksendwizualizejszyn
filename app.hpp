#ifndef APP_HPP
#define APP_HPP

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h> //Przydatne do wypisywania komunikat�w na konsoli
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tga.h"

#include "bullet.hpp"

class App
{
public:
    App(int* argc,char** argv);


 void DisplayFrame(void) ;
 void NextFrame(void) ;
 void KeyDown(int c, int x, int y) ;
void KeyUp(int c, int x, int y) ;

private:
 float speed_x=0;
 float speed_y=0;
 int lastTime=0;
 float angle_x;
 float angle_y;
 Bullet  bullet;
};

extern App *app;
#endif // APP_HPP
