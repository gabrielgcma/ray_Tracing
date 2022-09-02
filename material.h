#ifndef MATERIAL_H
#define MATERIAL_H

#include "utilitarios.h"
#include "hitavel.h"

class Material 
{
    public:
        virtual bool dispersar
        (
            const Ray& r_in, const Hit_registro& reg, Cor& atenuacao, Ray& disperso 
        ) const = 0;
};

class Lambertian : public Material 
{
    public:
        Cor albedo;

        Lambertian(const Cor& c) : albedo(c) {}

        virtual bool dispersar
        (
            const Ray& r_in, const Hit_registro& reg, Cor& atenuacao, Ray& disperso
        ) 
        const override 
        {
            auto direcao_dispersao = reg.normal + random_unitario();

            // Pegar direção do ray degenerado
            if(direcao_dispersao.quase_zero()) 
               direcao_dispersao = reg.normal;

            disperso = Ray(reg.p, direcao_dispersao);
            atenuacao = albedo;
            return true;
        }
};

class Metal : public Material 
{
    public:
        Cor albedo;
        double fuzz;

        Metal(const Cor& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool dispersar
        (
            const Ray& r_in, const Hit_registro& reg, Cor& atenuacao, Ray& disperso
        ) 
        const override 
        {
            Vec3 refletido = refletir(unitario(r_in.direcao()), reg.normal);
            disperso = Ray(reg.p, refletido + fuzz*random_esf_unitaria());
            atenuacao = albedo;
            return (escalar(disperso.direcao(), reg.normal) > 0);
        }
};

class Dieletrico : public Material
{
    public: 
        double ir; // índice de refração
        Dieletrico(double indice_refra) : ir(indice_refra) {}

        virtual bool dispersar
        (
            const Ray& r_in, const Hit_registro& reg, Cor& atenuacao, Ray& disperso
        ) 
        const override 
        {
            atenuacao = Cor(1.0, 1.0, 1.0);
            double proporcao_refra = reg.face_frontal ? (1.0/ir) : ir;
            
            Vec3 direcao_unitaria = unitario(r_in.direcao());
            double cos_theta = fmin(escalar(-direcao_unitaria, reg.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            // Não reflete se for true
            bool nao_reflete = proporcao_refra * sin_theta > 1.0;
            Vec3 direcao;

            if(nao_reflete)
                direcao = refletir(direcao_unitaria, reg.normal);
            else  
                direcao = refratar(direcao_unitaria, reg.normal, proporcao_refra);
            
            disperso = Ray(reg.p, direcao);

            return true;
        }
};  

#endif