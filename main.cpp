#include "utilitarios.h"

#include "cor.h"
#include "objs_hitaveis.h"
#include "esfera.h"
#include "camera.h"
#include "hitavel.h"
#include "material.h"

#include <iostream>
#include <vector>
#include <chrono>

using std::cin;
using std::cout;
using std::vector;

/*

double media_rendertime(vector<double> tempo_entre_scanlines)
{
    double soma = 0;
    for(double tempo : tempo_entre_scanlines)
        soma += tempo;

    double media = soma / tempo_entre_scanlines.size();

    return media; 
}

void eta(double media_rendertime, int scanlines_restantes)
{
    double etaSegundos = media_rendertime * scanlines_restantes;
    
    int horas = etaSegundos / 3600;
    int minutos = etaSegundos / 60;

    cout << "Tempo estimado de conclusão: " << horas << ":" << minutos << "" << std::flush;
}

*/

// Calcular a cor de um pixel atingido por um raio
Cor ray_cor(const Ray &r, const Hitavel &mundo, int profundidade)
{
    Hit_registro reg;

    // Se ultrapassamos o limite de reflexões do ray, nenhuma luz a mais é coletada
    if (profundidade <= 0)
        return Cor(0, 0, 0);

    if (mundo.hit(r, 0.001, infinito, reg))
    {
        Ray disperso;
        Cor atenuacao;

        if (reg.mat_ptr->dispersar(r, reg, atenuacao, disperso))
            return atenuacao * ray_cor(disperso, mundo, profundidade - 1);

        return Cor(0, 0, 0);
    }

    Vec3 unitario_direcao = unitario(r.direcao());
    auto t = 0.5 * (unitario_direcao.y() + 1.0);
    return (1.0 - t) * Cor(1.0, 1.0, 1.0) + t * Cor(0.5, 0.7, 1.0);
}

Objs_Hitaveis cena_aleataoria()
{
    Objs_Hitaveis mundo;

    auto material_chao = make_shared<Lambertian>(Cor(0.1, 0.1, 0.1));
    mundo.add(make_shared<Esfera>(Point3(0, -1000, 0), 100, material_chao));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto escolher_material = double_aleatorio();
            Point3 centro(a + 0.9 * double_aleatorio(), 0.2, b + 0.9 * double_aleatorio());

            if ((centro - Point3(4, 0.2, 0)).comprimento() > 0.9)
            {
                shared_ptr<Material> material_esfera;

                if (escolher_material < 0.8)
                {
                    // Difuso
                    auto albedo = Cor::aleatorio() * Cor::aleatorio();
                    material_esfera = make_shared<Lambertian>(albedo);
                    mundo.add(make_shared<Esfera>(centro, 0.2, material_esfera));
                }
                else if (escolher_material < 0.95)
                {
                    // Metal
                    auto albedo = Cor::aleatorio(0.5, 1);
                    auto fuzz = double_aleatorio(0, 0.5);
                    material_esfera = make_shared<Metal>(albedo, fuzz);
                    mundo.add(make_shared<Esfera>(centro, 0.2, material_esfera));
                }
                else
                {
                    // Vidro
                    material_esfera = make_shared<Dieletrico>(1.5);
                    mundo.add(make_shared<Esfera>(centro, 0.2, material_esfera));
                }
            }
        }
    }

    auto material1 = make_shared<Dieletrico>(1.5);
    mundo.add(make_shared<Esfera>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Cor(0.4, 0.2, 0.1));
    mundo.add(make_shared<Esfera>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Cor(0.7, 0.6, 0.5), 0.0);
    mundo.add(make_shared<Esfera>(Point3(4, 1, 0), 1.0, material3));

    //auto material4 = make_shared<Metal>(Cor(0.2, 0.8, 0.75), 1.5);
    //mundo.add(make_shared<Esfera>(Point3(5, 1, 0), 1.5, material4));

    return mundo;
}

int main()
{
    // Parâmetros da imagem a ser renderizada --------------------------------------------
    const auto aspect_ratio = 16.0 / 9.0;
    const int imgWidth = 1200;
    const int imgHeight = static_cast<int>(imgWidth / aspect_ratio);
    const int samples_por_pixel = 500;
    const int max_profundidade = 50;

    // Mundo ------------------------------------------------------------------------------
    auto mundo = cena_aleataoria();

    // Câmera ----------------------------------------------------------------------------
    Point3 olharDe(13, 2, 3);
    Point3 olharEm(0, 0, 0);
    Vec3 viewUp(0, 1, 0);
    auto dist_focal = 10.0;
    auto abertura = 0.5;

    Camera cam(olharDe, olharEm, viewUp, 20, aspect_ratio, abertura, dist_focal);

    // Render ------------------------------------------------------------------------------
    cout << "P3\n"
         << imgWidth << ' ' << imgHeight << "\n255\n";

    // i = linha, j = coluna
    for (int i = imgHeight - 1; i >= 0; --i)
    {
        std::cerr << "\rScanlines restantes: " << i << ' ' << std::flush;

        for (int j = 0; j < imgWidth; ++j)
        {
            Cor cor_pixel(0, 0, 0);
            for (int s = 0; s < samples_por_pixel; ++s)
            {
                auto u = (j + double_aleatorio()) / (imgWidth - 1);
                auto v = (i + double_aleatorio()) / (imgHeight - 1);

                Ray r = cam.get_ray(u, v);

                cor_pixel += ray_cor(r, mundo, max_profundidade);
            }
            escrever_cor(cout, cor_pixel, samples_por_pixel);
        }
    }
    std::cerr << "\nConcluído.\n";
}