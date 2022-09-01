#include "utilitarios.h"

#include "cor.h"
#include "objs_hitaveis.h"
#include "esfera.h"
#include "camera.h"
#include "hitavel.h"
#include "material.h"

#include <iostream>

using std::cout;
using std::cin;

// Calcular a cor de um pixel atingido por um raio
Cor ray_cor(const Ray& r, const Hitavel& mundo, int profundidade)
{
    Hit_registro reg;

    // Se ultrapassamos o limite de reflexões do ray, nenhuma luz a mais é coletada
    if(profundidade <= 0) return Cor(0, 0, 0);

    if(mundo.hit(r, 0.001, infinito, reg))
    {
        Ray disperso;
        Cor atenuacao;

        if (reg.mat_ptr->dispersar(r, reg, atenuacao, disperso))
            return atenuacao * ray_cor(disperso, mundo, profundidade-1);

        return Cor(0, 0, 0);
    }

    Vec3 unitario_direcao = unitario(r.direcao());
    auto t = 0.5*(unitario_direcao.y() + 1.0);
    return (1.0-t)*Cor(1.0, 1.0, 1.0) + t*Cor(0.5, 0.7, 1.0);
}   

int main()
{   
    // Parâmetros da imagem a ser renderizada --------------------------------------------
    const auto aspect_ratio = 16.0/9.0; 
    const int imgWidth = 800;
    const int imgHeight = static_cast<int>(imgWidth / aspect_ratio);
    const int samples_por_pixel = 100;
    const int max_profundidade = 50;

    // Mundo ------------------------------------------------------------------------------
    Objs_Hitaveis mundo;

    auto material_chao = make_shared<Lambertian>(Cor(0.2, 0.8, 0.1));
    auto material_centro = make_shared<Dieletrico>(Cor(0.1, 0.3, 0.8));
    auto material_esq = make_shared<Dieletrico>(Cor(0.8, 0.1, 0.2), 0.3);
    auto material_dir = make_shared<Metal>(Cor(0.2, 0.8, 0.6), 1.0);
    auto material_frente = make_shared<Metal>(Cor(0.5, 0.8, 0.8), 0.05);

    mundo.add(make_shared<Esfera>(Point3(0.0, -100.5, -1.0), 100.0, material_chao));
    mundo.add(make_shared<Esfera>(Point3(0.0, 0.0, -1.0), 0.5, material_centro));
    mundo.add(make_shared<Esfera>(Point3(-1.0, 0.0, -1.0), 0.25, material_esq));
    mundo.add(make_shared<Esfera>(Point3(1.0, 0.0, -1.0), 0.5, material_dir));
    mundo.add(make_shared<Esfera>(Point3(-0.5, -0.4, -0.7), 0.10, material_frente));

    // Câmera ----------------------------------------------------------------------------
    Camera cam;

    // Render ------------------------------------------------------------------------------
    cout<<"P3\n"<<imgWidth<<' '<<imgHeight<<"\n255\n";
    
    // i = linha, j = coluna
    for(int i = imgHeight-1; i>=0; --i)
    {
        std::cerr<<"\rScanlines restantes: "<<i<<' '<<std::flush;
        for(int j=0; j<imgWidth; ++j)
        {
            Cor cor_pixel(0, 0, 0);
            for(int s=0; s<samples_por_pixel; ++s)
            {
                auto u = (j+double_aleatorio()) / (imgWidth-1);
                auto v = (i+double_aleatorio()) / (imgHeight-1);

                Ray r = cam.get_ray(u, v);

                cor_pixel += ray_cor(r, mundo, max_profundidade);    
            }
            escrever_cor(cout, cor_pixel, samples_por_pixel);
        }
    }
    std::cerr<<"\nConcluído.\n";
}