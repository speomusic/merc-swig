#include "swigmod.h"

class MERC : public Language
{
public:
    virtual void main(int argc, char *argv[])
    {
        printf("I'm the Python module.\n");
    }

    virtual int top(Node *n)
    {
        printf("Generating code.\n");
        return SWIG_OK;
    }
};

extern "C" Language* swig_merc(void)
{
    return new MERC();
}
