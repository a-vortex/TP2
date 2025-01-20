#include "../include/paciente.h"
#include <cstring> // Para std::memset

Paciente::Paciente(int id, int alta, const std::tm& admissao, int grau_urgencia,
                   int medidas_hospitalares, int testes_laboratorio, int exames_imagem, int instrumentos_medicamentos)
    : id(id), grau_urgencia(grau_urgencia),
      tempo_total(0), tempo_espera_fila(0), tempo_atendimento(0), medidas_hospitalares(medidas_hospitalares),
      testes_laboratorio(testes_laboratorio), exames_imagem(exames_imagem), instrumentos_medicamentos(instrumentos_medicamentos),
      alta(alta), estado(0) {
        tempo_admissao = admissao; // Inicializar tempo_saida com zeros
        tempo_admissao = admissao;
}