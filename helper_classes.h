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

        const vertex operator+(const vertex& rhs) const {
            return vertex(*this) += rhs;
        }
        
        const vertex operator-(const vertex& rhs) const {
            return vertex(*this) -= rhs;
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
