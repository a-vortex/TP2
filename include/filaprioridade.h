#ifndef FILAPRIORIDADE_H
#define FILAPRIORIDADE_H

#include "evento.h"

class FilaPrioridade
{
private:
    Evento** eventos;
    int capacidade;
    int tamanho;

    // Redimensiona o array dinâmico para uma nova capacidade
    void redimensionar(int nova_capacidade);

    // Move o elemento no índice i para cima na fila de prioridade para restaurar a propriedade do heap
    void subir(int i);

    // Move o elemento no índice i para baixo na fila de prioridade para restaurar a propriedade do heap
    void descer(int i);

    // Troca dois elementos no array
    void trocar(int i, int j);

public:
    FilaPrioridade(int capacidade_inicial = 10);
    ~FilaPrioridade();

    // Insere um novo evento na fila de prioridade
    void adicionar(Evento* evento);

    // Remove e retorna o menor evento da fila de prioridade
    Evento* remover();

    // Verifica se a fila de prioridade está vazia
    bool vazio() const;
};

#endif // FILAPRIORIDADE_H