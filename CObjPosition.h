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
        glRotated(-thetaXZ, 0.0, 1.0, 0.0);
        glScaled(scale, scale, scale);
    }

    static const double PI = 3.1415926535;
    GLdouble transX, transY, transZ;
    GLdouble thetaXZ, thetaFront;
    GLdouble scale;

protected:
private:
};

#endif // COBJPOSITION_H
