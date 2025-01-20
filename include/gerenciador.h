#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include <cstdio>
#include <string>

#include "hospital.h"
#include "procedimentos.h"
#include "tempo.h"

//A classe Gerenciador é responsável por processar a entrada do programa e montar os TADs a partir dela.
//Também é responsável por imprimir as saídas do programa.
class Gerenciador {
    public:
        Hospital* ProcessarEntrada(FILE* Entrada);
        void imprimirSaida(const Paciente& paciente);

        // Declaração da função formatarDataHora
        std::string formatarDataHora(int ano, int mes, int dia, float hora);

private:
    std::string tempoParaString(const Tempo& tempo) const;
};

#endif // GERENCIADOR_H