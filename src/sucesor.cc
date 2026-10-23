/**
 * @file sucesor.cc
 * @brief Implementacion de la funcion basica Sucesor.
 */

#include "sucesor.h"

/**
 * @brief Aridad de la funcion sucesor.
 */
std::size_t Sucesor::aridad() const {
  return 1;
}

/**
 * @brief Devuelve x + 1.
 */
Natural Sucesor::calcular(const std::vector<Natural>& argumentos, Contador&) const {
  return argumentos[0] + 1;
}
