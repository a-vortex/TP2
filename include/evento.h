#ifndef EVENTO_H
#define EVENTO_H

#include "paciente.h"

enum TipoEvento {
    CHEGADA,
    ATENDIMENTO,
    SAIDA
};

// Classe que representa um evento no simulador
class Evento {
    public:
        // CHEGADA, ATENDIMENTO, SAIDA
        TipoEvento tipo;

        // Tempo em que o evento ocorre
        Tempo momento;

        // Ponteiro para o paciente associado ao evento
        Paciente* paciente;

        Evento(TipoEvento tipo, Tempo tempo_evento, Paciente* paciente) : 
               tipo(tipo), paciente(paciente) {
            momento = tempo_evento;
            }

        // Operador de comparação para a fila de prioridade
        bool operator<(const Evento& other) const {
            return momento.toDecimal() > other.momento.toDecimal();
    }
};

#endif // EVENTO_H