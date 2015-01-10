#include "CgluEye.h"
using namespace std;

CgluEye::CgluEye()
{
    //ctor
}

CgluEye::CgluEye(GLfloat s1, GLfloat s2, GLfloat s3, GLfloat a1, GLfloat a2, GLfloat a3)
{
    sEye[0] = s1; sEye[1] = s2; sEye[2] = s3;
    sAt[0]  = a1; sAt[1]  = a2; sAt[2]  = a3;
}

CgluEye::~CgluEye()
{
    //dtor
}

void CgluEye::setEye(GLfloat s[])
{
    for(int i=0; i<3; i+=1) sEye[i] = s[i];
    for(int i=0; i<3; i+=1) sAt[i]  = s[3+i];
}

void CgluEye::setEye(GLfloat s1, GLfloat s2, GLfloat s3, GLfloat a1, GLfloat a2, GLfloat a3)
{
    GLfloat tmp[] = { s1, s2, s3, a1, a2, a3 };
    setEye( tmp );
}
