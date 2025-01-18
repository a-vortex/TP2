#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "paciente.h"
#include "procedimentos.h"

//Tad responsavel por armazenar as informações do hospital.
class Hospital{
    public:

        Procedimentos Triagem;
        Procedimentos Atendimento;

        Procedimentos Medidas;
        Procedimentos Testes;
        Procedimentos Imagem;
        Procedimentos Instrumentos;

        Paciente* pacientes; // Ponteiro para um array dinâmico de Pacientes
        int populacao;       // Número de pacientes

        Hospital(Procedimentos Triagem, Procedimentos Atendimento, Procedimentos Medidas, 
                 Procedimentos Testes, Procedimentos Imagem, Procedimentos Instrumentos,
                 Paciente* pacientes, int n_unidades) : 
                 Triagem(Triagem), Atendimento(Atendimento), Medidas(Medidas), 
                 Testes(Testes), Imagem(Imagem), Instrumentos(Instrumentos),
                 pacientes(pacientes), populacao(n_unidades) {};
        ~Hospital() {
            Triagem.~Procedimentos();
            Atendimento.~Procedimentos();
            Medidas.~Procedimentos();
            Testes.~Procedimentos();
            Imagem.~Procedimentos();
            Instrumentos.~Procedimentos();
            delete[] pacientes;
        }

};

#endif // HOSPITAL_H