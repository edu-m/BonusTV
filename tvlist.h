#include "list.h"
#include "node.h"
#include "TV.h"
#include <fstream>

class TVList : public List<TV>
{
    unsigned short diplaySize;

public:
    unsigned short getDisplaySize()
    {
        return this->diplaySize;
    }

    TVList(int ds) : diplaySize(ds) {}
    TVList() : diplaySize(0) {}
};