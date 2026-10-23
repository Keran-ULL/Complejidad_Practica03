#ifndef POTENCIA_H
#define POTENCIA_H

#include "recursion.h"

/**
 * @file potencia.h
 * @brief Declaracion de la funcion primitiva recursiva Potencia.
 */

/**
 * @class Potencia
 * @brief potencia(x, y) = x^y, de aridad 2.
 *
 * Definida por recursion primitiva a partir del producto:
 *   potencia(x, 0)   = S(Z(pi_1^1(x)))
 *   potencia(x, y+1) = producto(pi_1^3(x, y, r), pi_3^3(x, y, r)),
 *                      con r = potencia(x, y)
 *
 * Con esta definicion potencia(0, 0) = 1.
 */
class Potencia : public Recursion {
public:
  /**
   * @brief Construye la funcion potencia.
   */
  Potencia();

private:
  /**
   * @brief Construye la funcion base g(x) = S(Z(pi_1^1(x))) = 1.
   * @return La funcion base.
   */
  static FuncionPtr crearBase();

  /**
   * @brief Construye la funcion paso h(x, y, r) = producto(x, r).
   * @return La funcion paso.
   */
  static FuncionPtr crearPaso();
};

#endif  
