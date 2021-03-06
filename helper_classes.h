#include <math.h>

#ifndef _HELPER
#define _HELPER

class vertex {
    public:
        float x, y, z;
       
        vertex() : x(0.0f), y(0.0f), z(0.0f) {}

        vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
        
        vertex(float val) : x(val), y(val), z(val) {}

        void set(float _x, float _y, float _z) {
            x = _x;
            y = _y;
            z = _z;
        }
        
        float fast_max(float a, float b)
        {
            if (a > b) return a;
            return b;
        }

        float fast_min(float a, float b)
        {
            return (a+b) - fast_max(a,b);
        }

        void min_set(float _x, float _y, float _z) {
            x = fast_min(x,_x);
            y = fast_min(y,_y);
            z = fast_min(z,_z);
        }
        
        void max_set(float _x, float _y, float _z) {
            x = fast_max(x,_x);
            y = fast_max(y,_y);
            z = fast_max(z,_z);
        }

        vertex& operator+=(const vertex& rhs) {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            return *this;
        }

        vertex& operator-=(const vertex& rhs) {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;
            return *this;
        }

        vertex& operator/=(const float scalar) {
            this->x/=scalar;
            this->y/=scalar;
            this->z/=scalar;
        }
        
        vertex& operator*=(const float scalar) {
            this->x*=scalar;
            this->y*=scalar;
            this->z*=scalar;
        }

        vertex operator+(const vertex& rhs) {
            return vertex(*this) += rhs;
        }
        
        vertex operator-(const vertex& rhs) {
            return vertex(*this) -= rhs;
        }

        vertex operator/(const float scalar) {
            return vertex(*this) /= scalar;
        }
        
        vertex operator*(const float scalar) {
            return vertex(*this) *= scalar;
        }

        float dot(const vertex& rhs) {
            return this->x*rhs.x + this->y*rhs.y + this->z*rhs.z; 
        }

        vertex cross(const vertex& rhs) {
           return vertex(
                            this->y*rhs.z - this->z*rhs.y,
                            this->z*rhs.x - this->x*rhs.z,
                            this->x*rhs.y - this->y*rhs.x
                        );
        }

        float mag(){
            return sqrt((this->x*this->x) + (this->y*this->y) + (this->z*this->z));
        }

};

class vector3 {
    public:
        vertex u, v;

        vector3() : u(vertex()), v(vertex()) {}

        vector3& operator+=(const vector3& rhs) {
            this->u += rhs.u;
            this->v += rhs.v;
            return *this;
        }

        

};

class triangle {
    public:
        vertex u, v, w;
};

#endif
