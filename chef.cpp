#include "chef.h"
#include <iostream>
#include <sstream>
#include <zconf.h>

unsigned int Chef::contador = 0;
#define CHEFE_COZINHA_DIR "./resources/chefes/"

Chef::Chef() : id(++contador) {
    stringstream nome;
    nome << "ChefeCozinha_" << id;

    ofstream log;
    log.open(CHEFE_COZINHA_DIR + nome.str() + ".txt");
    log << nome.str() << endl;
    log.close();
}

Chef::~Chef() = default;

void Chef::iniciarAtendimento(const unsigned int mesa) {
    // Implemente seu código aqui...
}

void Chef::preparar(const string &pedido) {
    // Implemente seu código aqui...
    std::cout << "O chefe "<<this->id<<" recebeu o pedido "<<pedido <<endl;
}

void Chef::finalizarAtendimento() {
    // Implemente seu código aqui...
}

Chef::Atendimento::Atendimento(const unsigned int mesa) {
    // Implemente seu código aqui...
}

Chef::Atendimento::~Atendimento() {
    // Implemente seu código aqui...
}

void Chef::Atendimento::preparar(const string &pedido) {
    // Implemente seu código aqui...
}
