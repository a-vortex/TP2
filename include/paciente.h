#ifndef PACIENTE_H
#define PACIENTE_H

#include "tempo.h"

// A classe paciente é o tad responsável por armazenar as informações de cada paciente.
struct Paciente {
    int id;
    Tempo tempo_admissao;
    Tempo tempo_saida;
    int grau_urgencia;
    float tempo_total;
    float tempo_espera_fila;
    float tempo_atendimento;
    int medidas_hospitalares;
    int testes_laboratorio;
    int exames_imagem;
    int instrumentos_medicamentos;
    int alta;
    int estado;

    Paciente(){};
    Paciente(int id, int alta, Tempo chegada, int grau_urgencia,
             int medidas_hospitalares, int testes_laboratorio, int exames_imagem, int instrumentos_medicamentos);
};
#endif // PACIENTE_H