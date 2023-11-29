#include "restaurante.h"
#include <algorithm>
#include <memory>

Restaurante::Restaurante(unsigned int qtdChefs, unsigned int qtdMesas) :mesas(), chefsDisponiveis() {
    if (qtdChefs > MAX_CHEFS) {
        throw std::invalid_argument("Quantidade inválida de chefs: " + std::to_string(qtdChefs));
    } else if (qtdMesas < qtdChefs || qtdMesas > qtdChefs * 4) {
        throw std::invalid_argument("Quantidade inválida de mesas: " + std::to_string(qtdMesas));
    }

    this->chefes = new Chef[qtdChefs];
    // Instancia <qtdChefs> objetos Chef
    for (int i = 0; i < qtdChefs; i++) {
        chefsDisponiveis.push_back(&chefes[i]);
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

/**
 * Procura se há um chefe disponivel
*/
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

    if(mesaO->getChef() == nullptr){
        if(this->chefsDisponiveis.size() < 1){
            // std::cout << "Pedido adicionado na fila de espera"<<endl;
            this->adicionarListaEspera(mesa, item);
            return;
        }
        mesaO->assignChef(this->getChefDisponivel());
    }

    // Depois removo esses logs sem sentido
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
    mesaO->assignChef(nullptr);
    chefsDisponiveis.push_back(chef);

    consultarListaEspera();
}

/**
 * IMPLEMENTAÇÃO LISTA DE ESPERA
*/
void Restaurante::consultarListaEspera(){
    // Verificar lista de espera
    if(this->listaEspera.size() < 1) return;
    Pedido pendente = this->listaEspera.front();
    this->listaEspera.erase(this->listaEspera.begin());
    this->fazerPedido(pendente.mesa, pendente.pedido);   
}

void Restaurante::adicionarListaEspera(unsigned int mesa, const std::string &item){
    this->listaEspera.push_back({ mesa, item });
}


