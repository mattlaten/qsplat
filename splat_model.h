#include "splat.h"
#include <vector>
#include <limits>

#ifndef _SPLAT_MODEL
#define _SPLAT_MODEL

class splat_model{
    public:
        std::vector<splat> splats;
        vertex max_val;
        vertex min_val;
};

#endif
