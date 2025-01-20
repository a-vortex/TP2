#ifndef EVENTO_H
#define EVENTO_H

#include "paciente.h"
#include <ctime>

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
        std::tm momento;

        // Ponteiro para o paciente associado ao evento
        Paciente* paciente;

        Evento(TipoEvento tipo, const std::tm& tempo_evento, Paciente* paciente) : 
               tipo(tipo), momento(tempo_evento), paciente(paciente) {
            momento = tempo_evento;
            }

        // Operador de comparação para a fila de prioridade
        bool operator<(const Evento& other) const {
            return mktime(const_cast<std::tm*>(&momento)) > mktime(const_cast<std::tm*>(&other.momento));
        }
};

#endif // EVENTO_H