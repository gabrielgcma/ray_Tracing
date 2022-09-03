#ifndef COR_H
#define COR_H

#include "vec3.h"
#include <iostream>
#include <cmath>

// Usando Multi-sampling
void escrever_cor(std::ostream &saida, Cor cor_pixel, int samples_por_pixel)
{
    auto r = cor_pixel.x();
    auto b = cor_pixel.z();
    auto g = cor_pixel.y();

    auto scale = 1.0 / samples_por_pixel;
    // Dividir a cor pelo número de samples e fazer correção de gamma para gamma = 2.0:
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Escrever o valor traduzido [0, 255] de cada componente da cor
    saida << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
          << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
          << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif