#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constantes -----------

const double infinito = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utilitários ---------

inline double graus_p_radianos(double graus)
{
    return graus * pi / 180.0;
}

// Headers comuns ------

#include "ray.h"
#include "vec3.h"

#endif