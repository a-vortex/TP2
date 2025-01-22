#include "../include/gerenciador.h"

// Lê dados de um arquivo e cria um objeto Hospital com base nesses dados.
// O tempo de atendimento de cada paciente é calculado com base nos tempos dos procedimentos e nas quantidades
// de medidas hospitalares, testes de laboratório, exames de imagem e instrumentos/medicamentos utilizados.
Hospital* Gerenciador::ProcessarEntrada(FILE* Entrada)
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

    Paciente** pacientes = new Paciente*[n_unidades];
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

        std::tm admissao = Auxiliar::inicializaTm(ano, mes, dia, hora);

        pacientes[i] = new Paciente(id, alta, admissao, grau_urgencia, medidas_hospitalares, testes_laboratorio, exames_imagem, instrumentos_medicamentos);

        if (pacientes[i]->alta == 1) {

            pacientes[i]->tempo_atendimento=procedimentos[0].tempo + procedimentos[1].tempo;
            continue;

        } else {

            pacientes[i]->tempo_atendimento=procedimentos[0].tempo + 
                                            procedimentos[1].tempo + 
                                            (procedimentos[2].tempo * pacientes[i]->medidas_hospitalares) + 
                                            (procedimentos[3].tempo * pacientes[i]->testes_laboratorio) +
                                            (procedimentos[4].tempo * pacientes[i]->exames_imagem) + 
                                            (procedimentos[5].tempo * pacientes[i]->instrumentos_medicamentos);
        
        }

    }
    return new Hospital(procedimentos[0], procedimentos[1], procedimentos[2], 
                        procedimentos[3], procedimentos[4], procedimentos[5], 
                        pacientes, n_unidades);
}

void Gerenciador::imprimirSaida(Paciente** pacientes, int populacao) {
    for (int i = 0; i < populacao; i++) {
        Paciente* paciente = pacientes[i];

        // Converter os tempos para strings formatadas
        std::string admissao_str = Auxiliar::tempoParaString(paciente->tempo_admissao);
        std::string saida_str = Auxiliar::tempoParaString(paciente->tempo_saida);

        // Imprimir os dados formatados
        std::cout << paciente->id << " ";
        std::cout << admissao_str << " ";
        std::cout << saida_str << " ";
        std::cout << std::fixed << std::setprecision(2) << paciente->tempo_total << " ";
        std::cout << std::setprecision(2) << paciente->tempo_atendimento << " ";
        std::cout << std::setprecision(2) << paciente->tempo_espera_fila << std::endl;
    }
}