#include <Windows.h>    // for solving the Code::Blocks errors
#define GLEW_STATIC

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <string>
#include <sstream>
#include "GlobalVariable.h"
#include "glm.h"
#include "textfile.h"
//#include "imageIO.c"
using namespace std;

GLMmodel *myObj = NULL;
GLMmodel * objarray[30];
int objind = 0;

void setShaders();


void setProjectionMatrix (int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (40.0*zoomFactor, (double)width/height, 1, 12);
                                                   /* 'zNear' 'zFar' */
}

void updateSeeAt(void)
{
	rad = (double) (PI*(sAngle+rotateX)/180.0);
    sAt[0] = (double)(sEye[0] + 10*cos(rad));
    sAt[2] = (double)(sEye[2] + 10*sin(rad));
    sAt[1] = sEye[1];
}

void drawOBJ()
{
    if (!myObj) return;
cout << myObj->pathname << endl;
    for (GLMgroup *groups = myObj->groups; groups != NULL; groups = groups->next) {
        int tmp = myObj->materials[groups->material].textureID;
        cout << "groups->name = " << groups->name << endl;
        cout << "id = " << tmp ;
        cout << "  material name = " << myObj->materials[groups->material].name << endl;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, myObj->materials[groups->material].textureID);
        for(unsigned i=0; i<groups->numtriangles; i+=1) {
            glBegin(GL_TRIANGLES);
                for (int j=0; j<3; j+=1)
                {
                    glNormal3fv(&myObj->normals[myObj->triangles[groups->triangles[i]].nindices[j]*3]);
                    glTexCoord2fv(&myObj->texcoords[myObj->triangles[groups->triangles[i]].tindices[j]*2]);
                    glVertex3fv(&myObj->vertices[myObj->triangles[groups->triangles[i]].vindices[j]*3]);
                }
            glEnd();
        }
    }
}

void display(void)
{
/* display callback, clear frame buffer and z buffer,
   rotate cube and draw, swap buffers */
//   updateSeeAt();
   ThirdPerson.updateLookAt();

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setProjectionMatrix(1, 1);
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


    ThirdPerson.LookAt();
//    gluLookAt(sEye[0], sEye[1], sEye[2],
//              sAt[0], sAt[1], sAt[2], 0.0, 1.0, 0.0);

glEnable(GL_COLOR_MATERIAL);
//    glTranslated(objPos[0], objPos[1], objPos[2]);
//    glRotated(theta[1], 0.0, 1.0, 0.0);

//    glTranslatef(lookAt[0][0], lookAt[0][1], lookAt[0][2]);
//    glRotatef(theta[1], 0.0, 1.0, 0.0);
//    glTranslatef(-lookAt[0][0], -lookAt[0][1], -lookAt[0][2]);

//	glRotatef(theta[0], 1.0, 0.0, 0.0);
//	glRotatef(theta[1], 0.0, 1.0, 0.0);
//	glRotatef(theta[2], 0.0, 0.0, 1.0);

//	glTranslated(-objPos[0], -objPos[1], -objPos[2]);


 drawOBJ();

//                setShaders();

 glFlush();
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
		drag = false;
		ThirdPerson.addXYAng( (x - old_rotateX)/10 );
//		sAngle += (x - old_rotateX)/10;
//		std::cout << "new x " << x << std::endl;
//		std::cout << "sangle change " << x-old_rotateX << std::endl << std::endl;

		rotateX = 0;   //沒有歸零會有 Error
		rotateY = 0;
		ThirdPerson.setDrag(0.0, 0.0);
	}
	else if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		drag = true;
		old_rotateX = x;
		old_rotateY = y;
//		std::cout << "old x " << old_rotateX << std::endl;
	}
}

