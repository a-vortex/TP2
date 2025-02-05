#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "hospital.h"
#include "evento.h"
#include "filaprioridade.h"
#include "auxiliar.h"
#include <ctime>

class Simulador {
private:
    Hospital* hospital;
    std::tm tempo_atual;
    bool temEventoOuFila() const;

public:
    FilaPrioridade eventos;

    Simulador(Hospital* hospital) 
    : hospital(hospital), 
      tempo_atual({0, 0, 0, 0, 0, 0, 0, 0, 0, -1, nullptr}), 
      eventos(10) {}

    ~Simulador();

    void adicionarEvento(Evento* evento);

    void executar();

    void processarChegada(Evento* evento);

    void processarAtendimento(Evento* evento);

    void processarSaida(Evento* evento);

    double getElapsedHours(const std::tm& start, const std::tm& end) const;
    
    std::tm addHours(const std::tm& date, float hours) const;
};

#endif // SIMULADOR_H