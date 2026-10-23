#ifndef CONTADOR_H
#define CONTADOR_H

/**
 * @file contador.h
 * @brief Declaracion de la clase Contador.
 */

/**
 * @class Contador
 * @brief Cuenta el numero de llamadas a funciones realizadas durante un
 *        calculo.
 *
 * Se pasa por referencia a cada evaluacion, de forma que no hay estado
 * global: cada calculo lleva su propio contador.
 */
class Contador {
public:
  /**
   * @brief Construye un contador a cero.
   */
  Contador();

  /**
   * @brief Anota una llamada mas.
   */
  void incrementar();

  /**
   * @brief Devuelve el numero de llamadas anotadas hasta ahora.
   * @return Numero de llamadas.
   */
  unsigned long long getLlamadas() const;

private:
  unsigned long long llamadas;  
};

#endif  
