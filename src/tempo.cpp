// #include "../include/tempo.h"

// Tempo Tempo::operator+(const Tempo& outro) const {
//     Tempo resultado;
//     resultado.hora = hora + outro.hora;
//     resultado.dia = dia + outro.dia + static_cast<int>(resultado.hora / 24);
//     resultado.hora = fmod(resultado.hora, 24);
//     resultado.mes = mes + outro.mes + static_cast<int>(resultado.dia / 30);
//     resultado.dia = resultado.dia % 30;
//     resultado.ano = ano + outro.ano + static_cast<int>(resultado.mes / 12);
//     resultado.mes = resultado.mes % 12;
//     return resultado;
// }

// Tempo Tempo::operator*(int multiplicador) const {
//     Tempo resultado;
//     resultado.hora = hora * multiplicador;
//     resultado.dia = dia * multiplicador + static_cast<int>(resultado.hora / 24);
//     resultado.hora = fmod(resultado.hora, 24);
//     resultado.mes = mes * multiplicador + static_cast<int>(resultado.dia / 30);
//     resultado.dia = resultado.dia % 30;
//     resultado.ano = ano * multiplicador + static_cast<int>(resultado.mes / 12);
//     resultado.mes = resultado.mes % 12;
//     return resultado;
// }

// float Tempo::toDecimal() const {
//     return ano * 365 * 24 + mes * 30 * 24 + dia * 24 + hora;
// }