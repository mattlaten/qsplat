#include "pre_processor.h"
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;

//--------------------------------------
// Sort Functions
//-------------------------------------

bool sortx(splat v, splat u) {return v.center.x < u.center.x;}
bool sorty(splat v, splat u) {return v.center.y < u.center.y;}
bool sortz(splat v, splat u) {return v.center.z < u.center.z;}

vertex partition(vector<splat>::iterator start, vector<splat>::iterator end, vertex BBmin, vertex BBmax)
{
    float xrange = BBmax.x - BBmin.x;
    float yrange = BBmax.y - BBmin.y;
    float zrange = BBmax.z - BBmin.z;
    if (xrange > yrange) {
        if (xrange > zrange) {
            //partition on x
            sort(start, end, sortx);
            vector<splat>::iterator midpoint = start;
            advance(midpoint, distance(start, end)/2);
            return vertex(midpoint->center.x, 0,0);
        } else {
            //partition on z
            sort(start, end, sortz);
            vector<splat>::iterator midpoint = start;
            advance(midpoint, distance(start, end)/2);
            return vertex(0,0,midpoint->center.z);
        }
    } else {
        if (yrange > zrange) {
            //partition on y
            sort(start, end, sorty);
            vector<splat>::iterator midpoint = start;
            advance(midpoint, distance(start, end)/2);
            return vertex(0,midpoint->center.y,0);
        } else {
            //partition on z
            sort(start, end, sortz);
            vector<splat>::iterator midpoint = start;
            advance(midpoint, distance(start, end)/2);
            return vertex(0,0,midpoint->center.z);
        }
    }
}

node * bounding_sphere(node * left, node * right) {
    node * n = new node;
    n->left = left;
    n->right = right;
    
    vertex m = (left->s.center+right->s.center)/2;
    float r = (left->s.center - right->s.center).mag()+left->s.size+right->s.size;

    splat s(m.x, m.y, m.z);
    s.size = r;
    s.normal = left->s.normal + right->s.normal;
    if (s.normal.mag() != 0)
        s.normal /= s.normal.mag();

    float left_cone = 0;    
    float right_cone = 0;    

    if (left->is_leaf()) {
        left_cone = abs(acos(s.normal.dot(left->s.normal)));
    } else {
        left_cone = abs(acos(left->cone));
    }
    if (right->is_leaf()) {
        right_cone = abs(acos(s.normal.dot(right->s.normal)));
    } else {
        right_cone = abs(acos(right->cone));
    }
    n->cone = cos(max(left_cone, right_cone));
    n->s = s;
    return n;
}


node * pre_processor::build_tree(vector<splat>::iterator start, vector<splat>::iterator end, vertex BBmin, vertex BBmax)
{
    int middle = distance(start, end)/2;
    if (start == end) {
        node * n = new node(*start);
        return n; 
    } else {
        vertex left_max = BBmax;
        vertex right_min = BBmin;
        vertex mid = partition(start, end, BBmin, BBmax);
        if (mid.x != 0) {
            left_max.x = mid.x;
            right_min.x = mid.x;
        }
        if (mid.y != 0) {
            left_max.y = mid.y;
            right_min.y = mid.y;
        }
        if (mid.z != 0) {
            left_max.z = mid.z;
            right_min.z = mid.z;
        }
        
        node * left = build_tree(start, start+middle, BBmin, left_max);
        node * right = build_tree(start+middle+1, end, right_min, BBmax);
        
        return bounding_sphere(left, right); 
    }
}
