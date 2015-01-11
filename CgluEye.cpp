#include "CgluEye.h"
#include <iostream>
#include <cmath>
using namespace std;

CgluEye::CgluEye()
{
    sNor[0] = 0.0; sNor[1] = 1.0; sNor[2] = 0.0;
    xzAng = -90.0;
    walkSpeed = 0.02;
}

CgluEye::CgluEye(GLfloat s1, GLfloat s2, GLfloat s3, GLfloat a1, GLfloat a2, GLfloat a3, GLfloat XZ)
{
    sEye[0] = s1; sEye[1] = s2; sEye[2] = s3;
    sAt[0]  = a1; sAt[1]  = a2; sAt[2]  = a3;
    sNor[0] = 0.0; sNor[1] = 1.0; sNor[2] = 0.0;
    xzAng = XZ;
    walkSpeed = 0.02;
    updateLookAt();
}

CgluEye::~CgluEye()
{
    //dtor
}

void CgluEye::setEye(GLfloat s[])
{
    for(int i=0; i<3; i+=1) sEye[i] = s[i];
    for(int i=0; i<3; i+=1) sAt[i]  = s[3+i];
    xzAng = s[6];
}
void CgluEye::setEye(GLfloat s1, GLfloat s2, GLfloat s3, GLfloat a1, GLfloat a2, GLfloat a3, GLfloat XZ)
{
    GLfloat tmp[] = { s1, s2, s3, a1, a2, a3, XZ };
    setEye( tmp );
}
void CgluEye::setNor(GLfloat n[])
{
    for(int i=0; i<3; i+=1) sNor[i] = n[i];
}
void CgluEye::setNor(GLfloat n1, GLfloat n2, GLfloat n3)
{
    GLfloat tmp[] = { n1, n2, n3 };
    setNor( tmp );
}

void CgluEye::goFront()
{
    double rad = (double) (PI*xzAng/180.0);
    sEye[0] += (double) cos(rad)*walkSpeed;
    sEye[2] += (double) sin(rad)*walkSpeed;
}
void CgluEye::goBack()
{
    double rad = (double) (PI*xzAng/180.0);
    sEye[0] -= (double) cos(rad)*walkSpeed;
    sEye[2] -= (double) sin(rad)*walkSpeed;
}
void CgluEye::goLeft()
{
    double rad = (double) (PI*(xzAng+90.0)/180.0);
//    sEye[0] += (double) sin(rad)*walkSpeed;
//    sEye[2] -= (double) cos(rad)*walkSpeed;
    sEye[0] += (double) cos(rad)*walkSpeed;
    sEye[2] += (double) sin(rad)*walkSpeed;
}
void CgluEye::goRight()
{
    double rad = (double) (PI*(xzAng-90.0)/180.0);
//    sEye[0] -= (double) cos(rad)*walkSpeed;
//    sEye[2] += (double) sin(rad)*walkSpeed;
    sEye[0] += (double) cos(rad)*walkSpeed;
    sEye[2] += (double) sin(rad)*walkSpeed;
}

void CgluEye::updateLookAt()
{
	double rad = (double) (PI*(xzAng+dragX)/180.0);
    sAt[0] = (double)(sEye[0] + 10*cos(rad));
    sAt[2] = (double)(sEye[2] + 10*sin(rad));
    sAt[1] = sEye[1];
    cout << "xzAng = " << xzAng << endl;
    cout << "drag =  " << dragX << endl;
    cout << "see eya = " << sEye[0] << " " << sEye[2] << "      ";
    cout << "see at  = " << sAt[0]  << " " << sAt[2]  << endl;
}

void CgluEye::LookAt()
{
    gluLookAt(sEye[0], sEye[1], sEye[2],
              sAt[0],  sAt[1],  sAt[2],
              sNor[0], sNor[1], sNor[2]);
}

void CgluEye::adjust()
{
    if(xzAng > 360.0) xzAng -= 360.0;
    if(xzAng < -360.0) xzAng += 360.0;
}
