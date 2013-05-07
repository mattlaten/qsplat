#include "helper_classes.h"

class splat {
    public:
        vertex center;
        float size;
        vertex normal;
    
        splat() {
        }

        splat(float x, float y, float z)
        {
            center = vertex(x,y,z);
        }
};
