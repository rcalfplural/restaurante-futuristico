#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <sstream>
#include "restaurante.h"
#include "chef.h"

// #define TESTAR

using namespace std;

/**
 * Função para testar a execução dos Chefs.
 */
void testarChefs() {
    Chef c1, c2;
    // c1.iniciarAtendimento(1);
    // sleep(3);
    // c1.preparar("Suco de Sapo Velho");
    // sleep(2);
    // c1.preparar("Jiromba assada");
    // sleep(2);
    // c1.preparar("Carne de tucupi");
    // sleep(3);
    // c1.finalizarAtendimento();
}

bool encerrar(std::string &comando) {
    std::transform(comando.begin(), comando.end(), comando.begin(), ::toupper);
    return (comando == "FIM");
}

/**
 * Função que processa a entrada da aplicação
 *
 * @param entrada um stream de entrada, seja o terminal ou um arquivo de texto
 */
int processarEntrada(std::istream &entrada) {
    unsigned int qtdChefs, qtdMesas;
    entrada >> qtdChefs >> qtdMesas;
    std::cin.ignore();

    try {
        Restaurante restaurante(qtdChefs, qtdMesas);

        while (true) {
            std::string linha;
            std::getline(entrada, linha);
            std::cout << "La linha: "<<linha<<endl;
            if (encerrar(linha)) {
                std::cout << "FIM PROGRAMA DETECTADO"<<endl;
                break;
            };

            int mesa;
            std::string pedido;
            std::istringstream stream(linha);

            stream >> mesa;
            stream.ignore();
            std::getline(stream, pedido);

            if (encerrar(pedido)) {
                restaurante.finalizarMesa(mesa);
            } else {
                restaurante.fazerPedido(mesa, pedido);
            }
        }

        return EXIT_SUCCESS;
    } catch (exception &ex) {
        std::cerr << ex.what() << endl;
        return EXIT_FAILURE;
    }
}

/**
 * Função principal chamada para inicializar a aplicação.
 *
 * @param argc - tamanho do vetor com os parâmetros de inicialização
 * @param argv - vetor com os parâmetros de inicialização
 *
 * @return  0 (EXIT_SUCCESS) quando a aplicação finaliza com sucesso;
 *          1 (EXIT_FAILURE) quando a aplicação é encerrada devido a uma falha.
 */
int main() {
    #ifdef TESTAR
    testarChefs();
    return 0;
    #else

    return processarEntrada(std::cin);
    #endif
}
