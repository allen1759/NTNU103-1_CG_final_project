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
    GLdouble GetTransX() const { return position.transX; }
    GLdouble GetTransY() const { return position.transY; }
    GLdouble GetTransZ() const { return position.transZ; }
    GLdouble GetThetaXZ() const { return position.thetaXZ+position.thetaFront; }
    void SetX(GLdouble x) { position.transX = x; }
    void SetY(GLdouble y) { position.transY = y; }
    void SetZ(GLdouble z) { position.transZ = z; }
    void SetThetaXZ(GLdouble the) { position.thetaXZ = the; }
    void SetThetaFront(GLdouble the) { position.thetaFront = the; }
    void SetScale(GLdouble s) { position.scale = s; }

    void goFront();
    void goBack();
    void goLeft();
    void goRight();
    void addThetaXZ(double the);
    void adjustBound();

    static const double PI = 3.1415926535;
protected:
private:
    GLMmodel *myObj;
    CObjPosition position;
    double walkSpeed;
};

#endif // CMYOBJECT_H
