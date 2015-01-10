#ifndef GLOBALVARIABLE_H_INCLUDED
#define GLOBALVARIABLE_H_INCLUDED

#include <GL/glew.h>
#include <GL/glut.h>
#include "CgluEye.h"

const double PI = (3.1415926535);

GLfloat diffuse0[]={1.0, 1.0, 1.0, 1.0};
GLfloat ambient0[]={1.0, 1.0, 1.0, 1.0};
GLfloat specular0[]={1.0, 1.0, 1.0, 1.0};
//GLfloat light0_pos[]={1.0, 2.0, 3,0, 1.0};
//GLfloat light0_pos[]={3.0, 0.0, 0.0, 1.0};
GLfloat light0_pos[]={3.0, 1.0, 0.0, 0.5};
GLfloat light0_dir[]={-3.0, 0.0, 0.0, -0.5};
int light_theta = 0;

// for look at
//CgluEye ThirdPerson(0.0, 0.0, 4.0, 0.0, 0.0, 0.0);
CgluEye ThirdPerson;
//static GLfloat sEye[3] = {0.0, -2.0, 0.0};
static GLfloat sEye[3] = {0.0, 0.0, 4.0};
static GLfloat sAt[3] = {0.0, 0.0, 0.0};
static GLfloat sAngle = -90.0;
//static GLdouble objPos[3] = {0.0, 0.0, 0.0};
static double speed = 0.02;         //所有移動的速度 不含旋轉
static double zoomFactor = 1.0;
double rad;

// for spin cube
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static int moving = 0;

// for drag function
bool drag = false;
double rotateX;			//拖曳後的相對座標，決定要旋轉幾度
double rotateY;
double old_rotateX;     //剛按下滑鼠時的視窗座標
double old_rotateY;

// control texture mode
int wave_mode = 1;

#endif // GLOBALVARIABLE_H_INCLUDED
