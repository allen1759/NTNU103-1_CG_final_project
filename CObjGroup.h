#ifndef COBJGROUP_H
#define COBJGROUP_H

#include "CMyObject.h"
#include <vector>

class CObjGroup
{
public:
    CObjGroup();
    virtual ~CObjGroup();

    void setIndex(int x) { index = x; }
    CMyObject * getCurrent() { return &objs[index]; }
    CMyObject * getNext()
    {
        index = (index+1)%objs.size();
        return &objs[index];
    }
    void push(CMyObject o)
    {
        objs.push_back(o);
    }

protected:
private:
    int index;
    std::vector<CMyObject> objs;
};

#endif // COBJGROUP_H
