#include "../include/simulador.h"
#include <iostream>
#include <iomanip>
#include <ctime>

Simulador::~Simulador() {
    while (!eventos.vazio()) {
        delete eventos.remover();
    }
}

void Simulador::adicionarEvento(Evento* evento) {
    eventos.adicionar(evento);
    std::cout << "Evento adicionado: tipo=" << evento->tipo << ", tempo=" << tempo_atual.tm_year + 1900 << " " << tempo_atual.tm_mon + 1 << " " << tempo_atual.tm_mday << " " << tempo_atual.tm_hour << std::endl;
}

void Simulador::executar() {
    while (!eventos.vazio() || !hospital->Triagem.getVerde().Vazia() || !hospital->Triagem.getAmarela().Vazia() || !hospital->Triagem.getVermelha().Vazia()
                            || !hospital->Atendimento.getVerde().Vazia() || !hospital->Atendimento.getAmarela().Vazia() || !hospital->Atendimento.getVermelha().Vazia() 
                            || !hospital->Medidas.getVerde().Vazia() || !hospital->Medidas.getAmarela().Vazia() || !hospital->Medidas.getVermelha().Vazia()
                            || !hospital->Testes.getVerde().Vazia() || !hospital->Testes.getAmarela().Vazia() || !hospital->Testes.getVermelha().Vazia()
                            || !hospital->Imagem.getVerde().Vazia() || !hospital->Imagem.getAmarela().Vazia() || !hospital->Imagem.getVermelha().Vazia()
                            || !hospital->Instrumentos.getVerde().Vazia() || !hospital->Instrumentos.getAmarela().Vazia() || !hospital->Instrumentos.getVermelha().Vazia()) {
        if (!eventos.vazio()) {
            Evento* evento_atual = eventos.remover();
            tempo_atual = evento_atual->momento;
            processarEvento(evento_atual);
            delete evento_atual;
        }

        for (Procedimentos* procedimento : {&hospital->Triagem, &hospital->Atendimento, &hospital->Medidas, &hospital->Testes, &hospital->Imagem, &hospital->Instrumentos}) {
            for (Fila* fila : {&procedimento->getVermelha(), &procedimento->getAmarela(), &procedimento->getVerde()}) {
                while (!fila->Vazia() && procedimento->n_unidades > 0) {
                    Paciente* paciente = fila->Desenfileira();
                    procedimento->n_unidades--;
                    std::tm tempo_procedimento = addHours(tempo_atual, procedimento->tempo);
                    Evento* novo_evento = new Evento(ATENDIMENTO, tempo_procedimento, paciente);
                    adicionarEvento(novo_evento);
                    std::cout << "Novo evento de atendimento criado para o paciente " << paciente->id << " atendimento: " << procedimento << " previsto para acabar" << tempo_procedimento.tm_year + 1900 << " " << tempo_procedimento.tm_mon + 1 << " " << tempo_procedimento.tm_mday << " " << tempo_procedimento.tm_hour << std::endl;
                    switch (procedimento->nome)
                    {
                    case 0:
                        paciente->estado = 3;
                        break;
                    case 1:
                        paciente->estado = 5;
                        break;
                    case 2:
                        paciente->estado = 7;
                        break;
                    case 3:
                        paciente->estado = 9;
                        break;
                    case 4:
                        paciente->estado = 11;
                        break;
                    case 5:
                        paciente->estado = 13;
                        break;
                    }
                }
            }
        }
    }
}

void Simulador::processarEvento(Evento* evento) {
    std::cout << "Processando evento: tipo=" << evento->tipo << std::endl;
    switch (evento->tipo) {
        case CHEGADA:
            processarChegada(evento);
            break;
        case ATENDIMENTO:
            processarAtendimento(evento);
            break;
        case SAIDA:
            processarSaida(evento);
            break;
    }
}

void Simulador::processarChegada(Evento* evento) {

    std::cout << "Processando chegada: paciente=" << evento->paciente->id << ", tempo=" << tempo_atual.tm_year + 1900 << " "<< tempo_atual.tm_mon + 1 << " " << tempo_atual.tm_mday << " " << tempo_atual.tm_hour << std::endl;

    hospital->Triagem.getVermelha().Enfileira(*evento->paciente);

    evento->paciente->estado = 2;

}

