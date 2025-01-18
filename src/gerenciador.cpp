#include "../include/gerenciador.h"
#include <iostream>
#include <iomanip>
#include <ctime>

// A função recebe uma data e hora separadas em componentes e formata
// em uma string no formato "Dia_da_semana Mês Dia Hora:Minuto:Segundo Ano".
std::string formatarDataHora(int ano, int mes, int dia, float hora) {
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

// Calcula a data e hora de alta com base na data e hora de admissão e no tempo total de permanência.
std::string calcularDataHoraAlta(int ano, int mes, int dia, float hora_admissao, float tempo_total) {
    std::tm t = {};
    t.tm_year = ano - 1900;
    t.tm_mon = mes - 1;
    t.tm_mday = dia;
    t.tm_hour = static_cast<int>(hora_admissao);
    t.tm_min = static_cast<int>((hora_admissao - t.tm_hour) * 60);
    t.tm_sec = 0;

    // Adiciona o tempo total em segundos
    time_t tempo_admissao = std::mktime(&t);
    time_t tempo_alta = tempo_admissao + static_cast<time_t>(tempo_total * 3600);

    std::tm* t_alta = std::localtime(&tempo_alta);

    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", t_alta);
    return std::string(buffer);
}

// Lê dados de um arquivo e cria um objeto Hospital com base nesses dados.
// O tempo de atendimento de cada paciente é calculado com base nos tempos dos procedimentos e nas quantidades
// de medidas hospitalares, testes de laboratório, exames de imagem e instrumentos/medicamentos utilizados.
Hospital Gerenciador::ProcessarEntrada(FILE* Entrada) {
    float tempo;
    int n_unidades;
    Procedimentos procedimentos[6];
    for (int i = 0; i < 6; i++) {
        fscanf(Entrada, "%f %d", &tempo, &n_unidades);
        procedimentos[i] = Procedimentos(tempo, n_unidades);
    }

    fscanf(Entrada, "%d", &n_unidades);
    Paciente* pacientes = new Paciente[n_unidades];
    for (int i = 0; i < n_unidades; i++) {
        int id, alta, ano, mes, dia, grau_urgencia, medidas_hospitalares,
            testes_laboratorio, exames_imagem, instrumentos_medicamentos;
        float hora;

        fscanf(Entrada, "%d %d %d %d %d %f %d %d %d %d %d %d %f", 
               &id, &alta, &ano, &mes, &dia, &hora, &grau_urgencia,
               &medidas_hospitalares, &testes_laboratorio, &exames_imagem, &instrumentos_medicamentos);
        
        pacientes[i] = Paciente(id, alta, ano, mes, dia, hora, grau_urgencia, medidas_hospitalares,
                                testes_laboratorio, exames_imagem, instrumentos_medicamentos);

        pacientes[i].tempo_atendimento = procedimentos[2].tempo * pacientes[i].medidas_hospitalares + 
                                         procedimentos[3].tempo * pacientes[i].testes_laboratorio +
                                         procedimentos[4].tempo * pacientes[i].exames_imagem + 
                                         procedimentos[5].tempo * pacientes[i].instrumentos_medicamentos;
    }

    Hospital HZ = Hospital(procedimentos[0], procedimentos[1], procedimentos[2],
                           procedimentos[3], procedimentos[4], procedimentos[5],
                           pacientes, n_unidades);
    return HZ;
}

// Imprime a saída dos dados dos pacientes de um hospital.
void Gerenciador::ImprimirSaida(Hospital HZ) {
    for (int i = 0; i < HZ.populacao; ++i) {
        Paciente& paciente = HZ.pacientes[i];

        std::string data_admissao = formatarDataHora(paciente.ano, paciente.mes, paciente.dia, paciente.hora);
        std::string data_alta = calcularDataHoraAlta(paciente.ano, paciente.mes, paciente.dia, paciente.hora, paciente.tempo_total);

        std::cout << std::setfill('0') << std::setw(10) << paciente.id << " "
                  << data_admissao << " "
                  << data_alta << " "
                  << std::fixed << std::setprecision(2) << paciente.tempo_total << " "
                  << paciente.tempo_atendimento << " "
                  << paciente.tempo_espera << std::endl;
    }
}