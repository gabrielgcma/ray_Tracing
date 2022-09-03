#ifndef OBJS_HITAVEIS_H
#define OBJS_HITAVEIS_H

#include "hitavel.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class Objs_Hitaveis : public Hitavel
{
public:
    std::vector<shared_ptr<Hitavel>> objetos;

    void clear() { objetos.clear(); }
    void add(shared_ptr<Hitavel> objeto) { objetos.push_back(objeto); }

    Objs_Hitaveis() {}
    Objs_Hitaveis(shared_ptr<Hitavel> objeto) { add(objeto); }

    virtual bool hit(const Ray &r, double t_min, double t_max, Hit_registro &reg) const override;
};

bool Objs_Hitaveis::hit(const Ray &r, double t_min, double t_max, Hit_registro &reg) const
{
    Hit_registro reg_temp;
    bool acertou_algo = false;
    auto mais_proximo = t_max;

    for (const auto &objeto : objetos)
    {
        if (objeto->hit(r, t_min, mais_proximo, reg_temp))
        {
            acertou_algo = true;
            mais_proximo = reg_temp.t;
            reg = reg_temp;
        }
    }

    return acertou_algo;
}

#endif