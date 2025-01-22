#include "../include/paciente.h"
#include <cstring> // Para std::memset

Paciente::Paciente(int id, int alta, const std::tm& admissao, int grau_urgencia,
                   int medidas_hospitalares, int testes_laboratorio, int exames_imagem, int instrumentos_medicamentos)
    : id(id), alta(alta), tempo_admissao(admissao), grau_urgencia(grau_urgencia),
      medidas_hospitalares(medidas_hospitalares), testes_laboratorio(testes_laboratorio),
      exames_imagem(exames_imagem), instrumentos_medicamentos(instrumentos_medicamentos) {
        tempo_espera_fila = 0;
        tempo_total = 0;
        estado = 1;
        inicializarsaida();
    // Construtor inicializa os membros da classe com os valores dos parâmetros
}
void Paciente::inicializarsaida(){
        std::tm saida = {};
        saida.tm_year = 0;
        saida.tm_mon = 0;
        saida.tm_mday = 0;
        saida.tm_hour = 0;
        saida.tm_min = 0;
        saida.tm_sec = 0;
        saida.tm_isdst = -1;
        mktime(&saida);

        this->tempo_saida = saida;
}