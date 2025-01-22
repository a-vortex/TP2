#ifndef FILA_H
#define FILA_H

#include "paciente.h"

// O tad Fila é responsável por armazenar as informações de cada fila.
class Fila{
    private:
        
        void redimensionar(int nova_capacidade);
        
    public:

        Paciente** pacientes;
        int capacidade;
        int tamanho;

        Fila() : pacientes(nullptr), capacidade(0), tamanho(0) {}
        ~Fila() {
        for (int i = 0; i < tamanho; ++i) {
            delete pacientes[i]; // Libera a memória de cada paciente
        }
        delete[] pacientes; // Libera o array de ponteiros
    }

        void Enfileira(Paciente* paciente);
        Paciente* Desenfileira();
        bool Vazia() const;

};

#endif // FILA_H