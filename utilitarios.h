#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;


// Constantes --------------------------------------------------------------------

const double infinito = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utilitários --------------------------------------------------------------------

inline double graus_p_radianos(double graus)
{
    return graus * pi / 180.0;
}

// Retorna um num real aleatório de [0, 1)
inline double double_aleatorio() { return rand() / (RAND_MAX + 1.0); }

// Retorna um num real aleatório de [min, max)
inline double double_aleatorio(double min, double max) { return min + (max-min)*double_aleatorio(); }

inline double clamp(double x, double min, double max) 
{
    if(x<min) return min;
    if(x>max) return max;
    return x;
}

// Headers comuns -----------------------------------------------------------------

#include "ray.h"
#include "vec3.h"

#endif