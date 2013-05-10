#include "tree.h"
#include "splat_model.h"
#include <vector>

class pre_processor
{
    public:
        void process(splat_model & model);
        node * build_tree(std::vector<splat>::iterator start, std::vector<splat>::iterator end , vertex BBmin , vertex BBmax);

};
