#include "splat.h"
#include <cstddef>

class node {
    public:
        splat s;
        node * left;
        node * right;
        float cone;

        node() : left(nullptr), right(nullptr), cone(0){
            }

        node(splat & _s) : s(_s), left(nullptr), right(nullptr), cone(0){
        }

        bool is_leaf() {
            return (left == nullptr) && (right == nullptr);
        }
};

