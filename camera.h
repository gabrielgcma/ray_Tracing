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
        Vec3 u, v, w;
        double raio_lente;

    public: 
        Camera
        (
            Point3 olharDe,
            Point3 olharEm,
            Vec3 viewUp,
            double vfov, // field of view vertical, em graus
            double aspect_ratio,
            double abertura,
            double dist_focal
        ) 
        {   
            auto theta = graus_p_radianos(vfov);
            auto h = tan(theta/2);
            auto viewport_altura = 2.0 * h;
            auto viewport_largura = aspect_ratio * viewport_altura;

            w = unitario(olharDe - olharEm);
            u = unitario(prod_vetorial(viewUp, w));
            v = prod_vetorial(w, u);

            origem = olharDe;
            horizontal = dist_focal * viewport_largura * u;
            vertical = dist_focal * viewport_altura * v;
            canto_inferior_esquerdo = origem - horizontal/2 - vertical/2 - dist_focal*w;

            raio_lente = abertura/2;
        }

        Ray get_ray(double s, double t) const 
        {
            Vec3 rd = raio_lente*random_no_disco_unitario();
            Vec3 offset = u * rd.x() + v * rd.y();
            
            return Ray
            (
                origem + offset,
                canto_inferior_esquerdo + s*horizontal + t*vertical - origem - offset
            );
        }
};

#endif