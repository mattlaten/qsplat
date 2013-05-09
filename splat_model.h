#include "splat.h"
#include <vector>
#include <limits>

class splat_model{
    public:
        std::vector<splat> splats;
        vertex max_val;
        vertex min_val;
};
