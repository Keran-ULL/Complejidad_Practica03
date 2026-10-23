#ifndef SUCESOR_H
#define SUCESOR_H

#include "funcion.h"

/**
 * @file sucesor.h
 * @brief Declaracion de la funcion basica Sucesor.
 */

/**
 * @class Sucesor
 * @brief Funcion sucesor S(x) = x + 1, de aridad 1.
 */
class Sucesor : public Funcion {
public:
  /**
   * @brief Aridad de la funcion sucesor.
   * @return 1.
   */
  std::size_t aridad() const override;

private:
  /**
   * @brief Calcula S(x) = x + 1.
   * @param argumentos Un unico argumento x.
   * @param contador No se utiliza: la funcion no llama a otras.
   * @return x + 1.
   */
  Natural calcular(const std::vector<Natural>& argumentos, Contador& contador) const override;
};

#endif  