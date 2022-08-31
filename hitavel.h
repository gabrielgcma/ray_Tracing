#ifndef HITAVEL_H
#define HITAVEL_H

#include "ray.h"
#include "utilitarios.h"

class Material;

struct Hit_registro
{
    Point3 p;
    Vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t;
    bool face_frontal;

    inline void setar_normal_face(const Ray& r, const Vec3& normal_para_fora)
    {
        face_frontal = escalar(r.direcao(), normal_para_fora) < 0;
        normal = face_frontal ? normal_para_fora : -normal_para_fora;
    }
};

class Hitavel
{
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, Hit_registro& reg) const = 0;
};

#endif