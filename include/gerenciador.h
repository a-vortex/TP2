#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "paciente.h"
#include "hospital.h"
#include "auxiliar.h"
#include <fstream>
#include <iomanip>

//A classe Gerenciador é responsável por processar a entrada do programa e montar os TADs a partir dela.
class Gerenciador {
    public:
        Hospital* ProcessarEntrada(FILE* Entrada);
        void imprimirSaida(Paciente** pacientes, int n_unidades);
};

#endif // GERENCIADOR_H