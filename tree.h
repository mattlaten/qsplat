#include "splat.h"
#include <cstddef>

class node {
    public:
        splat s;
        node * left;
        node * right;
        bool leaf = false;

        node() : left(NULL), right(NULL){
            }

        node(splat & _s) : s(_s), left(NULL), right(NULL){
        }

        bool is_leaf() {
            return (left == NULL) && (right == NULL);
        }
};

