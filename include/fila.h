#ifndef FILA_H
#define FILA_H

#include "paciente.h"

// O tad Fila é responsável por armazenar as informações de cada fila.
class Fila{
    private:
        
        void redimensionar(int nova_capacidade);
        
    public:

        Paciente* pacientes;
        int capacidade;
        int tamanho;

        Fila() : pacientes(nullptr), capacidade(0), tamanho(0) {}
        ~Fila() { delete[] pacientes; }

        void Enfileira(const Paciente& paciente);
        Paciente* Desenfileira();
        bool Vazia() const;

};

#endif // FILA_H