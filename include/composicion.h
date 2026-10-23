#ifndef COMPOSICION_H
#define COMPOSICION_H

#include <vector>

#include "funcion.h"

/**
 * @file composicion.h
 * @brief Declaracion de la operacion de composicion.
 */

/**
 * @class Composicion
 * @brief Composicion de funciones: f(x) = h(g_1(x), ..., g_m(x)).
 *
 * Las funciones g_i (internas) reciben todas los mismos k argumentos x y
 * la funcion h (externa) recibe los m resultados, por lo que h debe tener
 * aridad m. La composicion resultante tiene aridad k.
 */
class Composicion : public Funcion {
public:
  /**
   * @brief Construye la composicion h(g_1, ..., g_m).
   * @param externa Funcion h, de aridad m.
   * @param internas Funciones g_1, ..., g_m, todas de la misma aridad k.
   * @throws ErrorAridad Si no hay funciones internas, alguna es nula, no
   *         tienen todas la misma aridad o la aridad de h no es m.
   */
  Composicion(FuncionPtr externa, std::vector<FuncionPtr> internas);

  /**
   * @brief Aridad de la composicion.
   * @return Aridad k de las funciones internas.
   */
  std::size_t aridad() const override;

private:
  /**
   * @brief Evalua cada g_i con los argumentos y aplica h a los resultados.
   * @param argumentos Los k argumentos x.
   * @param contador Contador donde se anotan las llamadas a funciones.
   * @return h(g_1(x), ..., g_m(x)).
   */
  Natural calcular(const std::vector<Natural>& argumentos, Contador& contador) const override;

  FuncionPtr externa;                
  std::vector<FuncionPtr> internas;  
};

#endif  
