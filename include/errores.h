#ifndef ERRORES_H
#define ERRORES_H

#include <stdexcept>
#include <string>

/**
 * @file errores.h
 * @brief Jerarquia de excepciones del programa de funciones primitivas
 *        recursivas.
 *
 * Se agrupan todas en un unico fichero de cabecera: cada excepcion es una
 * clase minima que solo anade un mensaje descriptivo sobre
 * std::runtime_error, asi que no hace falta un .cc aparte. main()
 * captura ErrorPrimitiva de forma centralizada y muestra error.what().
 */

/**
 * @class ErrorPrimitiva
 * @brief Excepcion base de la que heredan todos los errores propios del
 *        programa.
 */
class ErrorPrimitiva : public std::runtime_error {
public:
  /**
   * @brief Construye el error con un mensaje descriptivo.
   * @param mensaje Descripcion del error, pensada para mostrarse tal
   *        cual al usuario.
   */
  explicit ErrorPrimitiva(const std::string& mensaje) : std::runtime_error(mensaje) {}
};

/**
 * @class ErrorArgumentos
 * @brief Error en las opciones de linea de comandos (falta una opcion
 *        obligatoria, un valor que no es un natural, etc.).
 */
class ErrorArgumentos : public ErrorPrimitiva {
public:
  explicit ErrorArgumentos(const std::string& mensaje) : ErrorPrimitiva(mensaje) {}
};

/**
 * @class ErrorAridad
 * @brief Error de aridad: se construye una funcion con componentes
 *        incompatibles (p. ej. una composicion cuyas funciones internas
 *        no tienen la misma aridad) o se evalua con un numero incorrecto
 *        de argumentos.
 */
class ErrorAridad : public ErrorPrimitiva {
public:
  explicit ErrorAridad(const std::string& mensaje) : ErrorPrimitiva(mensaje) {}
};

#endif  
