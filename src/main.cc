/**
 * @file main.cc
 * @brief Punto de entrada del programa que calcula la funcion potencia
 *        como funcion primitiva recursiva de numeros naturales.
 *
 * Lee la base x y el exponente y de la linea de comandos, evalua
 * potencia(x, y) y muestra el resultado junto con el numero de llamadas
 * a funciones realizadas durante el calculo.
 *
 * Uso:
 *   main -x <n> -y <n>
 *
 * Asignatura: Complejidad Computacional. Curso 2026/27.
 */

#include <iostream>

#include "argparser.h"
#include "contador.h"
#include "errores.h"
#include "potencia.h"

/**
 * @brief Funcion principal del programa.
 *
 * Se limita a coordinar las distintas clases. Cualquier error controlado
 * (opciones invalidas...) se propaga como una excepcion derivada de
 * ErrorPrimitiva y se captura aqui de forma centralizada.
 *
 * @param argc Numero de argumentos recibidos por linea de comandos.
 * @param argv Vector de argumentos recibidos por linea de comandos.
 * @return 0 si termina correctamente, 1 si se produce un error
 *         controlado, 2 ante un error no anticipado.
 */
int main(int argc, char* argv[]) {
  try {
    const Opciones opciones = ArgParser::parsear(argc, argv);

    const Potencia potencia;
    Contador contador;
    const Natural resultado = potencia.evaluar({opciones.x, opciones.y}, contador);

    std::cout << "potencia(" << opciones.x << ", " << opciones.y << ") = " << resultado << '\n';
    std::cout << "Llamadas a funciones: " << contador.getLlamadas() << '\n';
  } catch (const ErrorPrimitiva& error) {
    std::cerr << "Error: " << error.what() << '\n';
    return 1;
  } catch (const std::exception& error) {
    std::cerr << "Error inesperado: " << error.what() << '\n';
    return 2;
  }

  return 0;
}
