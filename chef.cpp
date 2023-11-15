#include "chef.h"
#include <iostream>
#include <sstream>
#include <zconf.h>

unsigned int Chef::contador = 0;

Chef::Chef() : id(++contador) {
    stringstream nome;
    nome << "ChefeCozinha_" << id;

    ofstream log;
    log.open(nome.str() + ".txt");
    log << nome.str() << endl;
    log.close();
}

Chef::~Chef() = default;

void Chef::iniciarAtendimento(const unsigned int mesa) {
    // Implemente seu código aqui...
}

void Chef::preparar(const string &pedido) {
    // Implemente seu código aqui...
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
