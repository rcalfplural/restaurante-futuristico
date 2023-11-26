#include "chef.h"
#include <iostream>
#include <sstream>
#include <zconf.h>
#include <sys/wait.h>

unsigned int Chef::contador = 0;

#define CHEFE_COZINHA_DIR "./resources/chefes/"

#define LEITURA 0
#define ESCRITA 1


Chef::Chef() : id(++contador) {
    std::cout << "Acabei de criar o chefe "<<id<<endl;
    this->inicializarArquivo();
}

Chef::~Chef() = default;

void Chef::atualizarArquivo(const std::string &info){
    std::cout << "Escrevendo a info "<<info<<endl;
    stringstream nome;
    nome << "ChefeCozinha_" << this->id;

    ofstream log;

    log.open(CHEFE_COZINHA_DIR+nome.str() + ".txt", ios::app);
    log << info << endl;
    log.close();
}

void Chef::inicializarArquivo(){
    stringstream nome;
    nome << "ChefeCozinha_" << id;

    std::cout << "Inicializando Chef "<<nome.str()<<endl;
    ofstream log;

    log.open(CHEFE_COZINHA_DIR+nome.str() + ".txt", ios::trunc);
    log << nome.str() << endl;
    log.close();
}

void Chef::iniciarAtendimento(const unsigned int mesa) {
    // Implemente seu código aqui...
    this->atendimento = new Chef::Atendimento(mesa, this);
    
}

void Chef::preparar(const string &pedido) {
    int *fd = this->atendimento->fd; 

    this->atendimento->preparar(pedido);
}

void Chef::finalizarAtendimento() {
    this->atualizarArquivo(std::to_string(this->atendimento->mesa)+" fim");
    delete this->atendimento;
}

Chef::Atendimento::Atendimento(const unsigned int mesa, Chef *chef) {
    this->chef = chef;
    this->mesa = mesa;
}

Chef::Atendimento::~Atendimento() {
    // TODO
}

void Chef::Atendimento::preparar(const std::string &pedido) {
    this->chef->atualizarArquivo(std::to_string(this->mesa)+" "+pedido);
}
