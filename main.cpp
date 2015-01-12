#include <Windows.h>    // for solving the Code::Blocks errors
#define GLEW_STATIC

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <sstream>
#include "GlobalVariable.h"
#include "glm.h"
#include "textfile.h"
//#include "imageIO.c"
#include "myFunction.h"
using namespace std;


void drawOBJ();
void display(void);
void spinCube();
void mouse(int btn, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void myReshape(int w, int h);
void setShaders();
void setProjectionMatrix (int width, int height);
void keyboardSwitchCase(unsigned char key, int x, int y);
#define printOpenGLError() printOglError(__FILE__, __LINE__)
int printOglError(char *file, int line);
void printInfoLog(GLhandleARB obj);


int main(int argc, char **argv)
{
    srand( time(NULL) );
    glutInit(&argc, argv);

/* need both double buffering and z buffer */

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Final Project");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */

	glClearColor( 0.4f, 0.4f, 0.6f, 0.0f );
    glewInit();


    string name ("object/ben/ben_");
    for(int i=0; i<3; i+=1) {
//    for(int i=0; i<30; i+=1) {
        stringstream ss;
        ss << name;
        if(i<10) ss << "0";
        ss << i;
        ss << ".obj";
        cout << "open the file : "<< ss.str() << endl;
        char filename[128];
        strcpy(filename, ss.str().c_str());
        benObjs.push(testOBJ);
        benObjs[i].ReadOBJ(filename);
        benObjs[i].SetScale(1.2);
        benObjs[i].SetY(-0.3);
        benObjs[i].SetX(1.0);
    }
    currentBen = &benObjs[0];

    architecture.ReadOBJ("object/Street/Street_environment_V01.obj");
    architecture.Unitize();
    architecture.SetScale(10);
    architecture.SetY(0.72);

    taxi.ReadOBJ("object/car/Car_02_Obj.obj");
    taxi.Unitize();
    taxi.SetScale(0.8);
    taxi.SetThetaFront(-90.0);

    bridge.ReadOBJ("object/pontez/pontez.obj");
    bridge.Unitize();
    bridge.SetScale(10.0);

    sphere.ReadOBJ("object/sphere/sphere.obj");
    sphere.SetScale(50.0);

    ThirdPerson.setEye(0.0, 0.0, 2.0);
    currentPerson = &TaxiFirstPerson;

    setShaders();
    glutMainLoop();
    return 0;
}

void drawOBJ()
{
    sphere.DrawOBJ();
    architecture.DrawOBJ();
    if( ControlBen ) {
        currentBen->DrawOBJ();
    }
    else {
        glPushMatrix();
            glTranslated(-17.8, -0.3, 0.2);
            glRotated(180, 0, 1, 0);
            bridge.DrawOBJ();
        glPopMatrix();
        glPushMatrix();
            glTranslated(+17.8, -0.3, 0.2);
            glRotated(-180, 0, 1, 0);
            bridge.DrawOBJ();
        glPopMatrix();
        glPushMatrix();
            glTranslated(-1.0, -0.3, -17.3);
            glRotated(90, 0, 1, 0);
            bridge.DrawOBJ();
        glPopMatrix();
        glPushMatrix();
            glTranslated(-1.0, -0.3, +17.3);
            glRotated(-90, 0, 1, 0);
            bridge.DrawOBJ();
        glPopMatrix();
    }

    double updown = (rand()%100-50)/100.0 * 0.01;
    GLdouble originY = taxi.GetTransY();
    taxi.SetY( originY + updown );
    taxi.DrawOBJ();
    taxi.SetY( originY );

    //currentBen->DrawOBJ();
}

void display(void)
{
/* display callback, clear frame buffer and z buffer,
   rotate cube and draw, swap buffers */

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_dir);
    GLfloat spotLightTheta = 40.0;
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &spotLightTheta);

    TaxiFirstPerson.setEye( taxi.GetTransX()-0.10*cos(PI*taxi.GetThetaXZ()/180.0)
                          , taxi.GetTransY()+0.08
                          , taxi.GetTransZ()-0.10*sin(PI*taxi.GetThetaXZ()/180.0) );
    TaxiFirstPerson.setXZAng( taxi.GetThetaXZ() );


    currentPerson->updateLookAt();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    currentPerson->LookAt();
//glEnable(GL_COLOR_MATERIAL);

    drawOBJ();

  //glFlush();
  glutSwapBuffers();
}

void spinCube()
{
/* Idle callback, spin cube 2 degrees about selected axis */
    if (! moving) return;

	theta[axis] += 10;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	/* display(); */
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
/* mouse callback, selects an axis about which to rotate */

	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;

    if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		currentPerson->setISDrag(false);
		currentPerson->dragXY(x, y);
		currentPerson->setDrag(0.0, 0.0);
	}
	else if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	    currentPerson->setISDrag(true);
		currentPerson->setOldDrag(x, y);
	}
}

void motion(int x, int y)
{
	if(!ThirdPerson.isDrag()) return;
	currentPerson->setMotionDrag(x, y);
    currentPerson->updateLookAt();

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    keyboardSwitchCase(key, x, y);
    ThirdPerson.updateLookAt();

    glutPostRedisplay();
}

