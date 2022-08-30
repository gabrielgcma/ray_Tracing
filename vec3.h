#ifndef VEC3_H // ifndef = if not defined
#define VEC3_H // then define

#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3
{
    public:
        double coords[3];
        // Construtor de um vetor nulo
        Vec3() : coords{0,0,0} {} 
        // Construtor usando parâmetros
        Vec3(double coord0, double coord1, double coord2) : coords{coord0, coord1, coord2} {}

        double x() const { return coords[0]; }
        double y() const { return coords[1]; }
        double z() const { return coords[2]; }

        // Invertendo um vetor:
        Vec3 operator-() const 
        {
            return Vec3(-coords[0], -coords[1], -coords[2]);
        }

        // Pegando a coordenada i de um vetor
        double operator[](int i) const
        {
            return coords[i];
        }
        
        // Pegando a coordenada i de um vetor usando uma reference
        double& operator[](int i)
        {
            return coords[i];
        }

        // Adicionando uma constante às coords de um vetor
        Vec3& operator+=(const Vec3 &v)
        {
            coords[0] += v.coords[0];
            coords[1] += v.coords[1];
            coords[2] += v.coords[2];
            return *this;
        } 

        // Multiplicando um vetor por uma constante: t(x, y, z)
        Vec3& operator*=(const double t)
        {
            coords[0] *= t;
            coords[1] *= t;
            coords[2] *= t;
            return *this;
        }

        // Dividindo um vetor por uma constante: 1/t(x, y, z)
        Vec3& operator/=(const double t)
        {
            // Já usa o operador sobrecarregado '*=' 
            return *this *= 1/t;
        }

        double comprimento_ao_quadrado() const
        {
            return coords[0]*coords[0] + coords[1]*coords[1] + coords[2]*coords[2];
        }

        // Comprimendo do vetor:
        double comprimento() const
        {
            return sqrt(comprimento_ao_quadrado());
        }
        
        inline static Vec3 aleatorio()
        {
            return Vec3(double_aleatorio(), double_aleatorio(), double_aleatorio());
        }

        inline static Vec3 aleatorio(double min, double max)
        {
            return Vec3(double_aleatorio(min, max), 
                        double_aleatorio(min, max), 
                        double_aleatorio(min, max));
        }
};

// ---------------------------------------------
// Vec3 utilitários - Sobrecarregando operadores
// ---------------------------------------------

// Sobrecarregando o operador << para mostrar coordenadas de vetores como '0 0 2' 
inline std::ostream& operator<<(std::ostream &saida, const Vec3 &v)
{
    return saida << v.coords[0] << ' ' << v.coords[1] << ' ' << v.coords[2];
}

// Novo vetor a partir de soma de vetores
inline Vec3 operator+(const Vec3 &u, const Vec3 &v) 
{   
    return Vec3(u.coords[0]+v.coords[0], u.coords[1]+v.coords[1], u.coords[2]+v.coords[2]);
}

// Novo vetor a partir de subtração de vetores
inline Vec3 operator-(const Vec3 &u, const Vec3 &v) 
{   
    return Vec3(u.coords[0]-v.coords[0], u.coords[1]-v.coords[1], u.coords[2]-v.coords[2]);
}

// Novo vetor a partir da multiplicação de vetores
inline Vec3 operator*(const Vec3 &u, const Vec3 &v) 
{
    return Vec3(u.coords[0]*v.coords[0], u.coords[1]*v.coords[1], u.coords[2]*v.coords[2]);
}

// Novo vetor a partir da multiplicação de escalar por vetor
inline Vec3 operator*(double t, const Vec3 &u)
{
    return Vec3(t*u.coords[0], t*u.coords[1], t*u.coords[2]);
}

inline Vec3 operator*(const Vec3 &u, double t)
{
    return t*u;
}

// Novo vetor a partir da divisão de um escalar por vetor
inline Vec3 operator/(Vec3 u, double t)
{
    return (1/t)*u;
}

// Produto escalar
inline double escalar(const Vec3 &u, const Vec3 &v)
{
    return u.coords[0] * v.coords[0]
        + u.coords[1] * v.coords[1]
        + u.coords[2] * v.coords[2];
}

// Produto vetorial:
inline Vec3 prod_vetorial(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.coords[1]*v.coords[2] - u.coords[2]*v.coords[1],
                u.coords[2]*v.coords[0] - u.coords[0]*v.coords[2],
                u.coords[0]*v.coords[1] - u.coords[1]*v.coords[0]);
}

inline Vec3 unitario(Vec3 v)
{
    return v / v.comprimento();
}

// Pegar um ponto aleatório dentro de uma esfera unitária tangente à superfície do sólido 
// para ser a direção aleatória do raio refletido (definição de difuso)
Vec3 random_esf_unitaria()
{
    while(true)
    {
        auto p = Vec3::aleatorio(-1, 1);
        if(p.comprimento_ao_quadrado() >= 1) continue;
        return p;
    }
}

// Outros aliases
using Point3 = Vec3; // Ponto 3D
using Cor = Vec3; // cor RGB

#endif