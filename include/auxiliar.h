#ifndef AUXILIAR
#define AUXILIAR

#include <string>
#include <ctime>
#include <iostream>

class Auxiliar{
    public:
        // Função que converte um tempo em horas para uma string no formato "dd/mm/aaaa hh:mm"
        static std::string tempoParaString(std::tm &tempo);

        // Função que adiciona uma quantidade de horas a uma data
        static std::tm adicionarHoras(const std::tm& date, float hours);

        // Função que calcula a diferença de tempo em horas entre duas datas
        static float diferenca(const std::tm &start, const std::tm &end);

        // Função que formata a data e hora
        static std::string formatarDataHora(int ano, int mes, int dia, float hora);

        // Função que inicializa uma estrutura tm
        static std::tm inicializaTm(int ano = 0, int mes = 0, int dia = 0, float hora = 0);
        static std::tm inicializaTm();
};

#endif // AUXILIAR