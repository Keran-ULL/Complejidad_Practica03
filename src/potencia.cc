/**
 * @file potencia.cc
 * @brief Implementacion de la funcion primitiva recursiva Potencia.
 */

#include "potencia.h"

#include <memory>
#include <vector>

#include "cero.h"
#include "composicion.h"
#include "producto.h"
#include "proyeccion.h"
#include "sucesor.h"

/**
 * @brief Construye la potencia a partir de su base y su paso.
 */
Potencia::Potencia() : Recursion(crearBase(), crearPaso()) {}

/**
 * @brief g(x) = S(Z(pi_1^1(x))), que vale siempre 1.
 */
FuncionPtr Potencia::crearBase() {
  const FuncionPtr cero = std::make_shared<Composicion>(
      std::make_shared<Cero>(),
      std::vector<FuncionPtr>{std::make_shared<Proyeccion>(1, 1)});
  return std::make_shared<Composicion>(std::make_shared<Sucesor>(),
                                       std::vector<FuncionPtr>{cero});
}

/**
 * @brief h(x, y, r) = producto(pi_1^3(x, y, r), pi_3^3(x, y, r)).
 */
FuncionPtr Potencia::crearPaso() {
  return std::make_shared<Composicion>(
      std::make_shared<Producto>(),
      std::vector<FuncionPtr>{std::make_shared<Proyeccion>(1, 3),
                              std::make_shared<Proyeccion>(3, 3)});
}