void motion(int x, int y)
{
	if(!drag) return;
	ThirdPerson.setDrag( 1.0*(x - old_rotateX)/10, 1.0*(y - old_rotateY)/10 );
//	rotateX = (x - old_rotateX)/10;
//	rotateY = (y - old_rotateY)/10;
//	std::cout << "rotate x " << rotateX << std::endl;

//	rad = (double) (PI*sAngle/180.0);
//    sAt[0] = (double)(sEye[0] + 100*cos(rad));
//    sAt[2] = (double)(sEye[2] + 100*sin(rad));
//    sAt[1] = sEye[1];
    //ThirdPerson.addXYAng(rotateX);
    ThirdPerson.updateLookAt();

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 0x1B:      // ESC key ASCII code
        exit(0);
        break;

    case 'p':
    case 'P':
        objind += 1;
        objind %= 30;
        myObj = objarray[objind];
        glmUnitize(myObj);
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

    case 't':
    case 'T':
        wave_mode=!wave_mode;
        setShaders();
        break;

    // 前進, 後退指令
    case 'W':
    case 'w':
        rad = (double) (PI*sAngle/180.0);
        sEye[0] += (double) cos(rad)*speed;
        sEye[2] += (double) sin(rad)*speed;
        break;

    case 'S':
    case 's':
        rad = (double) (PI*sAngle/180.0);
        sEye[0] -= (double) cos(rad)*speed;
        sEye[2] -= (double) sin(rad)*speed;
        break;

    // 左移, 右移指令
    case 'Q':
    case 'q':
        rad = (double) (PI*sAngle/180.0);
        sEye[0] += (double) cos(90-rad)*speed;
        sEye[2] -= (double) sin(90-rad)*speed;
        break;

    case 'E':
    case 'e':
        rad = (double) (PI*sAngle/180.0);
        sEye[0] -= (double) cos(90-rad)*speed;
        sEye[2] += (double) sin(90-rad)*speed;
        break;

    // 旋轉指令
    case 'A':
    case 'a':
        ThirdPerson.addXYAng( -5.0 );
//        sAngle -= 5.0;
//        if(sAngle > 360.0) sAngle -= 360.0;
//        if(sAngle < -360.0) sAngle += 360.0;
        break;

    case 'D':
    case 'd':
        ThirdPerson.addXYAng( +5.0);
//        sAngle += 5.0;
//        if(sAngle > 360.0) sAngle -= 360.0;
//        if(sAngle < -360.0) sAngle += 360.0;
        break;

    // Zoom 指令
    case 'n':
    case 'N':
        if(zoomFactor >= 1.9) break;
        zoomFactor += 0.05;
        break;

    case 'm':
    case 'M':
        if(zoomFactor <=0.1) break;
        zoomFactor -= 0.05;
        break;
    }
    //updateSeeAt();
    ThirdPerson.updateLookAt();

    glutPostRedisplay();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)

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

void setShaders() {
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


int main(int argc, char **argv)
{
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

	glClearColor( 0.0f, 0.8f, 1.0f, 0.0f );
    glewInit();

//    glDisable(GL_TEXTURE_2D);
//    glmDraw(MODEL,GLM_SMOOTH|GLM_MATERIAL);
//    glEnable(GL_TEXTURE_2D);
//    glMaterialfv(GL_FRONT, GL_SPECULAR,fNoLight);

//    myObj = glmReadOBJ("sponza.obj");
//    myObj = glmReadOBJ("ben_00.obj");
//    myObj = glmReadOBJ("Car_02_Obj.obj");
//    myObj = glmReadOBJ("object/ben/ben_00.obj");
    string name ("object/ben/ben_");
    for(int i=0; i<1; i+=1) {
//    for(int i=0; i<30; i+=1) {
        stringstream ss;
        ss << name;
        if(i<10) ss << "0";
        ss << i;
        ss << ".obj";
        cout << "open the file : "<< ss.str() << endl;
        char filename[100];
        strcpy(filename, ss.str().c_str());
        objarray[i] = glmReadOBJ(filename);
    }
    myObj = objarray[0];
    ThirdPerson.setEye(0.0, 0.0, 4.0, 0.0, 0.0, 0.0);

    glmUnitize(myObj);

    setShaders();
    glutMainLoop();
    return 0;
}



