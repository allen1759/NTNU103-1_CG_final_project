#ifndef CGLUEYE_H
#define CGLUEYE_H

#include <Windows.h>    // for solving the Code::Blocks errors
#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

class CgluEye
{
public:
    static const double PI = 3.1415926;
    CgluEye();
//    CgluEye(float, float, float, float, float, float);
    CgluEye(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
    virtual ~CgluEye();

    GLfloat & eye(int ind) { return sEye[ind]; }
    GLfloat & at(int ind) { return sAt[ind]; }
    GLfloat & nor(int ind) { return sNor[ind]; }

    void setEye(GLfloat s[]);
    void setEye(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
    void setNor(GLfloat n[]);
    void setNor(GLfloat, GLfloat, GLfloat);
    void updateLookAt(GLfloat xyAng, double dragX);
    void LookAt();

protected:
private:
    GLfloat sEye[3];
    GLfloat sAt[3];
    GLfloat sNor[3];
};

#endif // CGLUEYE_H
