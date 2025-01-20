#include "../include/gerenciador.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

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
        Tempo chegada{ano, mes, dia, hora};        
        pacientes[i] = Paciente(id, alta, chegada, grau_urgencia, medidas_hospitalares,
                                testes_laboratorio, exames_imagem, instrumentos_medicamentos);

        pacientes[i].tempo_atendimento =  procedimentos[0].tempo.toDecimal() + 
                                          procedimentos[1].tempo.toDecimal() + 
                                         (procedimentos[2].tempo.toDecimal() * pacientes[i].medidas_hospitalares) + 
                                         (procedimentos[3].tempo.toDecimal() * pacientes[i].testes_laboratorio) +
                                         (procedimentos[4].tempo.toDecimal() * pacientes[i].exames_imagem) + 
                                         (procedimentos[5].tempo.toDecimal() * pacientes[i].instrumentos_medicamentos);
    }

    return new Hospital(procedimentos[0], procedimentos[1], procedimentos[2], 
                        procedimentos[3], procedimentos[4], procedimentos[5], 
                        pacientes, n_unidades);
}

void Gerenciador::imprimirSaida(const Paciente& paciente) {
    // Truncar a hora de tempo_saida para 2 casas decimais
    Tempo tempo_saida_truncado = paciente.tempo_saida;
    tempo_saida_truncado.hora = std::floor(tempo_saida_truncado.hora * 100) / 100.0;
    std::cout<<tempo_saida_truncado.hora<<std::endl;

    // Converter os tempos para strings formatadas
    std::string admissao_str = tempoParaString(paciente.tempo_admissao);
    std::string saida_str = tempoParaString(tempo_saida_truncado);

    // Imprimir os dados formatados
    std::cout << std::setfill('0') << std::setw(7) << paciente.id << " ";
    std::cout << admissao_str << " ";
    std::cout << saida_str << " ";
    std::cout << std::fixed << std::setprecision(2) << paciente.tempo_total << " ";
    std::cout << paciente.tempo_espera_fila << " ";
    std::cout << paciente.tempo_atendimento << std::endl;
}

std::string Gerenciador::tempoParaString(const Tempo& tempo) const {
    std::tm tm = {};
    
    tm.tm_year = tempo.ano - 1900;
    tm.tm_mon = tempo.mes - 1;
    tm.tm_mday = tempo.dia;
    tm.tm_hour = static_cast<int>(tempo.hora);
    float parte_hora = tempo.hora - tm.tm_hour;

    tm.tm_min = static_cast<int>(parte_hora * 60);
    tm.tm_sec = static_cast<int>((parte_hora * 60 - tm.tm_min) * 60);
    std::cerr << "Ano: " << tm.tm_year << ", Mês: " << tm.tm_mon << ", Dia: " << tm.tm_mday << std::endl;
    std::cerr << "Hora: " << tm.tm_hour << ", Minuto: " << tm.tm_min << ", Segundo: " << tm.tm_sec << std::endl;

    // Verificar se os valores estão corretos
    if (tm.tm_year < 0 || tm.tm_mon < 0 || tm.tm_mon > 11 || tm.tm_mday < 1 || tm.tm_mday > 31 ||
        tm.tm_hour < 0 || tm.tm_hour > 23 || tm.tm_min < 0 || tm.tm_min > 59 || tm.tm_sec < 0 || tm.tm_sec > 59) {
        std::cerr << "Erro ao converter Tempo para std::tm: valores inválidos" << std::endl;
        return "Invalid Time";
    }

    std::ostringstream oss;
    oss << std::put_time(&tm, "%a %b %d %H:%M:%S %Y");
    return oss.str();
}