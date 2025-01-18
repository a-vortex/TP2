#ifndef PACIENTE_H
#define PACIENTE_H

#include <time.h>

// A classe paciente é o tad responsável por armazenar as informações de cada paciente.
class Paciente{
    public:

        int id;                 // Identificador único
        int alta;               // 0: Não teve alta, 1: Teve alta
        int ano;                // Data e hora de admissão
        int mes;
        int dia;
        float hora;
        int grau_urgencia;      // 0: Verde, 1: Amarelo, 2: Vermelho

        int medidas_hospitalares;
        int testes_laboratorio;
        int exames_imagem;
        int instrumentos_medicamentos;

        int estado_atual;        // Estado do paciente (1 a 14)
        float tempo_espera;      // Tempo total em filas
        float tempo_atendimento; // Tempo total sendo atendido
        float tempo_total;       // Tempo total no hospital

        Paciente(){};
        Paciente(int id, int alta, int ano, int mes, int dia, float hora, int grau_urgencia, 
                 int medidas_hospitalares, int testes_laboratorio, int exames_imagem, int instrumentos_medicamentos) : 
                 id(id), alta(alta), ano(ano), mes(mes), dia(dia), hora(hora), grau_urgencia(grau_urgencia), 
                 medidas_hospitalares(medidas_hospitalares), testes_laboratorio(testes_laboratorio), 
                 exames_imagem(exames_imagem), instrumentos_medicamentos(instrumentos_medicamentos) {
            estado_atual = 0;
            tempo_espera = 0;
            tempo_atendimento = 0;
            tempo_total = tempo_atendimento + tempo_espera;
        };

};

#endif // PACIENTE_H