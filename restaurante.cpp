#include "restaurante.h"


Restaurante::Restaurante(unsigned int qtdChefs, unsigned int qtdMesas) : chefs() {
    if (qtdChefs > MAX_CHEFS) {
        throw std::invalid_argument("Quantidade inválida de chefs: " + std::to_string(qtdChefs));
    } else if (qtdMesas < qtdChefs || qtdMesas > qtdChefs * 4) {
        throw std::invalid_argument("Quantidade inválida de mesas: " + std::to_string(qtdMesas));
    }

    // Instancia <qtdChefs> objetos Chef
    for (int i = 0; i < qtdChefs; i++) {
        chefs.emplace_back();
    }
}

Chef *Restaurante::getChef(unsigned int mesa) {
    // Implemente seu código aqui...
    return nullptr;
}

void Restaurante::fazerPedido(unsigned int mesa, const std::string &item) {
    // Implemente seu código aqui...
}

void Restaurante::finalizarMesa(unsigned int mesa) {
    if (this->getChef(mesa) == nullptr) {
        throw std::runtime_error("Não há Chef está atendendo a mesa: " + std::to_string(mesa));
    }
    // Implemente seu código aqui...
}




