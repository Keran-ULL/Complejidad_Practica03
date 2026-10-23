#ifndef PRODUCTO_H
#define PRODUCTO_H

#include "recursion.h"

/**
 * @file producto.h
 * @brief Declaracion de la funcion primitiva recursiva Producto.
 */

/**
 * @class Producto
 * @brief producto(x, y) = x * y, de aridad 2.
 *
 * Definida por recursion primitiva a partir de la suma:
 *   producto(x, 0)   = Z(pi_1^1(x))
 *   producto(x, y+1) = suma(pi_1^3(x, y, r), pi_3^3(x, y, r)),
 *                      con r = producto(x, y)
 */
class Producto : public Recursion {
public:
  /**
   * @brief Construye la funcion producto.
   */
  Producto();

private:
  /**
   * @brief Construye la funcion base g(x) = Z(pi_1^1(x)).
   * @return La funcion base.
   */
  static FuncionPtr crearBase();

  /**
   * @brief Construye la funcion paso h(x, y, r) = suma(x, r).
   * @return La funcion paso.
   */
  static FuncionPtr crearPaso();
};

#endif  // PRODUCTO_H
