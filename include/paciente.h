#ifndef PACIENTE_H
#define PACIENTE_H

#include <ctime> 

class Paciente {
public:
    int id;
    int alta;
    std::tm tempo_admissao;
    std::tm tempo_saida;
    int grau_urgencia;
    float tempo_atendimento;
    int medidas_hospitalares;
    int testes_laboratorio;
    int exames_imagem;
    int instrumentos_medicamentos;
    int estado;
    float tempo_total;
    float tempo_espera_fila;

    Paciente(){};
    Paciente(int id, int alta, const std::tm& admissao, int grau_urgencia, int medidas_hospitalares, int testes_laboratorio, int exames_imagem, int instrumentos_medicamentos);
    void inicializarsaida();
};

#endif // PACIENTE_H