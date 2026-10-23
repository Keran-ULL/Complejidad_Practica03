#!/usr/bin/env bash
#
# test.sh - Bateria de pruebas automaticas para el calculo de la funcion
# potencia como funcion primitiva recursiva.
#
# Compila el proyecto y comprueba: manejo de errores en las opciones de
# linea de comandos, resultados de la potencia (incluidos los casos
# limite) y el numero de llamadas a funciones.
#
# Uso: ./test/test.sh   (se puede ejecutar desde cualquier directorio)

set -uo pipefail

# --- Localizar la raiz del proyecto y el ejecutable ------------------
PROYECTO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROYECTO_DIR"

# Ajusta esta ruta si tu Makefile genera el ejecutable en otro sitio.
EJECUTABLE="build/main"

TMP_DIR="$(mktemp -d)"
trap 'rm -rf "$TMP_DIR"' EXIT

PASADOS=0
FALLADOS=0

# --- Funciones auxiliares --------------------------------------------

# Anota el resultado de un test y lo muestra por pantalla.
# $1: nombre del test.  $2: 0 si ha pasado, cualquier otro valor si ha fallado.
reportar() {
  local nombre="$1"
  local resultado="$2"
  if [ "$resultado" -eq 0 ]; then
    echo "  [OK]   $nombre"
    PASADOS=$((PASADOS + 1))
  else
    echo "  [FAIL] $nombre"
    FALLADOS=$((FALLADOS + 1))
  fi
}

# Ejecuta el programa con los argumentos dados y comprueba que TERMINA
# CON ERROR CONTROLADO (codigo de salida 1) y sin escribir nada en la
# salida estandar.
# $1: nombre del test. Resto: argumentos para el ejecutable.
esperar_error() {
  local nombre="$1"
  shift
  local salida
  salida=$("$EJECUTABLE" "$@" 2>/dev/null)
  local codigo=$?
  if [ "$codigo" -eq 1 ] && [ -z "$salida" ]; then
    reportar "$nombre" 0
  else
    reportar "$nombre" 1
    echo "         codigo de salida obtenido: $codigo (esperado: 1)"
  fi
}

# Comprueba el resultado de potencia(x, y) y el numero de llamadas.
# $1: x. $2: y. $3: resultado esperado. $4: llamadas esperadas.
comprobar_potencia() {
  local x="$1" y="$2" resultado="$3" llamadas="$4"
  local nombre="potencia($x, $y) = $resultado con $llamadas llamadas"
  local esperado="potencia($x, $y) = $resultado
Llamadas a funciones: $llamadas"
  local salida
  salida=$("$EJECUTABLE" -x "$x" -y "$y" 2>&1)
  local codigo=$?
  if [ "$codigo" -eq 0 ] && [ "$salida" == "$esperado" ]; then
    reportar "$nombre" 0
  else
    reportar "$nombre" 1
    echo "         esperado:"
    echo "$esperado" | sed 's/^/           /'
    echo "         obtenido (codigo $codigo):"
    echo "$salida" | sed 's/^/           /'
  fi
}

# --- Compilacion -------------------------------------------------------

echo "=== Compilando el proyecto ==="
if ! make >"$TMP_DIR/make.log" 2>&1; then
  echo "La compilacion ha fallado. Salida de 'make':"
  cat "$TMP_DIR/make.log"
  exit 1
fi
if [ ! -x "$EJECUTABLE" ]; then
  echo "No se encuentra el ejecutable en '$EJECUTABLE'."
  echo "Ajusta la variable EJECUTABLE al principio de este script."
  exit 1
fi
echo "OK: $EJECUTABLE"
echo

# --- 1. Manejo de errores ----------------------------------------------

echo "=== 1. Manejo de errores en las opciones ==="
esperar_error "Sin argumentos"
esperar_error "Falta -y"                         -x 2
esperar_error "Falta -x"                         -y 2
esperar_error "-x sin valor"                     -y 2 -x
esperar_error "-y sin valor"                     -x 2 -y
esperar_error "Opcion no reconocida"             -x 2 -y 3 -z 4
esperar_error "Argumento suelto sin opcion"      2 3
esperar_error "Opcion -x repetida"               -x 2 -x 3 -y 1
esperar_error "Opcion -y repetida"               -x 2 -y 3 -y 1
esperar_error "Valor negativo"                   -x -3 -y 2
esperar_error "Valor no numerico"                -x abc -y 2
esperar_error "Valor decimal"                    -x 2 -y 2.5
esperar_error "Valor con signo +"                -x +2 -y 2
esperar_error "Valor vacio"                      -x "" -y 2
esperar_error "Valor demasiado grande"           -x 99999999999999999999999 -y 2
echo

# --- 2. Resultados y numero de llamadas -----------------------------------

echo "=== 2. Resultados y numero de llamadas ==="
# Formato: x y resultado llamadas
comprobar_potencia 2 3 8 128
comprobar_potencia 3 5 243 44332
comprobar_potencia 2 10 1024 1400232
comprobar_potencia 10 3 1000 200496
comprobar_potencia 4 4 256 34820
comprobar_potencia 12 2 144 3268
echo

# --- 3. Casos limite ---------------------------------------------------------

echo "=== 3. Casos limite ==="
comprobar_potencia 0 0 1 6       # 0^0 = 1 con esta definicion
comprobar_potencia 5 0 1 6       # x^0 = 1
comprobar_potencia 2 0 1 6
comprobar_potencia 0 1 0 20      # 0^y = 0 si y > 0
comprobar_potencia 0 3 0 36
comprobar_potencia 7 1 7 20      # x^1 = x
comprobar_potencia 1 10 1 146    # 1^y = 1
comprobar_potencia 100000 1 100000 20   # base grande, exponente pequeno
echo

# --- 4. Orden de las opciones -------------------------------------------------

echo "=== 4. Orden de las opciones ==="
salida_normal=$("$EJECUTABLE" -x 2 -y 3)
salida_invertida=$("$EJECUTABLE" -y 3 -x 2)
if [ "$salida_normal" == "$salida_invertida" ]; then
  reportar "-y 3 -x 2 da lo mismo que -x 2 -y 3" 0
else
  reportar "-y 3 -x 2 da lo mismo que -x 2 -y 3" 1
fi
echo

# --- Resumen -----------------------------------------------------------------

echo "=== Resumen ==="
echo "Pasados : $PASADOS"
echo "Fallados: $FALLADOS"

[ "$FALLADOS" -eq 0 ]
