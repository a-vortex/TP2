#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include <cstdio>
#include <string>

#include "hospital.h"
#include "procedimentos.h"

//A classe Gerenciador é responsável por processar a entrada do programa e montar os TADs a partir dela.
//Também é responsável por imprimir as saídas do programa.
class Gerenciador {
    private:
    
        std::string formatarDataHora(int ano, int mes, int dia, float hora);

    public:

        Hospital ProcessarEntrada(FILE* Entrada);
        void ImprimirSaida(Hospital HZ);

};

#endif // GERENCIADOR_H