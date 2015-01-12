#include "CMyObject.h"
#include <iostream>
using namespace std;

CMyObject::CMyObject()
{
    myObj = NULL;
    walkSpeed = 0.8;
}

CMyObject::CMyObject(char filename[])
{
    myObj = glmReadOBJ(filename);
}

CMyObject::~CMyObject()
{
    if(myObj) glmDelete(myObj);
}

void CMyObject::DrawOBJ()
{
    if (!myObj) return;

    glPushMatrix();

    position.Transformation();

//cout << "----------------- " << myObj->pathname << endl;
    for (GLMgroup *groups = myObj->groups; groups != NULL; groups = groups->next) {
        int tmp = myObj->materials[groups->material].textureID;
//        cout << "groups->name = " << groups->name << endl;
//        cout << "id = " << tmp ;
//        cout << "  material name = " << myObj->materials[groups->material].name << endl;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, myObj->materials[groups->material].textureID);

        for(unsigned i=0; i<groups->numtriangles; i+=1) {
            glBegin(GL_TRIANGLES);
                for (int j=0; j<3; j+=1)
                {
                    glNormal3fv(&myObj->normals[myObj->triangles[groups->triangles[i]].nindices[j]*3]);
                    glTexCoord2fv(&myObj->texcoords[myObj->triangles[groups->triangles[i]].tindices[j]*2]);
                    glVertex3fv(&myObj->vertices[myObj->triangles[groups->triangles[i]].vindices[j]*3]);
                }
            glEnd();
        }
    }

    glPopMatrix();
}
void CMyObject::goFront()
{
    double rad = (double) (PI*(position.thetaXZ+position.thetaFront)/180.0);
    position.transX += (double) cos(rad)*walkSpeed;
    position.transZ += (double) sin(rad)*walkSpeed;
}
void CMyObject::goBack()
{
    double rad = (double) (PI*(position.thetaXZ+position.thetaFront)/180.0);
    position.transX -= (double) cos(rad)*walkSpeed;
    position.transZ -= (double) sin(rad)*walkSpeed;
}
void CMyObject::goLeft()
{
    double rad = (double) (PI*(position.thetaXZ+position.thetaFront-90.0)/180.0);
    position.transX += (double) cos(rad)*walkSpeed;
    position.transZ += (double) sin(rad)*walkSpeed;
}
void CMyObject::goRight()
{
    double rad = (double) (PI*(position.thetaXZ+position.thetaFront+90.0)/180.0);
    position.transX += (double) cos(rad)*walkSpeed;
    position.transZ += (double) sin(rad)*walkSpeed;
}
void CMyObject::addThetaXZ(double the)
{
    position.thetaXZ += the;
}