void Simulador::processarAtendimento(Evento* evento) {
    Paciente* paciente = evento->paciente;
    std::cout << "Processando atendimento: paciente=" << paciente->id << std::endl;

    switch (paciente->estado)
    {
    case 3:
        hospital->Triagem.n_unidades++;
        break;
    case 5:
        paciente->instrumentos_medicamentos--;
        hospital->Atendimento.n_unidades++;
        break;
    case 7:
        paciente->medidas_hospitalares--;
        hospital->Medidas.n_unidades++;
        break;
    case 9:
        paciente->testes_laboratorio--;
        hospital->Testes.n_unidades++;
        break;
    case 11:
        paciente->exames_imagem--;
        hospital->Imagem.n_unidades++;
        break;
    case 13:
        paciente->instrumentos_medicamentos--;
        hospital->Instrumentos.n_unidades++;
        break;
    }

    // Verificar se o paciente já realizou todos os procedimentos
    bool todos_procedimentos_realizados = (paciente->medidas_hospitalares == 0 &&
                                           paciente->testes_laboratorio == 0 &&
                                           paciente->exames_imagem == 0 &&
                                           paciente->instrumentos_medicamentos == 0);

    if (todos_procedimentos_realizados || paciente->alta) {
        // Criar um novo evento de saída para o paciente
        Evento* novo_evento = new Evento(SAIDA, evento->momento, paciente);
        adicionarEvento(novo_evento);
        std::cout << "Paciente " << paciente->id << " concluiu todos os procedimentos. Evento de saída criado." << std::endl;
    } else {
        // Verificar a fila dos procedimentos que o paciente ainda precisa fazer e colocá-lo na menor fila
        if (paciente->medidas_hospitalares > 0) {
            hospital->Medidas.getVerde().Enfileira(*paciente);
        } else if (paciente->testes_laboratorio > 0) {
            hospital->Testes.getVerde().Enfileira(*paciente);
        } else if (paciente->exames_imagem > 0) {
            hospital->Imagem.getVerde().Enfileira(*paciente);
        } else if (paciente->instrumentos_medicamentos > 0) {
            hospital->Instrumentos.getVerde().Enfileira(*paciente);
        }
    }
}

double Simulador::getElapsedHours(const std::tm& start, const std::tm& end) const {
    time_t time_start = mktime(const_cast<std::tm*>(&start));
    time_t time_end = mktime(const_cast<std::tm*>(&end));

    if (time_start == (time_t)-1 || time_end == (time_t)-1) {
        std::cerr << "Error: Invalid time values." << std::endl;
        exit(EXIT_FAILURE);
    }

    double seconds_diff = difftime(time_end, time_start);
    return seconds_diff / 3600.0;
}

void Simulador::processarSaida(Evento* evento) {
    Paciente* paciente = evento->paciente;
    std::cout << "Processando saída: paciente=" << paciente->id << " tempoalta:" << tempo_atual.tm_year + 1900 << " " << tempo_atual.tm_mon + 1 << " " << tempo_atual.tm_mday << " " << tempo_atual.tm_hour << "   TEMPO CHEGADA " << paciente->tempo_admissao.tm_year + 1900 << " " << paciente->tempo_admissao.tm_mon + 1 << " " << paciente->tempo_admissao.tm_mday << " " << paciente->tempo_admissao.tm_hour << std::endl;

    // Calcular o tempo total que o paciente passou no hospital
    float tempo_total_hospital = getElapsedHours(paciente->tempo_admissao, tempo_atual);

    // Atualizar o tempo de saída do paciente
    paciente->tempo_saida = addHours(paciente->tempo_admissao, tempo_total_hospital);

    // Calcular o tempo de espera na fila
    paciente->tempo_espera_fila = tempo_total_hospital - paciente->tempo_atendimento;

    // Atualizar o tempo total do paciente
    paciente->tempo_total = tempo_total_hospital;
    std::cout << "Paciente " << paciente->id << " saiu do hospital. Tempo total: " << paciente->tempo_total << std::endl;
    std::cout << "Tempo de espera na fila: " << paciente->tempo_espera_fila << std::endl;
    std::cout << "Tempo de atendimento: " << paciente->tempo_atendimento << std::endl;
    std::cout << "TEMPO CHEGADA " << paciente->tempo_admissao.tm_year + 1900 << " " << paciente->tempo_admissao.tm_mon + 1 << " " << paciente->tempo_admissao.tm_mday << " " << paciente->tempo_admissao.tm_hour << std::endl;
    std::cout << "TEMPO SAIDA " << paciente->tempo_saida.tm_year + 1900 << " " << paciente->tempo_saida.tm_mon + 1 << " " << paciente->tempo_saida.tm_mday << " " << paciente->tempo_saida.tm_hour << std::endl;
}

std::tm Simulador::addHours(const std::tm& date, float hours) const {
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