void myReshape(int windoww, int windowh)
{
    glViewport(0, 0, windoww, windowh);
    setProjectionMatrix(windoww, windowh);
//    if (w <= h)
//        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
//            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
//    else
//        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
//            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void setShaders()
{
	static int inited = 0;
	static GLhandleARB v,f,f2,p;
	char *vs = NULL,*fs = NULL;

	if (! inited) {
		v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
		f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
		f2 = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	}

	if (wave_mode == 1) {
    fs = textFileRead("shader/myshader.f");
    vs = textFileRead("shader/myshader.v");
//		vs = textFileRead("shader/newphong.vert");
//		fs = textFileRead("shader/newphong.frag");
//		vs = textFileRead("shader/newshader.vert");
//		fs = textFileRead("shader/newshader.frag");
	}
	else {
        vs = textFileRead("shader/toonf2.vert");
        fs = textFileRead("shader/toonf2.frag");
	}

	const char * vv = vs;
	const char * ff = fs;

	glShaderSourceARB(v, 1, &vv,NULL);
	glShaderSourceARB(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShaderARB(v);
	glCompileShaderARB(f);

	if (! inited) {
		p = glCreateProgramObjectARB();
	}
	// vertex shader processing
	glAttachObjectARB(p,v);

	glLinkProgramARB(p);
	printInfoLog(p);

    glUseProgramObjectARB(p);

	// fragement shader processing
	glAttachObjectARB(p,f);

	glLinkProgramARB(p);
	printInfoLog(p);

    glUseProgramObjectARB(p);

    glUniform1iARB(glGetUniformLocationARB(p, "texture"), 0);
    glUniform3fARB(glGetUniformLocationARB(p, "light"), light0_pos[0], light0_pos[1], light0_pos[2]);
    glUniform4fARB(glGetUniformLocationARB(p, "l_ambient"), 1.0, 1.0, 1.0, 1.0 );
    glUniform4fARB(glGetUniformLocationARB(p, "l_diffuse"), 1.0, 1.0, 1.0, 1.0 );
    glUniform4fARB(glGetUniformLocationARB(p, "l_specular"), 1.0, 1.0, 1.0, 1.0 );
}

int printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}

void printInfoLog(GLhandleARB obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB,
                                         &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetInfoLogARB(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

void setProjectionMatrix (int width, int height)
{
    static float rate;
    if(width+height!=0) rate = 1.0*width/height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (120.0*zoomFactor, rate, 0.01, 50);
                                   /* 'zNear' 'zFar' */
}

void keyboardSwitchCase(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 0x1B:      // ESC key ASCII code
        exit(0);
        break;

    case '0':
        ControlBen = !ControlBen;
        break;

    case '1':
        ThirdPerson.setEye( currentPerson->getEye(0),
                            currentPerson->getEye(1),
                            currentPerson->getEye(2) );
        ThirdPerson.setXZAng( currentPerson->getXZAng() );
        currentPerson = &ThirdPerson;
        break;
    case '3':
        currentPerson = &TaxiFirstPerson; break;

    case '6':
        currentObj = currentBen; break;
    case '7':
        currentObj = &taxi; break;

    case 'p': case 'P':
        currentBen = benObjs.getNext();
        break;
    case '[':
        currentPerson->speedUP(+0.01);
        break;
    case ']':
        currentPerson->speedUP(-0.01);
        break;

    case 'Y': case 'y':
        taxi.goFront();
        break;
    case 'H': case 'h':
        taxi.goBack();
        break;
    case 'T': case 't':
        taxi.goLeft();
        break;
    case 'U': case 'u':
        taxi.goRight();
        break;
    case 'G': case 'g':
        taxi.addThetaXZ( -30.0 );
        break;
    case 'J': case 'j':
        taxi.addThetaXZ( +30.0 );
        break;

    case '+':
        light_theta += 5;
        if(light_theta >= 360) light_theta -= 360;
        light0_pos[0] = 3.0 * cos(light_theta*PI/180);
        light0_pos[1] = 3.0 * sin(light_theta*PI/180);
        light0_dir[0] = light0_pos[0]*-1;
        light0_dir[1] = light0_pos[1]*-1;
        break;

    case '-':
        light_theta -= 5;
        if(light_theta < 0) light_theta += 360;
        light0_pos[0] = 3.0 * cos(light_theta*2*PI/180);
        light0_pos[1] = 3.0 * sin(light_theta*2*PI/180);
        light0_dir[0] = light0_pos[0]*-1;
        light0_dir[1] = light0_pos[1]*-1;
        break;

    case ' ':
        moving = !moving;
        break;

    case '`':
        wave_mode=!wave_mode;
        break;

    // 前進, 後退指令
    case 'W': case 'w':
        currentPerson->goFront();
        break;
    case 'S': case 's':
        currentPerson->goBack();
        break;
    // 左移, 右移指令
    case 'Q': case 'q':
        currentPerson->goLeft();
        break;
    case 'E': case 'e':
        currentPerson->goRight();
        break;
    // 上移, 下移指令
    case 'R': case 'r':
        currentPerson->goFloorUp();
        break;
    case 'F': case 'f':
        ThirdPerson.goFloorDown();
        break;

    // 旋轉指令
    case 'A': case 'a':
        ThirdPerson.addXZAng( -5.0 );
        break;

    case 'D': case 'd':
        ThirdPerson.addXZAng( +5.0);
        break;

    // Zoom 指令
    case 'n': case 'N':
        if(zoomFactor >= 1.9) break;
        zoomFactor += 0.05;
        setProjectionMatrix(0, 0);
        break;
    case 'm': case 'M':
        if(zoomFactor <=0.1) break;
        zoomFactor -= 0.05;
        setProjectionMatrix(0, 0);
        break;
    }
}



