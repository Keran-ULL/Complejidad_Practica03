# Práctica 3: Funciones primitivas recursivas de números naturales

Asignatura: Complejidad Computacional (ULL), curso 2026/27.

Programa en C++17 que calcula la función **potencia(x, y) = xʸ** como una función primitiva recursiva de números naturales. La función se construye únicamente a partir de las funciones básicas y de las operaciones de composición y recursión primitiva. Además del resultado, el programa muestra el número de llamadas a funciones realizadas.

## Índice

1. [Compilación y uso](#1-compilación-y-uso)
2. [Definición de las funciones](#2-definición-de-las-funciones)
3. [Diseño de clases](#3-diseño-de-clases)
4. [Criterio para contar las llamadas](#4-criterio-para-contar-las-llamadas)
5. [Límites prácticos](#5-límites-prácticos)
6. [Manejo de errores](#6-manejo-de-errores)
7. [Estructura del proyecto](#7-estructura-del-proyecto)
8. [Tests](#8-tests)

---

## 1. Compilación y uso

Requisitos: `g++` con soporte de C++17 y `make`.

```bash
make            # genera build/main
make clean      # borra build/
```

Ejecución:

```bash
build/main -x <n> -y <n>
```

| Opción | Obligatoria | Descripción |
|---|---|---|
| `-x <n>` | Sí | Base de la potencia (número natural). |
| `-y <n>` | Sí | Exponente de la potencia (número natural). |

Las opciones pueden ir en cualquier orden. Ejemplo:

```
$ build/main -x 2 -y 3
potencia(2, 3) = 8
Llamadas a funciones: 128
```

---

## 2. Definición de las funciones

**Funciones básicas**

| Función | Definición | Aridad |
|---|---|---|
| Cero | Z(x) = 0 | 1 |
| Sucesor | S(x) = x + 1 | 1 |
| Proyección | πᵢᵏ(x₁, …, xₖ) = xᵢ | k |

**Operaciones**

* **Composición:** f(x̄) = h(g₁(x̄), …, gₘ(x̄)). Las gᵢ reciben los mismos k argumentos y h tiene aridad m.
* **Recursión primitiva:** a partir de una función base g (aridad n) y una función paso h (aridad n+2):
  * f(x̄, 0) = g(x̄)
  * f(x̄, y+1) = h(x̄, y, f(x̄, y))

**Funciones derivadas**

| Función | Caso base | Paso |
|---|---|---|
| `suma(x, y)` | suma(x, 0) = π₁¹(x) | suma(x, y+1) = S(π₃³(x, y, suma(x, y))) |
| `producto(x, y)` | producto(x, 0) = Z(π₁¹(x)) | producto(x, y+1) = suma(π₁³, π₃³)(x, y, producto(x, y)) |
| `potencia(x, y)` | potencia(x, 0) = S(Z(π₁¹(x))) | potencia(x, y+1) = producto(π₁³, π₃³)(x, y, potencia(x, y)) |

Con esta definición **0⁰ = 1**.

---

## 3. Diseño de clases

| Clase | Ficheros | Responsabilidad |
|---|---|---|
| `Natural` | `natural.h` | Alias del tipo de los números naturales (`unsigned long long`). |
| `Contador` | `contador.h/.cc` | Cuenta las llamadas a funciones. Se pasa por referencia a cada evaluación, sin estado global. |
| `Funcion` | `funcion.h/.cc` | Clase abstracta base. `evaluar()` comprueba la aridad, anota la llamada en el contador y delega el cálculo en el método virtual `calcular()` (patrón método plantilla). Así todas las funciones cuentan igual. |
| `Cero`, `Sucesor`, `Proyeccion` | `cero.*`, `sucesor.*`, `proyeccion.*` | Funciones básicas. |
| `Composicion` | `composicion.*` | Operación de composición. Valida las aridades al construirse. |
| `Recursion` | `recursion.*` | Operación de recursión primitiva. Valida las aridades al construirse y se evalúa de forma recursiva, tal y como indica la definición. |
| `Suma`, `Producto`, `Potencia` | `suma.*`, `producto.*`, `potencia.*` | Funciones derivadas. Heredan de `Recursion` y solo construyen su caso base y su paso a partir de las clases anteriores: no contienen código de cálculo propio. |
| `ArgParser` | `argparser.*` | Interpreta `-x` e `-y`. |
| Errores | `errores.h` | Jerarquía de excepciones. |

Las funciones que se usan como componentes se guardan con `std::shared_ptr<const Funcion>` (`FuncionPtr`), porque una misma función puede ser componente de varias.

El árbol de funciones que se construye para `potencia` es:

```
Potencia = Recursion
├── base: S ∘ (Z ∘ π₁¹)
└── paso: Producto ∘ (π₁³, π₃³)
            └── Producto = Recursion
                ├── base: Z ∘ π₁¹
                └── paso: Suma ∘ (π₁³, π₃³)
                            └── Suma = Recursion
                                ├── base: π₁¹
                                └── paso: S ∘ π₃³
```

---

## 4. Criterio para contar las llamadas

Se cuenta **una llamada cada vez que se evalúa cualquier función**: una función básica, una composición (y cada una de sus componentes) o un nivel de recursión (y su caso base o su paso). Por ejemplo, `potencia(x, 0)` hace 6 llamadas: el nivel de recursión, la composición externa `S ∘ (…)`, `S`, la composición `Z ∘ π₁¹`, `π₁¹` y `Z`.

---

## 5. Límites prácticos

Dos factores limitan los valores que se pueden calcular:

* **Tiempo.** Todo valor se obtiene sumando de uno en uno, así que el número de llamadas crece con el propio resultado. Orden de magnitud en un equipo normal: `potencia(2, 10)` (1,4 millones de llamadas) es instantáneo, `potencia(2, 12)` (22 millones) tarda unos 4 segundos, y `potencia(2, 14)` (358 millones) más de un minuto. Por esta razón el tipo `Natural` nunca llega a desbordarse en la práctica.
* **Pila.** La recursión es real, no iterativa, de modo que la profundidad de las llamadas crece con los valores. Con la pila por defecto de Linux (8 MB), un exponente entre 20 000 y 30 000 o mayor (por ejemplo `-x 1 -y 30000`) produce un desbordamiento de pila y el sistema termina el programa. Una base grande con exponente pequeño no tiene problema.

---

## 6. Manejo de errores

Todas las excepciones derivan de `ErrorPrimitiva` (`include/errores.h`) y se capturan en `main`:

| Excepción | Cuándo se lanza |
|---|---|
| `ErrorArgumentos` | Falta `-x` o `-y`, una opción repetida o desconocida, falta el valor de una opción, o el valor no es un natural (negativo, decimal, texto, con signo, vacío) o no cabe en el tipo `Natural`. |
| `ErrorAridad` | Se construye una función con componentes incompatibles (p. ej. una composición cuyas funciones internas tienen distinta aridad) o se evalúa con un número incorrecto de argumentos. |

Códigos de salida: `0` correcto, `1` error controlado, `2` error inesperado.

---

## 7. Estructura del proyecto

```
CC_Practica3/
├── Makefile
├── README.md
├── include/          # cabeceras (.h)
├── src/              # implementación (.cc) y main.cc
├── test/
│   └── test.sh       # batería de pruebas automáticas
└── build/            # generado por make
```

---

## 8. Tests

```bash
chmod +x test/test.sh
./test/test.sh
```

El script compila el proyecto y ejecuta 30 pruebas automáticas:

* **Manejo de errores** en las opciones (cada caso debe terminar con código de salida 1 y sin escribir nada en la salida estándar).
* **Resultados y número de llamadas** de varias potencias.
* **Casos límite:** 0⁰, x⁰, 0ʸ, x¹, 1ʸ y una base grande.
* **Orden de las opciones.**

Al final se muestra el número de pruebas pasadas y falladas; el código de salida del script es 0 solo si todas pasan.
