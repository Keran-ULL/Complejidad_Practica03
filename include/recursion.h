#ifndef RECURSION_H
#define RECURSION_H

#include "funcion.h"

/**
 * @file recursion.h
 * @brief Declaracion de la operacion de recursion primitiva.
 */

/**
 * @class Recursion
 * @brief Recursion primitiva a partir de una funcion base g y una funcion
 *        paso h:
 *
 *   f(x_1..x_n, 0)   = g(x_1..x_n)
 *   f(x_1..x_n, y+1) = h(x_1..x_n, y, f(x_1..x_n, y))
 *
 * Si g tiene aridad n, h debe tener aridad n+2 y f tiene aridad n+1. La
 * evaluacion es recursiva (f se llama a si misma con y-1), tal y como
 * indica la definicion.
 */
class Recursion : public Funcion {
public:
  /**
   * @brief Construye la funcion definida por recursion primitiva.
   * @param funcionBase Funcion g, de aridad n.
   * @param funcionPaso Funcion h, de aridad n+2.
   * @throws ErrorAridad Si alguna funcion es nula o la aridad de h no es
   *         la de g mas 2.
   */
  Recursion(FuncionPtr funcionBase, FuncionPtr funcionPaso);

  /**
   * @brief Aridad de la funcion.
   * @return n+1, siendo n la aridad de la funcion base.
   */
  std::size_t aridad() const override;

private:
  /**
   * @brief Evalua f(x, y): g(x) si y es 0; en otro caso evalua
   *        recursivamente f(x, y-1) y aplica h a (x, y-1, resultado).
   * @param argumentos Los n+1 argumentos (x_1..x_n, y).
   * @param contador Contador donde se anotan las llamadas a funciones.
   * @return Valor de f.
   */
  Natural calcular(const std::vector<Natural>& argumentos, Contador& contador) const override;

  FuncionPtr base;  ///< Funcion g (caso base).
  FuncionPtr paso;  ///< Funcion h (paso recursivo).
};

#endif  // RECURSION_H
