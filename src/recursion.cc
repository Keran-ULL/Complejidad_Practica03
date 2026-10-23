/**
 * @file recursion.cc
 * @brief Implementacion de la operacion de recursion primitiva.
 */

#include "recursion.h"

#include <string>
#include <utility>

#include "errores.h"

/**
 * @brief Construye la recursion y valida las aridades de g y h.
 */
Recursion::Recursion(FuncionPtr funcionBase, FuncionPtr funcionPaso)
    : base(std::move(funcionBase)), paso(std::move(funcionPaso)) {
  if (!base || !paso) {
    throw ErrorAridad("Recursion invalida: faltan la funcion base o la funcion paso");
  }
  if (paso->aridad() != base->aridad() + 2) {
    throw ErrorAridad("Recursion invalida: la funcion base tiene aridad " +
                      std::to_string(base->aridad()) + " y la funcion paso " +
                      std::to_string(paso->aridad()) + " (deberia ser " +
                      std::to_string(base->aridad() + 2) + ")");
  }
}

/**
 * @brief Aridad de la funcion: la de la base mas uno (el argumento y).
 */
std::size_t Recursion::aridad() const {
  return base->aridad() + 1;
}

/**
 * @brief Caso base si y es 0; en otro caso, llamada recursiva con y-1 y
 *        aplicacion de la funcion paso.
 */
Natural Recursion::calcular(const std::vector<Natural>& argumentos, Contador& contador) const {
  const Natural y = argumentos.back();

  if (y == 0) {
    const std::vector<Natural> parametrosBase(argumentos.begin(), argumentos.end() - 1);
    return base->evaluar(parametrosBase, contador);
  }

  // Parametros del paso: (x_1..x_n, y-1, f(x_1..x_n, y-1)).
  std::vector<Natural> parametrosPaso = argumentos;
  parametrosPaso.back() = y - 1;
  const Natural anterior = evaluar(parametrosPaso, contador);
  parametrosPaso.push_back(anterior);
  return paso->evaluar(parametrosPaso, contador);
}
