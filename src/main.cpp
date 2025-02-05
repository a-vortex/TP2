#include <iostream>
#include <fstream>
#include <string>
#include "../include/gerenciador.h"
#include "../include/simulador.h"
#include "../include/evento.h"

//==========Estruturas de Dados==========

// Trabalho Prático 2 - Data Entrega 20/01
// Aluno: Maria Clara Contarini Domingos
// Matrícula: 2023060596
// Email: mccontarinid@gmail.com

//========================================

int main(int argc, char** argv) {
    // Verificação da existência do arquivo parâmetro do programa.
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.csv>" << std::endl;
        return false;
    }
    
    FILE* Entrada = fopen(argv[1], "r");
    if (!Entrada) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return false;
    }

    Gerenciador* gerenciador = new Gerenciador();
    
    // Processamento do arquivo de entrada
    Hospital* HZ = gerenciador->ProcessarEntrada(Entrada);
    fclose(Entrada);

    // Criação do simulador
    Simulador simulador(HZ);

    // Adicionar eventos iniciais de chegada
    for (int i = 0; i < HZ->populacao; ++i) {
        simulador.adicionarEvento(new Evento(CHEGADA, HZ->pacientes[i]->tempo_admissao, HZ->pacientes[i]));
    }

    // Executar a simulação
    simulador.executar();

    gerenciador->imprimirSaida(HZ->getPacientes(), HZ->getPopulacao());

    delete gerenciador;
    delete HZ;
    return 0;
    
}