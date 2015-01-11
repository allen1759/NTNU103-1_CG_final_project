#include "CMyObject.h"
#include <iostream>
using namespace std;

CMyObject::CMyObject()
{
    myObj = NULL;
}

CMyObject::CMyObject(char filename[])
{
    myObj = glmReadOBJ(filename);
}

CMyObject::~CMyObject()
{
    glmDelete(myObj);
}

void CMyObject::DrawOBJ()
{
    if (!myObj) return;
//cout << myObj->pathname << endl;
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
}
