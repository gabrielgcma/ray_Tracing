#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    public:
        Point3 orig;
        Vec3 dir;
        
        Ray() {}
        Ray(const Point3& origem, const Vec3& direcao) : orig(origem), dir(direcao) {}

        Point3 origem() const { return orig; }
        Vec3 direcao() const { return dir; }
        Point3 at(double t) const { return orig + t*dir; }
};

#endif