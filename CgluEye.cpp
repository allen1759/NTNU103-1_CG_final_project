#include "CgluEye.h"
#include <iostream>
#include <cmath>
using namespace std;

CgluEye::CgluEye()
{
    sNor[0] = 0.0; sNor[1] = 1.0; sNor[2] = 0.0;
    xzAng = -90.0;
    walkSpeed = 0.08;
    dragSpeed = 10.0;
    lookDist = 0.0001;
    drag_ = false;
}

CgluEye::CgluEye(GLfloat s1, GLfloat s2, GLfloat s3, GLfloat a1, GLfloat a2, GLfloat a3, GLfloat XZ)
{
    sEye[0] = s1; sEye[1] = s2; sEye[2] = s3;
    sAt[0]  = a1; sAt[1]  = a2; sAt[2]  = a3;
    sNor[0] = 0.0; sNor[1] = 1.0; sNor[2] = 0.0;
    xzAng = XZ;
    walkSpeed = 0.02;
    dragSpeed = 10.0;
    lookDist = 0.0001;
    drag_ = false;
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
    double radH = (double) (PI*yAng/180.0);
    sEye[0] += (double) cos(rad)*walkSpeed*cos(radH);
    sEye[2] += (double) sin(rad)*walkSpeed*cos(radH);
    sEye[1] += (double) sin(radH)*walkSpeed;
}
void CgluEye::goBack()
{
    double rad = (double) (PI*xzAng/180.0);
    double radH = (double) (PI*yAng/180.0);
    sEye[0] -= (double) cos(rad)*walkSpeed*cos(radH);
    sEye[2] -= (double) sin(rad)*walkSpeed*cos(radH);
    sEye[1] -= (double) sin(radH)*walkSpeed;
}
void CgluEye::goLeft()
{
    double rad = (double) (PI*(xzAng-90.0)/180.0);
    double radH = (double) (PI*yAng/180.0);
    sEye[0] += (double) cos(rad)*walkSpeed*cos(radH);
    sEye[2] += (double) sin(rad)*walkSpeed*cos(radH);
    //sEye[1] += (double) sin(radH)*walkSpeed;
}
void CgluEye::goRight()
{
    double rad = (double) (PI*(xzAng+90.0)/180.0);
    double radH = (double) (PI*yAng/180.0);
    sEye[0] += (double) cos(rad)*walkSpeed*cos(radH);
    sEye[2] += (double) sin(rad)*walkSpeed*cos(radH);
    //sEye[1] += (double) sin(radH)*walkSpeed;
}
void CgluEye::goFloorUp()
{
    sEye[1] += (double) walkSpeed;
}
void CgluEye::goFloorDown()
{
    sEye[1] -= (double) walkSpeed;
}
void CgluEye::dragXY(int x, int y)
{
    addXZAng( -(x - old_dragX)/dragSpeed );
    addYAng(  (y - old_dragY)/dragSpeed );
}

void CgluEye::updateLookAt()
{
	double rad = (double) (PI*(xzAng-dragX)/180.0);
	double radH = (double) (PI*(yAng+dragY)/180.0);
    sAt[0] = (double)(sEye[0] + lookDist*cos(rad)*cos(radH));
    sAt[2] = (double)(sEye[2] + lookDist*sin(rad)*cos(radH));
    sAt[1] = (double)(sEye[1] + lookDist*sin(radH));
    cout << "yAng = " << yAng << endl;
    cout << sEye[1] << endl;
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
    if(xzAng > 360.0) yAng -= 360.0;
    if(xzAng < -360.0) yAng += 360.0;
}
