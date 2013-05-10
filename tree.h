#include "splat.h"

class node {
    public:
        splat s;
        node * left;
        node * right;

        node(splat & _s)
        {
            s = _s;   
        }
};

