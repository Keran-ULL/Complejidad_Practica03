/**
 * @file composicion.cc
 * @brief Implementacion de la operacion de composicion.
 */

#include "composicion.h"

#include <string>
#include <utility>

#include "errores.h"

/**
 * @brief Construye la composicion y valida las aridades de sus
 *        componentes.
 */
Composicion::Composicion(FuncionPtr externa, std::vector<FuncionPtr> internas)
    : externa(std::move(externa)), internas(std::move(internas)) {
  if (!this->externa || this->internas.empty()) {
    throw ErrorAridad("Composicion invalida: faltan la funcion externa o las internas");
  }
  for (const FuncionPtr& interna : this->internas) {
    if (!interna) {
      throw ErrorAridad("Composicion invalida: hay una funcion interna nula");
    }
    if (interna->aridad() != this->internas.front()->aridad()) {
      throw ErrorAridad("Composicion invalida: las funciones internas no tienen la misma aridad");
    }
  }
  if (this->externa->aridad() != this->internas.size()) {
    throw ErrorAridad("Composicion invalida: la funcion externa tiene aridad " +
                      std::to_string(this->externa->aridad()) + " y hay " +
                      std::to_string(this->internas.size()) + " funciones internas");
  }
}

/**
 * @brief Aridad de la composicion: la de las funciones internas.
 */
std::size_t Composicion::aridad() const {
  return internas.front()->aridad();
}

/**
 * @brief Evalua las funciones internas y aplica la externa a los
 *        resultados.
 */
Natural Composicion::calcular(const std::vector<Natural>& argumentos, Contador& contador) const {
  std::vector<Natural> resultados;
  resultados.reserve(internas.size());
  for (const FuncionPtr& interna : internas) {
    resultados.push_back(interna->evaluar(argumentos, contador));
  }
  return externa->evaluar(resultados, contador);
}
