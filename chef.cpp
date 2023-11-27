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

void Chef::atualizarArquivo(const std::string &info){
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
    ofstream log;

    log.open(CHEFE_COZINHA_DIR+nome.str() + ".txt", ios::trunc);
    log << nome.str() << endl;
    log.close();
}

void Chef::iniciarAtendimento(const unsigned int mesa) {
    // Implemente seu código aqui...
    this->atualizarArquivo("Mesa "+std::to_string(mesa)+": ");
    this->atendimento = new Chef::Atendimento(mesa, this);
}

void Chef::preparar(const string &pedido) {
    this->atendimento->preparar(pedido);
}

void Chef::finalizarAtendimento() {
    delete this->atendimento;
}

Chef::Atendimento::Atendimento(const unsigned int mesa, Chef *chef) {
    this->chef = chef;
    this->mesa = mesa;
    
    /**
     * IMPLEMENTAÇÃO DA PARTE DE IPC!!!!!! COMECANDO A FAZER MENOS DE 1 HORA DA ENTREGA SO PRA SABER!
    */
   if(pipe(this->fd) < 0){
        throw runtime_error("Pipe falhou!");
   }

    if(this->pid < 0){
        throw runtime_error("Fork falhou!!");
    }
}

Chef::Atendimento::~Atendimento() {
    // TODO
    close(this->fd[ESCRITA]);
    close(this->fd[LEITURA]);
}

void Chef::Atendimento::preparar(const std::string &pedido) {
    this->pid = fork();

    if(this->pid < 0){
        throw runtime_error("Fork Falhou!");
    }
    else if(this->pid > 0){ // Processo pai
        close(this->fd[ESCRITA]);

        wait(nullptr);

        char buffer[256];
        ssize_t lido = read(this->fd[LEITURA], buffer, sizeof(buffer));
        if(lido < 0) {
            throw runtime_error("Deu bosta aqui na leitura");
        }
        std::cout << "Processo pai esta recebendo "<<buffer<<endl;
        std::string mensagem = buffer;
        this->chef->atualizarArquivo("  - "+mensagem);
        close(this->fd[LEITURA]);
    }else{ // Processo filho
        std::cout << "Processo filho esta mandando "<<pedido.c_str()<<endl;
        close(this->fd[LEITURA]);
        ssize_t escrito = write(this->fd[ESCRITA], pedido.c_str(), pedido.size()+1);
        if(escrito < 0){
            throw new runtime_error("Deu bosta aqui na escrita");
        }
        std::cout << escrito << " foi escrito!"<<endl;
        close(this->fd[ESCRITA]);
        exit(0);
    }
}
