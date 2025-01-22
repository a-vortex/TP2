#include "../include/simulador.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>

Simulador::~Simulador()
{
    while (!eventos.vazio())
    {
        delete eventos.remover();
    }
}

void Simulador::adicionarEvento(Evento *evento)
{
    eventos.adicionar(evento);
}

void Simulador::executar()
{
    while (temEventoOuFila()) 
    {
        if (!eventos.vazio())
        {
            Evento *evento_atual = eventos.remover();
            tempo_atual = evento_atual->momento;
            switch (evento_atual->tipo){
                case CHEGADA:
                    processarChegada(evento_atual);
                    break;
                case ATENDIMENTO:
                    processarAtendimento(evento_atual);
                    break;
                case SAIDA:
                    processarSaida(evento_atual);
                    break;
            }
            delete evento_atual;
        }

        for (Procedimentos *procedimento : {&hospital->Triagem, &hospital->Atendimento, &hospital->Medidas, &hospital->Testes, &hospital->Imagem, &hospital->Instrumentos})
        {
            for (Fila *fila : {&procedimento->getVermelha(), &procedimento->getAmarela(), &procedimento->getVerde()})
            {
                while (!fila->Vazia() && procedimento->n_unidades > 0)
                {
                    Paciente *paciente = fila->Desenfileira();
                    procedimento->n_unidades--;
                    std::tm tempo_procedimento = Auxiliar::adicionarHoras(tempo_atual, procedimento->tempo);
                    Evento *novo_evento = new Evento(ATENDIMENTO, tempo_procedimento, paciente);
                    adicionarEvento(novo_evento);
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

void Simulador::processarChegada(Evento *evento)
{
    hospital->Triagem.getVermelha().Enfileira(evento->paciente);
    evento->paciente->estado = 2;
}

void Simulador::processarAtendimento(Evento *evento)
{
    Paciente* paciente = evento->paciente;
    switch (paciente->estado)
    {
    case 3:
        hospital->Triagem.n_unidades++;
        break;
    case 5:
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
    bool todos_procedimentos_realizados=(paciente->medidas_hospitalares == 0 &&
                                        paciente->testes_laboratorio == 0 &&
                                        paciente->exames_imagem == 0 &&
                                        paciente->instrumentos_medicamentos == 0);
    if(paciente->estado == 3)
    {
        paciente->estado = 4;
        switch (paciente->grau_urgencia)
        {
        case 0:
            hospital->Atendimento.getVerde().Enfileira(paciente);
            break;
        case 1:
            hospital->Atendimento.getAmarela().Enfileira(paciente);
            break;
        case 2:
            hospital->Atendimento.getVermelha().Enfileira(paciente);
            break;
        }

    }else if (todos_procedimentos_realizados || paciente->alta)
    {
        // Criar um novo evento de saída para o paciente
        Evento *novo_evento = new Evento(SAIDA, evento->momento, paciente);
        adicionarEvento(novo_evento);
    }
    else
    {
        // Verificar a fila dos procedimentos que o paciente ainda precisa fazer
        if (paciente->medidas_hospitalares > 0)
        {
            if (paciente->grau_urgencia == 0)
            {
                hospital->Medidas.getVerde().Enfileira(paciente);
            }
            else if (paciente->grau_urgencia == 1)
            {
                hospital->Medidas.getAmarela().Enfileira(paciente);
            }
            else if (paciente->grau_urgencia == 2)
            {
                hospital->Medidas.getVermelha().Enfileira(paciente);
            }
            paciente->estado = 6;
        }
        else if (paciente->testes_laboratorio > 0)
        {
            if (paciente->grau_urgencia == 0)
            {
                hospital->Testes.getVerde().Enfileira(paciente);
            }
            else if (paciente->grau_urgencia == 1)
            {
                hospital->Testes.getAmarela().Enfileira(paciente);
            }
            else if (paciente->grau_urgencia == 2)
            {
                hospital->Testes.getVermelha().Enfileira(paciente);
            }
            paciente->estado = 8;
        }
        else if (paciente->exames_imagem > 0)
        {
            if (paciente->grau_urgencia == 0)
            {
                hospital->Imagem.getVerde().Enfileira(paciente);
            }
            else if (paciente->grau_urgencia == 1)
            {
                hospital->Imagem.getAmarela().Enfileira(paciente);
            }
            else if (paciente->grau_urgencia == 2)
            {
                hospital->Imagem.getVermelha().Enfileira(paciente);
            }
            paciente->estado = 10;
        }
        else if (paciente->instrumentos_medicamentos > 0)
        {
            if (paciente->grau_urgencia == 0)
            {
                hospital->Instrumentos.getVerde().Enfileira(paciente);
            }
            else if (paciente->grau_urgencia == 1)
            {
                hospital->Instrumentos.getAmarela().Enfileira(paciente);
            }
            else if (paciente->grau_urgencia == 2)
            {
                hospital->Instrumentos.getVermelha().Enfileira(paciente);
            }
            paciente->estado = 12;
        }
    }
}
void Simulador::processarSaida(Evento *evento)
{
    Paciente *paciente = evento->paciente;

    // Calcular o tempo total que o paciente passou no hospital
    paciente->tempo_total = Auxiliar::diferenca(paciente->tempo_admissao, tempo_atual);
    
    // Atualizar o tempo de saída do paciente
    paciente->tempo_saida = tempo_atual;

    // Calcular o tempo de espera na fila
    paciente->tempo_espera_fila = paciente->tempo_total - paciente->tempo_atendimento;

    // Arredondar o tempo de espera na fila para 2 casas decimais
    paciente->tempo_espera_fila = std::round(paciente->tempo_espera_fila * 100.0) / 100.0;

    if (std::fabs(paciente->tempo_espera_fila) < 1e-6)
    {
        paciente->tempo_espera_fila = 0;
    }
}

bool Simulador::temEventoOuFila() const {
    return (!eventos.vazio() || !hospital->Triagem.getVermelha().Vazia() 
                            || !hospital->Atendimento.getVerde().Vazia() || !hospital->Atendimento.getAmarela().Vazia() || !hospital->Atendimento.getVermelha().Vazia()    
                            || !hospital->Medidas.getVerde().Vazia() || !hospital->Medidas.getAmarela().Vazia() || !hospital->Medidas.getVermelha().Vazia() 
                            || !hospital->Testes.getVerde().Vazia() || !hospital->Testes.getAmarela().Vazia() || !hospital->Testes.getVermelha().Vazia() 
                            || !hospital->Imagem.getVerde().Vazia() || !hospital->Imagem.getAmarela().Vazia() || !hospital->Imagem.getVermelha().Vazia() 
                            || !hospital->Instrumentos.getVerde().Vazia() || !hospital->Instrumentos.getAmarela().Vazia() || !hospital->Instrumentos.getVermelha().Vazia());
}