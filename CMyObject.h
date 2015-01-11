#ifndef CMYOBJECT_H
#define CMYOBJECT_H

#include <Windows.h>    // for solving the Code::Blocks errors
#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include "glm.h"

class CMyObject
{
public:
    CMyObject();
    CMyObject(char filename[]);
    virtual ~CMyObject();

    void ReadOBJ(char filename[]) { myObj = glmReadOBJ(filename); }
    void Unitize() { glmUnitize(myObj); }
    void DrawOBJ();

protected:
private:
    GLMmodel *myObj;
};

#endif // CMYOBJECT_H
