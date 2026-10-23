#ifndef CERO_H
#define CERO_H

#include "funcion.h"

/**
 * @file cero.h
 * @brief Declaracion de la funcion basica Cero.
 */

/**
 * @class Cero
 * @brief Funcion cero Z(x) = 0, de aridad 1.
 */
class Cero : public Funcion {
public:
  /**
   * @brief Aridad de la funcion cero.
   * @return 1.
   */
  std::size_t aridad() const override;

private:
  /**
   * @brief Calcula Z(x) = 0.
   * @param argumentos Un unico argumento (se ignora).
   * @param contador No se utiliza: la funcion no llama a otras.
   * @return 0.
   */
  Natural calcular(const std::vector<Natural>& argumentos, Contador& contador) const override;
};

#endif  
