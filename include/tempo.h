#ifndef TEMPO_H
#define TEMPO_H

#include <cmath>

struct Tempo {
    int ano;
    int mes;
    int dia;
    float hora; // Hora em decimal (ex: 14.5 para 14h30m)

    Tempo() : ano(0), mes(0), dia(0), hora(0.0f) {}
    Tempo(int ano, int mes, int dia, float hora) : ano(ano), mes(mes), dia(dia), hora(hora) {}

    Tempo operator+(const Tempo& outro) const;
    Tempo operator*(int multiplicador) const;
    float toDecimal() const;
};

#endif // TEMPO_H