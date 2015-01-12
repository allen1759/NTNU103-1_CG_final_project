#ifndef COBJGROUP_H
#define COBJGROUP_H

#include "CMyObject.h"
#include <vector>
#include <iostream>

class CObjGroup
{
public:
    CObjGroup();
    virtual ~CObjGroup();

    void setIndex(int x) { index = x; }
    void setFreq(int f) { countFreq = f; }
    void countUp() { currFreq += 1; }
    bool isChange()
    {
        if( currFreq < countFreq ) return false;
        currFreq = 0;
        return true;
    }
    CMyObject & operator[]( int i ) { return objs[i]; }
    const CMyObject & operator[]( int i ) const { return objs[i]; }
    CMyObject * getCurrent() { return &objs[index]; }
    CMyObject * getNext()
    {
        int nextIndex = (index+1)%objs.size();
        objs[nextIndex].SetPosition( objs[index].GetPosition() );
        index = nextIndex;
        return &objs[index];
    }
    void push(const CMyObject & o)
    {
        objs.push_back(o);
    }
    void resize(int n)
    {
        objs.resize(n);
    }

protected:
private:
    int countFreq;
    int currFreq;
    int index;
    std::vector<CMyObject> objs;
};

#endif // COBJGROUP_H
