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
    this->inicializarArquivo();
}

Chef::~Chef() = default;

void Chef::iniciarAtendimento(const unsigned int mesa) {
    // Implemente seu código aqui...
    this->atendimento = new Chef::Atendimento(mesa, this);
    
}

void Chef::atualizarArquivo(const std::string info){
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

void Chef::preparar(const string &pedido) {
    int *fd = this->atendimento->fd; 

    this->atendimento->preparar();
    if(this->atendimento->pid < 1) return;
    close(fd[LEITURA]); // Fecha a leitura pois aqui apenas a escrita será usada
    write(fd[ESCRITA], pedido.c_str(), pedido.size()+1);
}

void Chef::finalizarAtendimento() {
    delete this->atendimento;
}

Chef::Atendimento::Atendimento(const unsigned int mesa, Chef *chef) {
    this->pid = fork();
    this->chef = chef;
    this->mesa = mesa;
    if(pipe(this->fd) < 0){
        std::cerr << "Falhou o pipe!" << endl;
        return;
    }

}

Chef::Atendimento::~Atendimento() {
    close(fd[LEITURA]);
    close(fd[ESCRITA]);
    if(this->pid > 0){
        std::cout << "Estamos separados falhamos"<<endl;
        kill(this->pid, 0);
    }else{
        std::cout << "Estamos juntos conseguimos"<<endl;
    }
}

void Chef::Atendimento::preparar() {
    if(this->pid > 0) return;
    std::cout << "RECEBA!"<<endl;
    char *recebimento;
    close(this->fd[ESCRITA]);
    read(this->fd[LEITURA], recebimento, sizeof(recebimento));
    this->chef->atualizarArquivo(std::to_string(this->mesa)+" "+recebimento);
}
