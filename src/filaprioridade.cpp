#include "../include/filaprioridade.h"
#include <algorithm>

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
    while (i > 0 && eventos[(i - 1) / 2]->momento.toDecimal() > eventos[i]->momento.toDecimal()) {
        trocar(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void FilaPrioridade::descer(int i) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamanho && eventos[esquerda]->momento.toDecimal() < eventos[menor]->momento.toDecimal()) {
        menor = esquerda;
    }
    if (direita < tamanho && eventos[direita]->momento.toDecimal() < eventos[menor]->momento.toDecimal()) {
        menor = direita;
    }
    if (menor != i) {
        trocar(i, menor);
        descer(menor);
    }
}

void FilaPrioridade::trocar(int i, int j) {
    std::swap(eventos[i], eventos[j]);
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