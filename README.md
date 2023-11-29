# Restaurante Futurístico

Aplicação em C++ que exemplifica o uso de comunicação entre processos por meio das funções fork e pipe.

## Informações da submissão do Trabalho

#### Funcionalidades implementadas:
- [ ] Implementação do atendimento dos pedidos em ``Restaurante::fazerPedido()`` na linha 49 do arquivo `restaurante.cpp`.
- [ ] Algoritmo resposável pela verificação para saber se a mesa já está sendo atendida com complexidade O(1): `Chef *Mesa::getChef()` em `mesa.cpp`.
- [ ] Verificação de chef disponível O(1) em `Chef* Restaurante::getChefDisponivel()` no arquivo `restaurante.cpp`.
- [ ] Lista de espera implementada em `void Restaurante::consultarListaEspera()` e `void Restaurante::adicionarListaEspera(unsigned int mesa, const std::string &item)` em `restaurante.cpp`.

#### Sobre o arquivo de entrada
O arquivo original de entrada (`resources/entrada_original.txt`) tem na estrutura os argumentos de entrada do numero de mesas e de chefes dispostos em uma só linha de entrada fazendo com que o programa leia apenas o primeiro numero e pule para a proxima linha ignorando o segundo numero na entrada. Além de que o comando da linha 10 faça com que o programa dispare a exceção `std::runtime_error("Não há Chef está atendendo a mesa: " + std::to_string(mesa));` em `void Restaurante::finalizarMesa(unsigned int mesa);` no arquivo `restaurante.txt`.