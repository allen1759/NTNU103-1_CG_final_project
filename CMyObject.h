#ifndef CMYOBJECT_H
#define CMYOBJECT_H

#include <Windows.h>    // for solving the Code::Blocks errors
#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include "glm.h"
#include "CObjPosition.h"

class CMyObject
{
public:
    CMyObject();
    CMyObject(char filename[]);
    virtual ~CMyObject();

    void ReadOBJ(char filename[]) { myObj = glmReadOBJ(filename); }
    void Unitize() { glmUnitize(myObj); }
    void DrawOBJ();
    void SetX(GLdouble x) { position.transX = x; }
    void SetY(GLdouble y) { position.transY = y; }
    void SetZ(GLdouble z) { position.transZ = z; }
    void SetScale(GLdouble s) { position.scale = s; }

protected:
private:
    GLMmodel *myObj;
    CObjPosition position;
};

#endif // CMYOBJECT_H
