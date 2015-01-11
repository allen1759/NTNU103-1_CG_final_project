#ifndef CGLUEYE_H
#define CGLUEYE_H

#include <Windows.h>    // for solving the Code::Blocks errors
#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

class CgluEye
{
public:
    static const double PI = 3.1415926;
    CgluEye();
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
    void setMotionDrag(int x, int y) { setDrag( (x - old_dragX)/dragSpeed, (y - old_dragY)/dragSpeed );}
    void setOldDrag(GLfloat x, GLfloat y) { old_dragX=x; old_dragY=y; }
    void setYAng(GLfloat ang) { yAng = ang; adjust(); }
    void addYAng(GLfloat ang) { yAng += ang; adjust(); }
    void setISDrag(bool bo) { drag_ = bo; }
    bool isDrag() { return drag_; }
    void speedUP( double x ) { walkSpeed += x; std::cout << "Current speed : " << walkSpeed << std::endl; }

    void goFront();
    void goBack();
    void goLeft();
    void goRight();
    void goFloorUp();
    void goFloorDown();
    void dragXY(int x, int y);
    void updateLookAt();
    void LookAt();

protected:
private:
    GLfloat sEye[3];
    GLfloat sAt[3];
    GLfloat sNor[3];
    GLfloat xzAng, yAng;
    double dragX, dragY, old_dragX, old_dragY;
    double walkSpeed, dragSpeed, lookDist;
    bool drag_;
    void adjust();
};

#endif // CGLUEYE_H
