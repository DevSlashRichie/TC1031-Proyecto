# Biblioteca de Películas

Este proyecto es un sistema de línea de comandos para gestionar una biblioteca de películas. Permite agregar películas, verlas ordenadas por calificación, y guardar/cargar la biblioteca desde un archivo CSV.

## ¿Cómo usar el programa?

Para compilar y ejecutar el programa, sigue estos pasos en tu terminal:

1.  **Compilación**: Utiliza un compilador de C++ (como g++) para compilar el archivo `main.cpp`.

    ```bash
    g++ -std=c++11 main.cpp -o movie_library
    ```

2.  **Ejecución**: Corre el programa ejecutable generado.

    ```bash
    ./movie_library
    ```
    El programa cargará las películas desde `movies.csv` si existe.

3.  **Interacción**: Una vez que el programa esté en ejecución, aparecerá un menú con las siguientes opciones:
    - `1. Add movie`: Para agregar una nueva película.
    - `2. Show all movies (sorted by rating)`: Para mostrar la lista de películas ordenadas por calificación.
    - `3. Show all movies (sorted by seen date)`: Para mostrar la lista de películas ordenadas por la fecha en que fueron vistas.
    - `4. Show movies by specific rating`: Para mostrar las películas que coinciden con una calificación específica.
    - `0. Exit`: Para salir del programa y guardar la biblioteca en `movies.csv`.

## Dataset

El programa utiliza un archivo `movies.csv` para persistir los datos. Al iniciar, intenta cargar este archivo, y al salir, guarda las películas en él. Un ejemplo del formato es:

```csv
MovieName,Rating,Watched,SeenDate
Inception,9,1,2020-01-10
The Dark Knight,10,1,2019-05-20
```

## Algoritmo de Ordenamiento por Fecha

Para la funcionalidad de ordenar las películas por la fecha en que fueron vistas, se implementó un algoritmo de ordenamiento explícito. A diferencia del ordenamiento por calificación (que se basa en las propiedades del `std::multiset`), este ordenamiento se realiza bajo demanda.

El proceso es el siguiente:

1.  **Copia de Datos**: Las películas, que están almacenadas en un `std::multiset`, se copian a un `std::vector`.
2.  **Ordenamiento**: Se utiliza `std::sort`, una función de la biblioteca estándar de C++, para ordenar el `std::vector`. `std::sort` es un algoritmo híbrido altamente optimizado (generalmente una combinación de Quicksort, Heapsort e Insertion Sort) conocido como Introsort.
3.  **Comparación**: Para el criterio de ordenamiento, se proporciona una función lambda que compara dos películas basándose en su `seen_date`.

### ¿Por qué `std::sort` es una buena elección?

-   **Eficiencia**: `std::sort` tiene una complejidad promedio de **O(N log N)**, que es muy eficiente para conjuntos de datos de tamaño moderado a grande.
-   **Estándar de la Industria**: Es la forma idiomática y recomendada de ordenar colecciones en C++ moderno. Está bien probado, es rápido y es mantenido por la comunidad de C++.
-   **Simplicidad**: Evita la necesidad de implementar un algoritmo de ordenamiento desde cero, lo que reduce la cantidad de código y la probabilidad de errores.

### Análisis de Complejidad del Nuevo Comando

-   **`showMoviesByDate` (Consulta y Ordenamiento)**:
    -   **Peor, Mejor y Caso Promedio**: O(N log N), donde N es el número de películas. Este costo está dominado por la operación de ordenamiento `std::sort`. La copia inicial de los datos del `multiset` al `vector` toma O(N) tiempo, y la iteración para mostrar las películas también toma O(N) tiempo, pero el ordenamiento es la operación más costosa.

## SICT0302B: Toma decisiones

### Selecciona y usa una estructura de datos adecuada al problema

Para almacenar las películas, se utilizó un `std::multiset<Movie>`. Esta estructura de datos es un contenedor asociativo que mantiene sus elementos ordenados. Se eligió por las siguientes razones:

1.  **Ordenamiento automático**: El `multiset` ordena automáticamente las películas según la calificación (`rating`) al momento de la inserción. Esto se logra sobrecargando el operador `<` en la estructura `Movie`. Gracias a esto, no es necesario implementar un algoritmo de ordenamiento manual para mostrar las películas ordenadas, lo que simplifica el código y reduce la posibilidad de errores.
2.  **Eficiencia en la inserción**: La inserción de un elemento en un `multiset` (implementado como un árbol binario de búsqueda balanceado, usa Black-Red) tiene una complejidad logarítmica, O(log n), que es muy eficiente.

### Selecciona un algoritmo de ordenamiento adecuado al problema

El proyecto utiliza una estrategia de ordenamiento dual, diseñada a partir de los casos de uso esperados del usuario:

