#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <string>

#include "natural.h"

/**
 * @author Keran Miranda González
 * @file argparser.h
 * @brief Declaracion de la estructura Opciones y la clase ArgParser.
 *
 * Interpreta las opciones de linea de comandos del programa:
 *
 *   main -x <n> -y <n>
 *
 * Ambas son obligatorias: -x es la base y -y el exponente de la
 * potencia, dos numeros naturales (enteros >= 0).
 */

/**
 * @struct Opciones
 * @brief Opciones de linea de comandos ya interpretadas.
 */
struct Opciones {
  Natural x;  // Base de la potencia 
  Natural y;  // Exponente de la potencia 
};

/**
 * @class ArgParser
 * @brief Interprete de las opciones de linea de comandos.
 *
 * No mantiene estado propio: todos sus metodos son estaticos.
 */
class ArgParser {
public:
  /**
   * @brief Interpreta las opciones de linea de comandos.
   *
   * @param argc Numero de argumentos, tal y como los recibe main().
   * @param argv Vector de argumentos, tal y como los recibe main().
   * @return Las opciones ya interpretadas y validadas.
   * @throws ErrorArgumentos Si falta -x o -y, si aparece repetida, si a
   *         una opcion le falta el valor, si el valor no es un natural
   *         o no cabe en el tipo Natural, o si hay una opcion no
   *         reconocida.
   */
  static Opciones parsear(int argc, char* argv[]);

private:
  /**
   * @brief Obtiene el valor asociado a una opcion y avanza el indice
   *        para dejarlo apuntando a ese valor.
   *
   * @param argc Numero de argumentos.
   * @param argv Vector de argumentos.
   * @param indice Indice de la opcion; se incrementa en 1.
   * @param opcion Nombre de la opcion, para el mensaje de error.
   * @return El valor asociado a la opcion.
   * @throws ErrorArgumentos Si no queda ningun argumento tras la opcion.
   */
  static std::string obtenerValor(int argc, char* argv[], int& indice,
                                  const std::string& opcion);

  /**
   * @brief Convierte un texto en un numero natural.
   *
   * Solo se admiten cifras decimales: se rechazan signos, decimales,
   * espacios y el texto vacio.
   *
   * @param texto Texto a convertir.
   * @param opcion Nombre de la opcion, para el mensaje de error.
   * @return El numero natural.
   * @throws ErrorArgumentos Si el texto no es un natural o es demasiado
   *         grande.
   */
  static Natural aNatural(const std::string& texto, const std::string& opcion);
};

#endif  
