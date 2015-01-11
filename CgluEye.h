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
    CgluEye(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat XZ=-90.0);
    virtual ~CgluEye();

    GLfloat & eye(int ind) { return sEye[ind]; }
    GLfloat & at(int ind) { return sAt[ind]; }
    GLfloat & nor(int ind) { return sNor[ind]; }

    void setEye(GLfloat s[]);
    void setEye(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat XZ=-90.0);
    void setNor(GLfloat n[]);
    void setNor(GLfloat, GLfloat, GLfloat);
    void setXZAng(GLfloat ang) { xzAng = ang; adjust(); }
    void addXZAng(GLfloat ang) { xzAng += ang; adjust(); }
    void setDrag(GLfloat x, GLfloat y) { dragX=x; dragY=y; }
    void setYAng(GLfloat ang) { yAng = ang; adjust(); }
    void addYAng(GLfloat ang) { yAng += ang; adjust(); }
    void goFront();
    void goBack();
    void goLeft();
    void goRight();
    void updateLookAt();
    void LookAt();

protected:
private:
    GLfloat sEye[3];
    GLfloat sAt[3];
    GLfloat sNor[3];
    GLfloat xzAng, yAng;
    double dragX, dragY;
    double walkSpeed, lookDist;
    void adjust();
};

#endif // CGLUEYE_H