1.  **Ordenamiento Principal por Calificación (Rating) - `std::multiset` (Árbol de Búsqueda Balanceado - BST)**:
    -   **Estrategia**: La estructura de datos principal para almacenar las películas es un `std::multiset`, que las mantiene automáticamente ordenadas por calificación. Esto se logra aprovechando las propiedades de un Árbol de Búsqueda Balanceado (BST).
    -   **Justificación**: Se tomó esta decisión de diseño bajo dos supuestos clave sobre el comportamiento del usuario:
        1.  **La consulta más frecuente será por calificación**: Se espera que los usuarios quieran ver sus películas mejor calificadas con más frecuencia que verlas por fecha.
        2.  **La biblioteca crecerá con el tiempo**: Se espera que los usuarios agreguen películas continuamente.
        3. **Permite buscar por rating de manera más eficiente**: Como se espera que el usuario tenga más interés en buscar rating, se agregó una funcionalidad que permite al usuario buscar solo las películas de cierto rating. Usar BST permite una búsqueda logarítmica. 
    -   Dado estos supuestos, el `std::multiset` es ideal. Cada vez que un usuario agrega una película, la inserción en el BST tiene una complejidad de **O(log n)**. Este bajo costo de inserción es crucial para una aplicación donde se esperan adiciones frecuentes. Al mismo tiempo, la lista ya está ordenada por calificación, por lo que mostrarla es una operación eficiente de **O(n)** (para iterar y mostrar), satisfaciendo la necesidad de la consulta principal de manera óptima.

2.  **Ordenamiento Secundario por Fecha de Vista - `std::sort` (Introsort)**:
    -   **Estrategia**: Para la funcionalidad de ordenar por fecha, que se considera una consulta secundaria, se utiliza un enfoque de ordenamiento bajo demanda.
    -   **Implementación**: Los datos se copian del `multiset` a un `std::vector` temporal y se ordenan usando `std::sort`. Este algoritmo es típicamente una implementación de **Introsort**, un híbrido de Quicksort, Heapsort e Insertion Sort.
    -   **Justificación**: Como se espera que esta consulta sea menos frecuente, no es eficiente mantener una segunda estructura de datos constantemente ordenada por fecha. Incurrir en el costo de un ordenamiento **O(N log N)** con `std::sort` solo cuando el usuario lo solicita explícitamente es un compromiso de diseño inteligente. Evita la complejidad y la sobrecarga de memoria de mantener múltiples índices, ofreciendo flexibilidad sin penalizar el rendimiento de las operaciones más comunes (agregar películas y verlas por calificación).

## SICT0301B: Evalúa los componentes

### Análisis de complejidad

El análisis de complejidad de las operaciones principales es el siguiente:

-   **`addMovie` (Inserción)**:
    -   **Peor, Mejor y Caso Promedio**: O(log n). La inserción en un `std::multiset` (árbol balanceado) siempre requiere una búsqueda logarítmica para encontrar la posición correcta y luego una inserción y posible rebalanceo, que también es logarítmico.
-   **`showMovies` (Consulta por Rating)**:
    -   **Peor, Mejor y Caso Promedio**: O(n). La función itera sobre todos los `n` elementos del `multiset` para imprimirlos. No hay una forma más rápida de mostrar todos los elementos.
-   **`loadFromCSV` (Carga de datos)**:
    -   **Peor, Mejor y Caso Promedio**: O(k * log n), donde `k` es el número de líneas en el archivo CSV y `n` es el número de películas en la biblioteca. Por cada línea leída, se realiza una inserción en el `multiset`.
-   **`showMoviesByRating` (Consulta por calificación)**:
    -   **Peor, Mejor y Caso Promedio**: O(log n + k).  
        Gracias al uso de las funciones `lower_bound` y `upper_bound` del `std::multiset`, la búsqueda de todas las películas con una calificación específica se realiza en tiempo logarítmico **O(log n)**, ya que estas funciones aprovechan las propiedades del Árbol de Búsqueda Balanceado (BST) interno para encontrar los límites de los elementos que comparten la misma clave (en este caso, la calificación).  
        Una vez encontrados los límites, se itera solo sobre los elementos que coinciden películas con ese rating, resultando en una complejidad total de **O(log n + k)**.  

## SICT0303B: Implementa acciones científicas

### Implementa mecanismos para consultar información

-   El programa permite consultar todas las películas de la biblioteca a través de la opción `2. Show all movies`. La información se presenta de forma clara y ordenada por calificación, lo que facilita al usuario ver las películas mejor valoradas primero.

### Implementa mecanismos de lectura y escritura de archivos

-   **Lectura**: Al iniciar, la función `loadFromCSV("movies.csv")` lee los datos de las películas desde un archivo CSV, permitiendo la persistencia de la biblioteca entre sesiones.
-   **Escritura**: Al agregar una nueva película, la función `saveToCSV("movies.csv")` se llama para guardar el estado actual de la biblioteca en el archivo CSV. Esto asegura que los datos no se pierdan si el programa se cierra.

