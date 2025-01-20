#include "../include/gerenciador.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cmath> // Para std::floor

// Função que formata a data e hora
std::string Gerenciador::formatarDataHora(int ano, int mes, int dia, float hora) {
    std::tm t = {};
    t.tm_year = ano - 1900;
    t.tm_mon = mes - 1;
    t.tm_mday = dia;
    t.tm_hour = static_cast<int>(hora);
    t.tm_min = static_cast<int>((hora - t.tm_hour) * 60);
    t.tm_sec = 0;

    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", &t);
    return std::string(buffer);
}

// Lê dados de um arquivo e cria um objeto Hospital com base nesses dados.
// O tempo de atendimento de cada paciente é calculado com base nos tempos dos procedimentos e nas quantidades
// de medidas hospitalares, testes de laboratório, exames de imagem e instrumentos/medicamentos utilizados.
Hospital* Gerenciador::ProcessarEntrada(FILE *Entrada)
{
    float tempo;
    int n_unidades;
    Procedimentos procedimentos[6];
    for (int i = 0; i < 6; i++)
    {
        if (fscanf(Entrada, "%f %d", &tempo, &n_unidades) != 2) {
            std::cerr << "Erro ao ler os dados dos procedimentos." << std::endl;
            exit(1);
        }
        procedimentos[i] = Procedimentos(tempo, n_unidades, i);
    }

    if (fscanf(Entrada, "%d", &n_unidades) != 1) {
        std::cerr << "Erro ao ler o número de unidades." << std::endl;
        exit(1);
    }

    Paciente *pacientes = new Paciente[n_unidades];
    for (int i = 0; i < n_unidades; i++)
    {
        int id, alta, ano, mes, dia, grau_urgencia, medidas_hospitalares,
            testes_laboratorio, exames_imagem, instrumentos_medicamentos;
        float hora;

        // Corrigir a leitura dos dados do arquivo CSV
        if (fscanf(Entrada, "%d %d %d %d %d %f %d %d %d %d %d",
                   &id, &alta, &ano, &mes, &dia, &hora, &grau_urgencia,
                   &medidas_hospitalares, &testes_laboratorio, &exames_imagem, &instrumentos_medicamentos) != 11) {
            std::cerr << "Erro ao ler os dados do paciente." << std::endl;
            exit(1);
        }

        // Inicializar a estrutura std::tm para a data e hora de admissão
        std::tm admissao = {};
        admissao.tm_year = ano - 1900;
        admissao.tm_mon = mes - 1;
        admissao.tm_mday = dia;
        admissao.tm_hour = static_cast<int>(hora);
        admissao.tm_min = static_cast<int>((hora - admissao.tm_hour) * 60);
        admissao.tm_sec = 0;

        pacientes[i] = Paciente(id, alta, admissao, grau_urgencia, medidas_hospitalares,
                                testes_laboratorio, exames_imagem, instrumentos_medicamentos);

        pacientes[i].tempo_atendimento =  procedimentos[0].tempo + 
                                          procedimentos[1].tempo + 
                                         (procedimentos[2].tempo * pacientes[i].medidas_hospitalares) + 
                                         (procedimentos[3].tempo * pacientes[i].testes_laboratorio) +
                                         (procedimentos[4].tempo * pacientes[i].exames_imagem) + 
                                         (procedimentos[5].tempo * pacientes[i].instrumentos_medicamentos);
    }

    return new Hospital(procedimentos[0], procedimentos[1], procedimentos[2], 
                        procedimentos[3], procedimentos[4], procedimentos[5], 
                        pacientes, n_unidades);
}

std::tm Gerenciador::addHours(const std::tm& date, float hours) const {
    std::tm new_date = date;
    time_t original_time = mktime(&new_date);
    if (original_time == (time_t)-1) {
        char s[64] = {0};
        strftime(s, sizeof(s), "%c", &new_date);
        std::cerr << "Error: Invalid time value. " << s << std::endl;
        exit(EXIT_FAILURE);
    }

    original_time += static_cast<time_t>(hours * 3600);

    std::tm* updated_date = localtime(&original_time);
    if (updated_date == nullptr) {
        std::cerr << "Error: localtime conversion failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    return *updated_date;
}

std::string Gerenciador::tempoParaString(const std::tm& tempo) const {
    char s[64] = {0};
    strftime(s, sizeof(s), "%a %b %d %H:%M:%S %Y", &tempo);
    return std::string(s);
}

void Gerenciador::imprimirSaida(const Paciente& paciente) {
    // Converter os tempos para strings formatadas
    std::string admissao_str = tempoParaString(paciente.tempo_admissao);
    std::string saida_str = tempoParaString(addHours(paciente.tempo_admissao, paciente.tempo_total));

    // Imprimir os dados formatados
    std::cout << paciente.id << " ";
    std::cout << admissao_str << " ";
    std::cout << saida_str << " ";
    std::cout << paciente.tempo_total << " ";
    std::cout << paciente.tempo_espera_fila << " ";
    std::cout << paciente.tempo_atendimento << std::endl;
}