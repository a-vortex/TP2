#include "../include/fila.h"

// Redimensiona a fila para uma nova capacidade, copiando os pacientes existentes para o novo array.
void Fila::redimensionar(int nova_capacidade) {
    Paciente** novo_array = new Paciente*[nova_capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novo_array[i] = pacientes[i];
    }
    delete[] pacientes;
    pacientes = novo_array;
    capacidade = nova_capacidade;
}

// Adiciona um novo paciente ao final da fila, redimensionando se necessário.
void Fila::Enfileira(Paciente* paciente) {
    if (tamanho == capacidade) {
        int nova_capacidade = (capacidade == 0) ? 1 : capacidade * 3;
        redimensionar(nova_capacidade);
    }
    pacientes[tamanho++] = paciente;
}

// Remove o paciente do início da fila, deslocando os pacientes restantes.
Paciente* Fila::Desenfileira() {
    if (tamanho > 0) {
        Paciente* paciente = pacientes[0];
        for (int i = 1; i < tamanho; ++i) {
            pacientes[i - 1] = pacientes[i];
        }
        --tamanho;
        return paciente;
    }
    return nullptr; // Retorna nullptr se a fila estiver vazia
}

// Verifica se a fila está vazia.
bool Fila::Vazia() const {
    return tamanho == 0;
};