#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "paciente.h"
#include "hospital.h"
#include <fstream>
#include <string>
#include <ctime>

//A classe Gerenciador é responsável por processar a entrada do programa e montar os TADs a partir dela.
//Também é responsável por imprimir as saídas do programa.
class Gerenciador {
    public:
        Hospital* ProcessarEntrada(FILE* Entrada);
        void imprimirSaida(const Paciente& paciente);
        std::tm addHours(const std::tm& date, float hours) const;

        // Declaração da função formatarDataHora
        std::string formatarDataHora(int ano, int mes, int dia, float hora);

    private:
        std::string tempoParaString(const std::tm& tempo) const;
};

#endif // GERENCIADOR_H