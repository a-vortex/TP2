#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "hospital.h"
#include "evento.h"
#include "filaprioridade.h"

class Simulador {
private:
    Hospital* hospital;
    Tempo tempo_atual;

public:
    FilaPrioridade eventos;

    Simulador(Hospital* hospital) : hospital(hospital), tempo_atual({0, 0, 0, 0}), eventos(10) {}

    ~Simulador();

    void adicionarEvento(Evento* evento);

    void executar();

    void processarEvento(Evento* evento);

    void processarChegada(Evento* evento);

    void processarAtendimento(Evento* evento);

    void processarSaida(Evento* evento);
};

#endif // SIMULADOR_H