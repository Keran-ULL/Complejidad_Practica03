/**
 * @file producto.cc
 * @brief Implementacion de la funcion primitiva recursiva Producto.
 */

#include "producto.h"

#include <memory>
#include <vector>

#include "cero.h"
#include "composicion.h"
#include "proyeccion.h"
#include "suma.h"

/**
 * @brief Construye el producto a partir de su base y su paso.
 */
Producto::Producto() : Recursion(crearBase(), crearPaso()) {}

/**
 * @brief g(x) = Z(pi_1^1(x)).
 */
FuncionPtr Producto::crearBase() {
  return std::make_shared<Composicion>(
      std::make_shared<Cero>(),
      std::vector<FuncionPtr>{std::make_shared<Proyeccion>(1, 1)});
}

/**
 * @brief h(x, y, r) = suma(pi_1^3(x, y, r), pi_3^3(x, y, r)).
 */
FuncionPtr Producto::crearPaso() {
  return std::make_shared<Composicion>(
      std::make_shared<Suma>(),
      std::vector<FuncionPtr>{std::make_shared<Proyeccion>(1, 3),
                              std::make_shared<Proyeccion>(3, 3)});
}
