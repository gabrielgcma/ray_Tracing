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
            double vfov, // field of view vertical, em graus
            double aspect_ratio
        ) 
        {   
            auto theta = graus_p_radianos(vfov);
            auto h = tan(theta/2);
            auto viewport_altura = 2.0 * h;
            auto viewport_largura = aspect_ratio * viewport_altura;
            
            auto comp_focal = 1.0;

            origem = Point3(0, 0, 0);
            horizontal = Vec3(viewport_largura, 0, 0);
            vertical = Vec3(0, viewport_altura, 0);
            canto_inferior_esquerdo = origem - horizontal/2 - vertical/2 - Vec3(0, 0, comp_focal);
        }

        Ray get_ray(double u, double v) const 
        {
            return Ray(origem, canto_inferior_esquerdo + u*horizontal + v*vertical - origem);
        }
};

#endif