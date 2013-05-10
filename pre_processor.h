#include "tree.h"
#include "splat_model.h"
#include <vector>

class pre_processor
{
    public:
        void process(splat_model);
        node build_tree(vector<splat>::iterator, vector<splat>::iterator , vertex, vertex);

};
