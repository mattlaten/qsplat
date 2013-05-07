#include <math.h>

class vertex {
    public:
        float x, y, z;
       
        vertex() : x(0), y(0), z(0) {}

        vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

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

        vertex operator+(const vertex& rhs) {
            return vertex(*this) += rhs;
        }
        
        vertex operator-(const vertex& rhs) {
            return vertex(*this) -= rhs;
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
            return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
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
