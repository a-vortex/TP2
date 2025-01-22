#include "../include/auxiliar.h"

std::string Auxiliar::tempoParaString(std::tm &tempo)
{
    char buffer[80];
    // Formatar a data e hora no formato desejado
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", &tempo);
    return std::string(buffer);
}

std::tm Auxiliar::adicionarHoras(const std::tm &date, float hours)
{
    std::tm new_date = date;
    time_t original_time = mktime(&new_date);
    if (original_time == (time_t)-1)
    {
        char s[64] = {0};
        strftime(s, sizeof(s), "%c", &new_date);
        std::cerr << "Error: Invalid time value. " << s << std::endl;
        exit(EXIT_FAILURE);
    }

    original_time += static_cast<time_t>(hours * 3600);

    std::tm *updated_date = localtime(&original_time);
    if (updated_date == nullptr)
    {
        std::cerr << "Error: localtime conversion failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    return *updated_date;
}

float Auxiliar::diferenca(const std::tm &start, const std::tm &end)
{

    if (start.tm_year < 70 || start.tm_mon < 0 || start.tm_mday <= 0)
    {
        std::cerr << "Erro: Tempo inicial inválido." << std::endl;
        exit(EXIT_FAILURE);
    }
    time_t time_start = mktime(const_cast<std::tm *>(&start));
    time_t time_end = mktime(const_cast<std::tm *>(&end));

    if (time_start == (time_t)-1 || time_end == (time_t)-1)
    {
        std::cerr << "Error: Invalid time values." << std::endl;
        exit(EXIT_FAILURE);
    }

    double seconds_diff = difftime(time_end, time_start);
    return seconds_diff / 3600.0;
}

std::string Auxiliar::formatarDataHora(int ano, int mes, int dia, float hora)
{
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

std::tm Auxiliar::inicializaTm(int ano, int mes, int dia, float hora) {
    // Inicializar a estrutura std::tm para a data e hora de admissão
    std::tm tempo = {};
    tempo.tm_year = ano - 1900;
    tempo.tm_mon = mes - 1;
    tempo.tm_mday = dia;
    tempo.tm_hour = static_cast<int>(hora);
    tempo.tm_min = static_cast<int>((hora - static_cast<int>(hora)) * 60);
    tempo.tm_sec = 0;
    tempo.tm_isdst = -1;
    mktime(&tempo);
    return tempo;
}

std::tm Auxiliar::inicializaTm() {
    // Inicializar a estrutura std::tm para a data e hora de admissão
    std::tm tempo = {};
    tempo.tm_year = 0;
    tempo.tm_mon = 0;
    tempo.tm_mday = 0;
    tempo.tm_hour = 0;
    tempo.tm_min = 0;
    tempo.tm_sec = 0;
    tempo.tm_isdst = -1;
    mktime(&tempo);
    return tempo;
}