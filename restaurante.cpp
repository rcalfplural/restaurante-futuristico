#include "restaurante.h"
#include <algorithm>

Restaurante::Restaurante(unsigned int qtdChefs, unsigned int qtdMesas) : chefs(), mesas(), chefsDisponiveis() {
    if (qtdChefs > MAX_CHEFS) {
        throw std::invalid_argument("Quantidade inválida de chefs: " + std::to_string(qtdChefs));
    } else if (qtdMesas < qtdChefs || qtdMesas > qtdChefs * 4) {
        throw std::invalid_argument("Quantidade inválida de mesas: " + std::to_string(qtdMesas));
    }

    // Instancia <qtdChefs> objetos Chef
    for (int i = 0; i < qtdChefs; i++) {
        chefs.emplace_back();
        chefsDisponiveis.emplace_back(&chefs.at(i));
    }

    for(int i = 0; i < qtdMesas; i < i++){
        mesas.emplace_back(i+1);
    }
}

Mesa *Restaurante::getMesa(unsigned int mesa) {
    // Implemente seu código aqui...
    auto it = std::find_if(this->mesas.begin(), this->mesas.end(), [mesa](const Mesa &obj){
        return obj.numeroMesa == mesa;
    });


    if(it != this->mesas.end()){

        return &(*it);
    }

    return nullptr;
}


Chef *Restaurante::getChefDisponivel(){
    if(chefsDisponiveis.size() < 1) return nullptr;
    Chef *ret = chefsDisponiveis.front();
    chefsDisponiveis.erase(chefsDisponiveis.begin());
    return ret;
}

void Restaurante::fazerPedido(unsigned int mesa, const std::string &item) {
    // Pegar o chefe responsavel pela tal mesa
    Mesa *mesaO = this->getMesa(mesa);
    // Se o chef for null dai "cadastra" um novo chef na tal mesa
    if(mesaO == nullptr){
        throw std::runtime_error("Mesa nao encontrada: "+std::to_string(mesa));
    }

    Chef *chef = mesaO->getChef();

    if(chef == nullptr){
        // "cadastra um novo chef na tal mesa"
        Chef *chefDisponivel = getChefDisponivel();

        if(chefDisponivel == nullptr){
            // Adiciona na fila de espera
            throw std::runtime_error("[ERRO]: Restaurante::fazerPedido. Não há chefes disponiveis! Favor implementar a fila de espera!");
        }

        mesaO->assignChef(chefDisponivel);
        mesaO->getChef()->iniciarAtendimento(mesaO->numeroMesa);
    }

    // Depois removo esses logs sem sentido
    std::cout << "O chef "<<mesaO->getChef()->getID()<< " irá coisar o pedido "<<item <<  " para a mesa " << mesaO->numeroMesa << endl;
    mesaO->getChef()->preparar(item);
}



void Restaurante::finalizarMesa(unsigned int mesa) {
    Mesa *mesaO = this->getMesa(mesa);

    Chef *chef = mesaO->getChef();
    if (chef == nullptr) {
        throw std::runtime_error("Não há Chef está atendendo a mesa: " + std::to_string(mesa));
    }

    // Finaliza atendimento do chef e readiciona ele na fila de chefes disponiveis
    chef->finalizarAtendimento();
    chefsDisponiveis.emplace_back(chef);
}




