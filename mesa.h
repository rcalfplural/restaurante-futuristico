#ifndef _MESA_H
#define _MESA_H

#include "chef.h"

class Mesa{
    public:
    Chef *getChef();
    void assignChef(Chef *chef);
    Mesa(int numeroMesa);

    private:
    int numeroMesa;
    Chef *chefResponsavel;
    friend class Restaurante;
};

#endif