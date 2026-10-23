#ifndef PROYECCION_H
#define PROYECCION_H

#include "funcion.h"

/**
 * @file proyeccion.h
 * @brief Declaracion de la funcion basica Proyeccion.
 */

/**
 * @class Proyeccion
 * @brief Funcion proyeccion pi_i^k(x_1, ..., x_k) = x_i, de aridad k.
 */
class Proyeccion : public Funcion {
public:
  /**
   * @brief Construye la proyeccion i-esima de k argumentos.
   * @param indice Posicion i del argumento que se devuelve (de 1 a k).
   * @param total Aridad k de la funcion.
   * @throws ErrorAridad Si indice no esta entre 1 y total.
   */
  Proyeccion(std::size_t indice, std::size_t total);

  /**
   * @brief Aridad de la proyeccion.
   * @return k.
   */
  std::size_t aridad() const override;

private:
  /**
   * @brief Calcula pi_i^k(x_1, ..., x_k) = x_i.
   * @param argumentos Los k argumentos.
   * @param contador No se utiliza: la funcion no llama a otras.
   * @return El argumento i-esimo.
   */
  Natural calcular(const std::vector<Natural>& argumentos, Contador& contador) const override;

  std::size_t indice;  
  std::size_t total;   
};

#endif  
