#ifndef CAMERA_H
#define CAMERA_H

#include "utilitarios.h"

class Camera
{
    private: 
        Point3 origem;
        Point3 canto_inferior_esquerdo;
        Vec3 horizontal;
        Vec3 vertical;

    public: 
        Camera
        (
            Point3 olharDe,
            Point3 olharEm,
            Vec3 viewUp,
            double vfov, // field of view vertical, em graus
            double aspect_ratio
        ) 
        {   
            auto theta = graus_p_radianos(vfov);
            auto h = tan(theta/2);
            auto viewport_altura = 2.0 * h;
            auto viewport_largura = aspect_ratio * viewport_altura;

            auto w = unitario(olharDe - olharEm);
            auto u = unitario(prod_vetorial(viewUp, w));
            auto v = prod_vetorial(w, u);

            origem = olharDe;
            horizontal = viewport_largura * u;
            vertical = viewport_altura * v;
            canto_inferior_esquerdo = origem - horizontal/2 - vertical/2 - w;
        }

        Ray get_ray(double s, double t) const 
        {
            return Ray(origem, canto_inferior_esquerdo + s*horizontal + t*vertical - origem);
        }
};

#endif