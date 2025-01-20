#ifndef PROCEDIMENTOS_H
#define PROCEDIMENTOS_H

#include "fila.h"
#include "paciente.h"
#include <ctime> 

// TAD responsável por armazenar as informações dos procedimentos, com suas respectivas filas.
class Procedimentos {
    private:
        Fila vermelha; // Fila de prioridade vermelha
        Fila amarela; // Fila de prioridade amarela
        Fila verde; // Fila de prioridade verde

    public:
        int nome; // Nome do procedimento
        float tempo; // Tempo necessário para realizar o procedimento em horas
        int n_unidades; // Número de unidades disponíveis para o procedimento

        float tempo_ocioso; // Tempo ocioso das unidades
        float tempo_util; // Tempo útil das unidades

        float tempo_espera_vermelha = 0; // Tempo de espera acumulado para a fila vermelha
        float tempo_espera_amarela = 0; // Tempo de espera acumulado para a fila amarela
        float tempo_espera_verde = 0; // Tempo de espera acumulado para a fila verde

        Fila& getVerde() { return verde; }
        Fila& getAmarela() { return amarela; }
        Fila& getVermelha() { return vermelha; }

        // Construtor padrão
        Procedimentos() : nome(0), tempo(0), n_unidades(0), tempo_ocioso(0), tempo_util(0) {}

        // Construtor que inicializa o tempo e o número de unidades
        // @param tempo Tempo necessário para realizar o procedimento
        // @param n_unidades Número de unidades disponíveis para o procedimento
        Procedimentos(float aux, int n_unidades, int Nome) : nome(Nome), tempo(aux), n_unidades(n_unidades), tempo_ocioso(0), tempo_util(0) {}

        // Destrutor padrão
        ~Procedimentos() = default;
};

#endif // PROCEDIMENTOS_H