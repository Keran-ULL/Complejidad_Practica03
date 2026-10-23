/**
 * @file argparser.cc
 * @brief Implementacion de la clase ArgParser.
 */

#include "argparser.h"

#include <limits>
#include <stdexcept>

#include "errores.h"

/**
 * @brief Interpreta las opciones de linea de comandos.
 *
 * Recorre argv de izquierda a derecha reconociendo -x e -y; cualquier
 * otra cosa es un error. Se llevan dos indicadores porque 0 es un valor
 * valido y no sirve para saber si una opcion ha aparecido.
 */
Opciones ArgParser::parsear(int argc, char* argv[]) {
  Opciones opciones{0, 0};
  bool tieneX = false;
  bool tieneY = false;

  for (int i = 1; i < argc; ++i) {
    const std::string argumento = argv[i];

    if (argumento == "-x") {
      if (tieneX) {
        throw ErrorArgumentos("La opcion '-x' aparece mas de una vez");
      }
      opciones.x = aNatural(obtenerValor(argc, argv, i, "-x"), "-x");
      tieneX = true;
    } else if (argumento == "-y") {
      if (tieneY) {
        throw ErrorArgumentos("La opcion '-y' aparece mas de una vez");
      }
      opciones.y = aNatural(obtenerValor(argc, argv, i, "-y"), "-y");
      tieneY = true;
    } else {
      throw ErrorArgumentos("Opcion no reconocida: '" + argumento + "'");
    }
  }

  if (!tieneX) {
    throw ErrorArgumentos("Falta la opcion obligatoria -x <n>");
  }
  if (!tieneY) {
    throw ErrorArgumentos("Falta la opcion obligatoria -y <n>");
  }

  return opciones;
}

/**
 * @brief Obtiene el valor asociado a una opcion y avanza el indice.
 */
std::string ArgParser::obtenerValor(int argc, char* argv[], int& indice,
                                    const std::string& opcion) {
  if (indice + 1 >= argc) {
    throw ErrorArgumentos("A la opcion '" + opcion + "' le falta el valor");
  }
  ++indice;
  return argv[indice];
}

/**
 * @brief Convierte un texto de cifras decimales en un natural.
 */
Natural ArgParser::aNatural(const std::string& texto, const std::string& opcion) {
  if (texto.empty() || texto.find_first_not_of("0123456789") != std::string::npos) {
    throw ErrorArgumentos("El valor de '" + opcion + "' debe ser un numero natural (entero >= 0): '" +
                          texto + "'");
  }
  try {
    return std::stoull(texto);
  } catch (const std::out_of_range&) {
    throw ErrorArgumentos("El valor de '" + opcion + "' es demasiado grande (maximo " +
                          std::to_string(std::numeric_limits<Natural>::max()) + "): '" + texto + "'");
  }
}
