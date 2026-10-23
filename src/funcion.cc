/**
 * @file funcion.cc
 * @brief Implementacion de la clase Funcion.
 */

#include "funcion.h"

#include <string>

#include "errores.h"

/**
 * @brief Comprueba la aridad, anota la llamada y delega en calcular().
 */
Natural Funcion::evaluar(const std::vector<Natural>& argumentos, Contador& contador) const {
  if (argumentos.size() != aridad()) {
    throw ErrorAridad("La funcion espera " + std::to_string(aridad()) +
                      " argumento(s) y se han dado " + std::to_string(argumentos.size()));
  }
  contador.incrementar();
  return calcular(argumentos, contador);
}
