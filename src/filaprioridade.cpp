#include "../include/filaprioridade.h"
#include <ctime>

FilaPrioridade::FilaPrioridade(int capacidade_inicial) : capacidade(capacidade_inicial), tamanho(0) {
    eventos = new Evento*[capacidade];
}

FilaPrioridade::~FilaPrioridade() {
    delete[] eventos;
}

void FilaPrioridade::redimensionar(int nova_capacidade) {
    Evento** novo_array = new Evento*[nova_capacidade];
    for (int i = 0; i < tamanho; ++i) {
        novo_array[i] = eventos[i];
    }
    delete[] eventos;
    eventos = novo_array;
    capacidade = nova_capacidade;
}

void FilaPrioridade::subir(int i) {
    while (i > 0 && mktime(&eventos[(i - 1) / 2]->momento) > mktime(&eventos[i]->momento)) {
        trocar(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void FilaPrioridade::descer(int i) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamanho && mktime(&eventos[esquerda]->momento) < mktime(&eventos[menor]->momento)) {
        menor = esquerda;
    }
    if (direita < tamanho && mktime(&eventos[direita]->momento) < mktime(&eventos[menor]->momento)) {
        menor = direita;
    }
    if (menor != i) {
        trocar(i, menor);
        descer(menor);
    }
}

void FilaPrioridade::trocar(int i, int j) {
    Evento* temp = eventos[i];
    eventos[i] = eventos[j];
    eventos[j] = temp;
}

void FilaPrioridade::adicionar(Evento* evento) {
    if (tamanho == capacidade) {
        redimensionar(2 * capacidade);
    }
    eventos[tamanho] = evento;
    subir(tamanho);
    tamanho++;
}

Evento* FilaPrioridade::remover() {
    if (vazio()) {
        return nullptr;
    }
    Evento* evento = eventos[0];
    eventos[0] = eventos[tamanho - 1];
    tamanho--;
    descer(0);
    return evento;
}

bool FilaPrioridade::vazio() const {
    return tamanho == 0;
}