#ifndef SUMA_H
#define SUMA_H

#include "recursion.h"

/**
 * @file suma.h
 * @brief Declaracion de la funcion primitiva recursiva Suma.
 */

/**
 * @class Suma
 * @brief suma(x, y) = x + y, de aridad 2.
 *
 * Definida por recursion primitiva:
 *   suma(x, 0)   = pi_1^1(x)
 *   suma(x, y+1) = S(pi_3^3(x, y, suma(x, y)))
 */
class Suma : public Recursion {
public:
  /**
   * @brief Construye la funcion suma.
   */
  Suma();

private:
  /**
   * @brief Construye la funcion base g(x) = pi_1^1(x).
   * @return La funcion base.
   */
  static FuncionPtr crearBase();

  /**
   * @brief Construye la funcion paso h(x, y, r) = S(pi_3^3(x, y, r)).
   * @return La funcion paso.
   */
  static FuncionPtr crearPaso();
};

#endif  
