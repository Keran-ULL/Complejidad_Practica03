/**
 * @file suma.cc
 * @brief Implementacion de la funcion primitiva recursiva Suma.
 */

#include "suma.h"

#include <memory>
#include <vector>

#include "composicion.h"
#include "proyeccion.h"
#include "sucesor.h"

/**
 * @brief Construye la suma a partir de su base y su paso.
 */
Suma::Suma() : Recursion(crearBase(), crearPaso()) {}

/**
 * @brief g(x) = pi_1^1(x).
 */
FuncionPtr Suma::crearBase() {
  return std::make_shared<Proyeccion>(1, 1);
}

/**
 * @brief h(x, y, r) = S(pi_3^3(x, y, r)).
 */
FuncionPtr Suma::crearPaso() {
  return std::make_shared<Composicion>(
      std::make_shared<Sucesor>(),
      std::vector<FuncionPtr>{std::make_shared<Proyeccion>(3, 3)});
}
