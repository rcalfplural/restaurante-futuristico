#include "restaurante.h"
#include <algorithm>
#include <memory>

Restaurante::Restaurante(unsigned int qtdChefs, unsigned int qtdMesas) : chefs(), mesas(), chefsDisponiveis() {
    if (qtdChefs > MAX_CHEFS) {
        throw std::invalid_argument("Quantidade inválida de chefs: " + std::to_string(qtdChefs));
    } else if (qtdMesas < qtdChefs || qtdMesas > qtdChefs * 4) {
        throw std::invalid_argument("Quantidade inválida de mesas: " + std::to_string(qtdMesas));
    }

    this->chefes = new Chef[qtdChefs];
    // Instancia <qtdChefs> objetos Chef
    for (int i = 0; i < qtdChefs; i++) {
        // Chef elChef{};
        chefs.emplace_back(&chefes[i]);
        chefsDisponiveis.push_back(&chefes[i]);
    }

    for(int i = 0; i < qtdMesas; i < i++){
        mesas.emplace_back(i+1);
    }

    this->printChefs();
    this->printChefsDisponiveis();
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
    std::cout << "PEgando mesa disponivel: "<<ret->getID()<<endl;
    return ret;
}

void Restaurante::printChefs(){
    for(int i = 0; i < this->chefs.size(); i++){
        std::cout << "Chef_" << this->chefs.at(i)->getID() << endl;
    }
}

void Restaurante::printChefsDisponiveis(){
    for(int i = 0; i < this->chefsDisponiveis.size(); i++){
        std::cout << "Chef_" << this->chefsDisponiveis.at(i)->getID() << endl;
    }
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
            // Implementar fila de espera
            // throw std::runtime_error("Não há mais chefs disponiveis para o atendimento");
            std::cout << "Pedido adicionado na fila de espera"<<endl;
            this->listaEspera.push_back({ mesa, item });
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

    // Verificar lista de espera
    if(this->listaEspera.size() < 1) return;
    Pedido pendente = this->listaEspera.front();
    this->listaEspera.erase(this->listaEspera.begin());
    this->fazerPedido(pendente.mesa, pendente.pedido);
}




