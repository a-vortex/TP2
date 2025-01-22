#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "paciente.h"
#include "procedimentos.h"

// Classe que representa um hospital
class Hospital {
public:
    Procedimentos Triagem;
    Procedimentos Atendimento;
    Procedimentos Medidas;
    Procedimentos Testes;
    Procedimentos Imagem;
    Procedimentos Instrumentos;

    Paciente** pacientes;
    int populacao;

    int getPopulacao() const { return populacao; }
    Paciente** getPacientes() const { return pacientes; }

    // Desabilitar a cópia do objeto Hospital
    Hospital(const Hospital&) = delete;
    Hospital& operator=(const Hospital&) = delete;

    // Construtor que inicializa os procedimentos e os pacientes
    Hospital(Procedimentos triagem, Procedimentos atendimento, Procedimentos medidas, 
            Procedimentos testes, Procedimentos imagem, Procedimentos instrumentos, 
            Paciente** pacientes, int n_unidades) 
            :Triagem(triagem), Atendimento(atendimento), Medidas(medidas), 
            Testes(testes), Imagem(imagem), Instrumentos(instrumentos), 
            pacientes(pacientes), populacao(n_unidades) {}

    // Destrutor que libera a memória alocada para os pacientes
    ~Hospital() {
        if (pacientes != nullptr) {
            for (int i = 0; i < populacao; ++i) {
                delete pacientes[i];
            }
            delete[] pacientes;
            pacientes = nullptr;
        }
    }
};

#endif // HOSPITAL_H