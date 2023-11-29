#include "mesa.h"

Mesa::Mesa(int numeroMesa): numeroMesa(numeroMesa), chefResponsavel() {
}

Chef *Mesa::getChef(){
    return this->chefResponsavel;
}

void Mesa::assignChef(Chef *chef){
    this->chefResponsavel = chef;
    if(chef == nullptr) return;
    this->chefResponsavel->iniciarAtendimento(this->numeroMesa);
}