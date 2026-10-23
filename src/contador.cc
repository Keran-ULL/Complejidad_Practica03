/**
 * @file contador.cc
 * @brief Implementacion de la clase Contador.
 */

#include "contador.h"

/**
 * @brief Construye un contador a cero.
 */
Contador::Contador() : llamadas(0) {}

/**
 * @brief Anota una llamada mas.
 */
void Contador::incrementar() {
  ++llamadas;
}

/**
 * @brief Devuelve el numero de llamadas anotadas.
 */
unsigned long long Contador::getLlamadas() const {
  return llamadas;
}
