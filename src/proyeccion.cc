/**
 * @file proyeccion.cc
 * @brief Implementacion de la funcion basica Proyeccion.
 */

#include "proyeccion.h"

#include <string>

#include "errores.h"

/**
 * @brief Construye la proyeccion, validando que 1 <= indice <= total.
 */
Proyeccion::Proyeccion(std::size_t indice, std::size_t total) : indice(indice), total(total) {
  if (indice < 1 || indice > total) {
    throw ErrorAridad("Proyeccion invalida: el indice " + std::to_string(indice) +
                      " no esta entre 1 y " + std::to_string(total));
  }
}

/**
 * @brief Aridad de la proyeccion.
 */
std::size_t Proyeccion::aridad() const {
  return total;
}

/**
 * @brief Devuelve el argumento de posicion indice (contando desde 1).
 */
Natural Proyeccion::calcular(const std::vector<Natural>& argumentos, Contador&) const {
  return argumentos[indice - 1];
}
