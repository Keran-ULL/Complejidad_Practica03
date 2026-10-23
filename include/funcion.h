#ifndef FUNCION_H
#define FUNCION_H

#include <memory>
#include <vector>

#include "contador.h"
#include "natural.h"

/**
 * @file funcion.h
 * @brief Declaracion de la clase abstracta Funcion.
 *
 * Es la base de todas las funciones primitivas recursivas del programa:
 * las basicas (Cero, Sucesor, Proyeccion), las operaciones (Composicion,
 * Recursion) y las derivadas (Suma, Producto, Potencia).
 */

/**
 * @class Funcion
 * @brief Funcion de N^k en N, siendo k su aridad.
 *
 * Usa el patron "metodo plantilla": evaluar() es comun a todas las
 * funciones (comprueba la aridad y anota la llamada en el contador) y
 * delega el calculo propio de cada funcion en calcular(). Asi todas las
 * llamadas se cuentan de la misma forma, sin repetir codigo.
 */
class Funcion {
public:
  virtual ~Funcion() = default;

  /**
   * @brief Numero de argumentos que recibe la funcion.
   * @return Aridad k de la funcion.
   */
  virtual std::size_t aridad() const = 0;

  /**
   * @brief Evalua la funcion para unos argumentos, anotando la llamada.
   * @param argumentos Argumentos de la funcion; deben ser tantos como su
   *        aridad.
   * @param contador Contador donde se anotan las llamadas a funciones.
   * @return Valor de la funcion.
   * @throws ErrorAridad Si el numero de argumentos no coincide con la
   *         aridad.
   */
  Natural evaluar(const std::vector<Natural>& argumentos, Contador& contador) const;

protected:
  /**
   * @brief Calculo propio de cada funcion; lo invoca evaluar() una vez
   *        comprobada la aridad y anotada la llamada.
   * @param argumentos Argumentos de la funcion (ya validados).
   * @param contador Contador donde se anotan las llamadas a funciones.
   * @return Valor de la funcion.
   */
  virtual Natural calcular(const std::vector<Natural>& argumentos, Contador& contador) const = 0;
};

// Puntero compartido a una funcion; permite que varias funciones usen la misma como componente.
using FuncionPtr = std::shared_ptr<const Funcion>;

#endif  
