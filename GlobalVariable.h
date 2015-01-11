#ifndef GLOBALVARIABLE_H_INCLUDED
#define GLOBALVARIABLE_H_INCLUDED

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include "glm.h"
#include "CgluEye.h"
#include "CMyObject.h"
#include "CObjGroup.h"

static const double PI = (3.1415926535);

CMyObject testOBJ;

CMyObject * currentBen = NULL;

CMyObject architecture;
CObjGroup benObjs;
//std::vector<CMyObject> benObjs;

static GLMmodel *myObj = NULL;
static GLMmodel * objarray[30];
static int benIndex = 0;

static GLfloat diffuse0[]={1.0, 1.0, 1.0, 1.0};
static GLfloat ambient0[]={1.0, 1.0, 1.0, 1.0};
static GLfloat specular0[]={1.0, 1.0, 1.0, 1.0};
//GLfloat light0_pos[]={1.0, 2.0, 3,0, 1.0};
//GLfloat light0_pos[]={3.0, 0.0, 0.0, 1.0};
static GLfloat light0_pos[]={3.0, 1.0, 0.0, 0.5};
static GLfloat light0_dir[]={-3.0, 0.0, 0.0, -0.5};
static int light_theta = 0;

// for look at
CgluEye ThirdPerson;

static double zoomFactor = 0.5;
//double rad;

// for spin cube
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static int moving = 0;

// for drag function
static bool drag = false;
static double rotateX;			//拖曳後的相對座標，決定要旋轉幾度
static double rotateY;
static double old_rotateX;     //剛按下滑鼠時的視窗座標
static double old_rotateY;

// control texture mode
static int wave_mode = 1;

#endif // GLOBALVARIABLE_H_INCLUDED
