#include "utilitarios.h"

#include "cor.h"
#include "objs_hitaveis.h"
#include "esfera.h"

#include <iostream>

using std::cout;
using std::cin;

// Calcular a cor de um pixel atingido por um raio
Cor ray_cor(const Ray& r, const Hitavel& mundo)
{
    Hit_registro reg;
    if(mundo.hit(r, 0, infinito, reg))
    {
        return 0.5*(reg.normal + Cor(1,  1, 1));
    }

    Vec3 unitario_direcao = unitario(r.direcao());
    
    auto t = 0.5*(unitario_direcao.y() + 1.0);
    return (1.0-t)*Cor(1.0, 1.0, 1.0) + t*Cor(0.5, 0.7, 1.0);
}   

int main()
{   
    // Parâmetros da imagem a ser renderizada
    const auto aspect_ratio = 16.0/9.0; 
    const int imgWidth = 800;
    const int imgHeight = static_cast<int>(imgWidth / aspect_ratio);

    // Mundo 
    Objs_Hitaveis mundo;
    mundo.add(make_shared<Esfera>(Point3(0, 0, -1), 0.5));
    mundo.add(make_shared<Esfera>(Point3(0, -100.5, -1), 100));

    // Câmera
    auto viewport_height = 2.0;
    auto viewport_width  = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin-(horizontal/2)-(vertical/2)-(Vec3(0, 0, focal_length));

    // Render
    cout<<"P3\n"<<imgWidth<<' '<<imgHeight<<"\n255\n";
    
    // i = linha, j = coluna
    for(int i = imgHeight-1; i>=0; --i)
    {
        std::cerr<<"\rScanlines restantes: "<<i<<' '<<std::flush;
        for(int j=0; j<imgWidth; ++j)
        {
            auto u = double(j) / (imgWidth-1);
            auto v = double(i) / (imgHeight-1);
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            Cor cor_pixel = ray_cor(r, mundo);
            escrever_cor(cout, cor_pixel);
        }
    }

    std::cerr<<"\nConcluído.\n";
}