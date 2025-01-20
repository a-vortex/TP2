#include "../include/paciente.h"

Paciente::Paciente(int id, int alta, Tempo chegada, int grau_urgencia,
                   int medidas_hospitalares, int testes_laboratorio, int exames_imagem, int instrumentos_medicamentos)
    : id(id), tempo_saida(0, 0, 0, 0), grau_urgencia(grau_urgencia),
      tempo_total(0), tempo_espera_fila(0), tempo_atendimento(0), medidas_hospitalares(medidas_hospitalares),
      testes_laboratorio(testes_laboratorio), exames_imagem(exames_imagem), instrumentos_medicamentos(instrumentos_medicamentos),
      alta(alta), estado(0) {
        tempo_admissao = chegada;
}