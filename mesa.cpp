#include "mesa.h"

Mesa::Mesa(int numeroMesa): numeroMesa(numeroMesa) {
}

Chef *Mesa::getChef(){
    return this->chefResponsavel;
}

void Mesa::assignChef(Chef *chef){
    this->chefResponsavel = chef;
}