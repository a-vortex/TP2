#include "../include/simulador.h"
#include <iostream> 

Simulador::~Simulador() {
    while (!eventos.vazio()) {
        delete eventos.remover();
    }
}

void Simulador::adicionarEvento(Evento* evento) {
    eventos.adicionar(evento);
    std::cout << "Evento adicionado: tipo=" << evento->tipo << ", tempo=" << tempo_atual.ano << " "<< tempo_atual.mes << " " << tempo_atual.dia << " " << tempo_atual.hora << std::endl;
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
                    Tempo tempo_procedimento = procedimento->tempo;
                    Tempo tempoatual = tempo_atual + tempo_procedimento;
                    Evento* novo_evento = new Evento(ATENDIMENTO, tempoatual, paciente);
                    adicionarEvento(novo_evento);
                    std::cout << "Novo evento de atendimento criado para o paciente " << paciente->id << " atendimento: " << procedimento << " previsto para acabar" << tempo_atual.ano << " "<< tempo_atual.mes << " " << tempo_atual.dia << " " << tempo_atual.hora << std::endl;
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

    std::cout << "Processando chegada: paciente=" << evento->paciente->id << ", tempo=" << tempo_atual.ano << " "<< tempo_atual.mes << " " << tempo_atual.dia << " " << tempo_atual.hora << std::endl;

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
        Evento* novo_evento = new Evento(SAIDA, evento->momento , paciente);
        adicionarEvento(novo_evento);
        std::cout << "Paciente " << paciente->id << " concluiu todos os procedimentos. Evento de saída criado." << std::endl;
    } else {
        // Verificar a fila dos procedimentos que o paciente ainda precisa fazer e colocá-lo na menor
        Fila* menor_fila = nullptr;
        Procedimentos* procedimento_selecionado = nullptr;
        Tempo menor_tempo_espera = {9999, 0, 0, 0}; // Inicializar com um valor grande
        int menor_indice = -1; // Inicializar com um valor inválido

        auto calcularTempoEspera = [](Procedimentos* proc, int grau_urgencia) -> Tempo {
            int num_pacientes_vermelha = proc->getVermelha().tamanho;
            int num_pacientes_amarela = proc->getAmarela().tamanho;
            int num_pacientes_verde = proc->getVerde().tamanho;
            Tempo tempo_espera = {0, 0, 0, 0};

            switch (grau_urgencia) {
                case 0: // Verde
                    tempo_espera = proc->tempo * (num_pacientes_vermelha + num_pacientes_amarela + num_pacientes_verde);
                    break;
                case 1: // Amarela
                    tempo_espera = proc->tempo * (num_pacientes_vermelha + num_pacientes_amarela);
                    break;
                case 2: // Vermelha
                    tempo_espera = proc->tempo * num_pacientes_vermelha;
                    break;
            }
            return tempo_espera;
        };

        auto verificarFila = [&](Procedimentos* proc, int indice) {
            Tempo tempo_espera = calcularTempoEspera(proc, paciente->grau_urgencia);
            if (tempo_espera.toDecimal() < menor_tempo_espera.toDecimal() || 
                (tempo_espera.toDecimal() == menor_tempo_espera.toDecimal() && (menor_indice == -1 || indice < menor_indice))) {
                menor_tempo_espera = tempo_espera;
                menor_fila = (paciente->grau_urgencia == 0) ? &proc->getVerde() :
                             (paciente->grau_urgencia == 1) ? &proc->getAmarela() : &proc->getVermelha();
                procedimento_selecionado = proc;
                menor_indice = indice;
            }
        };

        if (paciente->medidas_hospitalares > 0) {
            verificarFila(&hospital->Medidas, 0);
        }
        if (paciente->testes_laboratorio > 0) {
            verificarFila(&hospital->Testes, 1);
        }
        if (paciente->exames_imagem > 0) {
            verificarFila(&hospital->Imagem, 2);
        }
        if (paciente->instrumentos_medicamentos > 0) {
            verificarFila(&hospital->Instrumentos, 3);
        }

        if (menor_fila != nullptr) {
            menor_fila->Enfileira(*paciente);
            std::cout << "Paciente " << paciente->id << " foi colocado na fila do procedimento " << procedimento_selecionado->nome << " com tempo de espera " << menor_tempo_espera.toDecimal() << std::endl;
        }
    }
}

void Simulador::processarSaida(Evento* evento) {
    Paciente* paciente = evento->paciente;
    std::cout << "Processando saída: paciente=" << paciente->id << " tempoalta:"<< tempo_atual.ano << " "<< tempo_atual.mes << " " << tempo_atual.dia << " " << tempo_atual.hora << "   TEMPO CHEGADA " << paciente->tempo_admissao.ano << " " << paciente->tempo_admissao.mes << " " << paciente->tempo_admissao.dia << " "<< paciente->tempo_admissao.hora<< std::endl;

    // Atualizar o tempo de saída do paciente
    paciente->tempo_saida = tempo_atual;

    // Calcular o tempo total que o paciente passou no hospital
    float tempo_total_hospital = tempo_atual.toDecimal() - paciente->tempo_admissao.toDecimal();

    // Calcular o tempo de espera na fila
    paciente->tempo_espera_fila = tempo_total_hospital - paciente->tempo_atendimento;

    // Atualizar o tempo total do paciente
    paciente->tempo_total = tempo_total_hospital;
    std::cout << "Paciente " << paciente->id << " saiu do hospital. Tempo total: " << paciente->tempo_total << std::endl;
    std::cout << "Tempo de espera na fila: " << paciente->tempo_espera_fila << std::endl;
    std::cout << "Tempo de atendimento: " << paciente->tempo_atendimento << std::endl;
    std::cout << "TEMPO CHEGADA " << paciente->tempo_admissao.ano << " " << paciente->tempo_admissao.mes << " " << paciente->tempo_admissao.dia << " "<< paciente->tempo_admissao.hora<< std::endl;
    std::cout << "TEMPO SAIDA " << paciente->tempo_saida.ano << " " << paciente->tempo_saida.mes << " " << paciente->tempo_saida.dia << " "<< paciente->tempo_saida.hora<< std::endl;
}