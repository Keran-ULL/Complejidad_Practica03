#ifndef NATURAL_H
#define NATURAL_H

/**
 * @file natural.h
 * @brief Tipo utilizado para representar los numeros naturales.
 */

/**
 * @brief Numero natural (0, 1, 2, ...). Se usa un entero sin signo de 64
 *        bits.
 *
 * Nota: el tiempo de calculo crece al menos linealmente con el resultado
 * (todo valor se obtiene sumando de uno en uno con la funcion sucesor),
 * por lo que en la practica nunca se llega a desbordar este tipo.
 */
using Natural = unsigned long long;

#endif  
