#ifndef COBJPOSITION_H
#define COBJPOSITION_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>

class CObjPosition
{
public:
    CObjPosition();
    virtual ~CObjPosition();

    void Transformation()
    {
        glTranslated(transX, transY, transZ);
        glRotated(PI*thetaXZ/180.0, 0.0, 1.0, 0.0);
        glScaled(scale, scale, scale);

//    glTranslated(objPos[0], objPos[1], objPos[2]);
//    glRotated(theta[1], 0.0, 1.0, 0.0);

//    glTranslatef(lookAt[0][0], lookAt[0][1], lookAt[0][2]);
//    glRotatef(theta[1], 0.0, 1.0, 0.0);
//    glTranslatef(-lookAt[0][0], -lookAt[0][1], -lookAt[0][2]);

//	glRotatef(theta[0], 1.0, 0.0, 0.0);
//	glRotatef(theta[1], 0.0, 1.0, 0.0);
//	glRotatef(theta[2], 0.0, 0.0, 1.0);

//	glTranslated(-objPos[0], -objPos[1], -objPos[2]);
    }

    static const double PI = 3.1415926535;
    GLdouble transX, transY, transZ;
    GLdouble thetaXZ;
    GLdouble scale;

protected:
private:
};

#endif // COBJPOSITION_H
