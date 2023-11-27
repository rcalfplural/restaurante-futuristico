#ifndef RESTAURANTE_APP_RESTAURANTE_H
#define RESTAURANTE_APP_RESTAURANTE_H

#include <iostream>
#include <string>
#include <vector>
#include "chef.h"
#include "mesa.h"

// Caso queira usar uma estrutura para armazenar as informações de um pedido...
struct Pedido {
    unsigned int mesa;
    std::string pedido;
};

class Restaurante {
public:

    /**
     * Cria um objeto Restaurante contendo uma quantidade definida de chefs e de mesas.
     *
     * @param qtdChefs número de chefs
     * @param qtdMesas número de mesas
     */
    Restaurante(unsigned int qtdChefs, unsigned int qtdMesas);

    /**
     * Informa um pedido ao restaurante.
     *
     * @param mesa
     * @param item
     */
    void fazerPedido(unsigned int mesa, const std::string &item);
    void finalizarMesa(unsigned int mesa);
    void printChefs();
    void printChefsDisponiveis();

    Chef*   getChefDisponivel();

private:
    static const unsigned int MAX_CHEFS = 100;

    std::vector<Chef*> chefs;
    Chef *chefes;
    std::vector<Chef*> chefsDisponiveis;
    std::vector<Mesa> mesas;
    std::vector<Pedido> listaEspera;
    // Como armazenar as informações das mesas?
    // Como armazenar os pedidos em espera?

    /**
     * Retorna um ponteiro para o Chef que está atendendo a mesa.
     *
     * @param mesa número da mesa
     * @return um ponteiro para o Chef
     */
    Mesa *getMesa(unsigned int mesa);
};


#endif //RESTAURANTE_APP_RESTAURANTE_H
