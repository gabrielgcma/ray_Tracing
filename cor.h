#ifndef COR_H
#define COR_H

#include "vec3.h"
#include <iostream>

void escrever_cor (std::ostream &saida, Cor cor_pixel)
{      
    // Escrever o valor traduzido [0, 255] de cada componente da cor
    saida << static_cast<int>(255.999 * cor_pixel.x()) << ' '
          << static_cast<int>(255.999 * cor_pixel.y()) << ' ' 
          << static_cast<int>(255.999 * cor_pixel.z()) << '\n';
}

#endif