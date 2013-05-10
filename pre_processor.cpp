#include "pre_processor.h"

void pre_processor::process(splat_model model)
{
}

//--------------------------------------
// Sort Functions
//-------------------------------------

bool sortx(vertex v, vertex u) {return v.x < u.x;}
bool sorty(vertex v, vertex u) {return v.y < u.y;}
bool sortz(vertex v, vertex u) {return v.z < u.z;}

node pre_processor::build_tree(vector<splat>::iterator start, vector<splat>::iterator end, vertex min, vertex max)
{
    if (start == end) {
        return node(*start);
    } else {
        float xrange = max.x - min.x;
        float yrange = max.y - min.y;
        float xrange = max.z - min.z;
        if (xrange > yrange) {
            if (xrange > zrange) {
                //partition on x
                sort(start, end, sortx)
            } else {
                //partition on z
                sort(start, end, sortz)
            }
        } else {
            if (yrange > zrange) {
                //partition on y
                sort(start, end, sorty)
            } else {
                //partition on z
                sort(start, end, sortz)
            }
        }

    }
}
