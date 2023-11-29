#ifndef RESTAURANTE_APP_CHEF_H
#define RESTAURANTE_APP_CHEF_H

#include <csignal>
#include <fstream>
#include <string>

using namespace std;

class Chef {
public:

    /**
     * Cria um objeto Chef.
     */
    Chef();

    /**
     * Destrói um objeto Chef.
     */
    virtual ~Chef();

    /**
     * Inicia o atendimento a uma mesa.
     *
     * @param mesa número da mesa
     */
    void iniciarAtendimento(unsigned int mesa);

    /**
     * Finaliza o atendimento da mesa atual.
     */
    void finalizarAtendimento();

    /**
     * Prepara o pedido de uma mesa em atendimento.
     *
     * @param pedido string com o pedido
     */
    void preparar(const std::string &pedido);

    /**
     * Retorna o id deste objeto Chef.
     *
     * @return o id
     */
    [[nodiscard]] unsigned int getID() const { return id; }

private:

    void inicializarArquivo();
    void atualizarArquivo(const std::string &info);

    class Atendimento;

    static unsigned int contador;

    const unsigned int id;
    Atendimento *atendimento{};

    class Atendimento {
    public:

        /** 
         * Cria um objeto Atendimento vinculando sua existência a um processo filho em execução.
         * Quando este objeto é instanciado, um processo filho é criado juntamente a um canal de comunicação.
         *
         * @param mesa número da mesa ao qual este chef está preparando pedidos
         */
        explicit Atendimento(unsigned int mesa, Chef *chef);

        /** 
         * Destrói um objeto Atendimento.
         * Quando este é deletado, o processo vinculado a ele é encerrado.
         */
        virtual ~Atendimento(); 

        void preparar(const std::string &pedido);

    private:
        Chef *chef;
        int fd[2] = {0, 0};
        int mesa;
        pid_t pid;
        friend class Chef;
    };

};

#endif //RESTAURANTE_APP_CHEF_H
