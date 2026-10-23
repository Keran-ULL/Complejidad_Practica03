/**
 * @file cero.cc
 * @brief Implementacion de la funcion basica Cero.
 */

#include "cero.h"

/**
 * @brief Aridad de la funcion cero.
 */
std::size_t Cero::aridad() const {
  return 1;
}

/**
 * @brief Devuelve siempre 0.
 */
Natural Cero::calcular(const std::vector<Natural>&, Contador&) const {
  return 0;
}
