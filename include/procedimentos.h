#ifndef PROCEDIMENTOS_H
#define PROCEDIMENTOS_H

#include "fila.h"

//Tad responsavel por armazenar as informações dos procedimentos, com suas respectivas filas.
class Procedimentos {

    public:

        float tempo;
        int n_unidades;

        float tempo_ocioso;
        float tempo_util;

        float tempo_espera_vermelha = 0;
        float tempo_espera_amarela = 0;
        float tempo_espera_verde = 0;

        Fila* vermelha;
        Fila* amarela;
        Fila* verde;

        Procedimentos(){};
        Procedimentos(float tempo, int n_unidades) : tempo(tempo), n_unidades(n_unidades) {
            vermelha = new Fila();
            amarela = new Fila();
            verde = new Fila();
            tempo_ocioso = 0;
            tempo_util = 0;
        }
        ~Procedimentos() {
            vermelha->~Fila();
            amarela->~Fila();
            verde->~Fila();
        }

};

#endif // PROCEDIMENTOS_H