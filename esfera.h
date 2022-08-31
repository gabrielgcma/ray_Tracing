#ifndef ESFERA_H
#define ESFERA_H

#include "hitavel.h"
#include "vec3.h"

class Esfera : public Hitavel 
{
    public:
        Point3 centro;
        double raio;
        shared_ptr<Material> mat_ptr;

        Esfera() {}
        Esfera(Point3 centro, double r, shared_ptr<Material> m) : centro(centro), raio(r), mat_ptr(m) {};

        virtual bool hit(const Ray& r, double t_min, double t_max, Hit_registro& reg) const override;
};

bool Esfera::hit(const Ray& r, double t_min, double t_max, Hit_registro& reg) const 
{
    Vec3 oc = r.origem() - centro;
    auto a = r.direcao().comprimento_ao_quadrado();
    auto b_sobre_dois = escalar(oc, r.direcao());
    auto c = oc.comprimento_ao_quadrado() - raio*raio;

    auto delta = b_sobre_dois*b_sobre_dois - a*c;
    if(delta < 0) return false;
    auto sqrtDelta = sqrt(delta);

    // Encontrar a raiz mais próxima que está dentro do limite aceitável 
    auto raiz = (-b_sobre_dois - sqrtDelta) / a;
    if(raiz < t_min || t_max < raiz)
    {
        raiz = (-b_sobre_dois + sqrtDelta) / a;
        if(raiz < t_min || t_max < raiz)
        {
            return false;
        }
    }

    reg.t = raiz;
    reg.p = r.at(reg.t);
    Vec3 normal_para_fora = (reg.p - centro) / raio;
    reg.setar_normal_face(r, normal_para_fora);
    reg.mat_ptr = mat_ptr;

    return true;
}

#endif