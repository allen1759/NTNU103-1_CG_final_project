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
    CgluEye();
    CgluEye(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
    virtual ~CgluEye();

    void setEye(GLfloat s[]);
    void setEye(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
    void setNor(GLfloat n[]);
    void setNor(GLfloat, GLfloat, GLfloat);
    void LookAt();

protected:
private:
    GLfloat sEye[3] = {0.0, 0.0, 4.0};
    GLfloat sAt[3] = {0.0, 0.0, 0.0};
    GLfloat sNor[3] = {0.0, 1.0, 0.0};
};

#endif // CGLUEYE_H
