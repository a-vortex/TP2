#include <iostream>
#include <fstream>
#include <string>

#include "../include/gerenciador.h"

//==========Estruturas de Dados==========

// Trabalho Prático 2 - Data Entrega 20/01
// Aluno: Maria Clara Contarini Domingos
// Matrícula: 2023060596
// Email: mccontarinid@gmail.com

//========================================

int main(int argc, char** argv) {

    //Verificação da existência do arquivo parâmetro do programa.
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.xcsv>" << std::endl;
        return 1;
    }
    
    FILE* Entrada = fopen(argv[1], "r");
    if (!Entrada) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return 1;
    }

    //Processamento do arquivo de entrada
    Gerenciador* gerenciador = new Gerenciador();
    Hospital HZ = gerenciador->ProcessarEntrada(Entrada);
    fclose(Entrada);

    //todo logica de estados
    
    delete gerenciador;
    return 0;

}
