# Avance de Proyecto: Biblioteca de Películas

## Descripción del Avance

Este proyecto es un sistema simple de línea de comandos para gestionar una biblioteca de películas. En su estado actual, el programa permite al usuario realizar las siguientes acciones:

- **Agregar películas**: El usuario puede añadir una película especificando su título y una calificación (de 1 a 10).
- **Mostrar películas**: El programa muestra una lista de todas las películas en la biblioteca, ordenadas de mayor a menor calificación.
- **Guardar tus películas**: El programa te da guardar tus películas ya vistas en un archivo para un futuro.

El programa está implementado en C++ y utiliza una estructura `Movie` para almacenar la información de cada película y una clase `MovieLibrary` para gestionar la colección.


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

3.  **Interacción**: Una vez que el programa esté en ejecución, aparecerá un menú con las siguientes opciones:
    - `1. Add movie`: Para agregar una nueva película.
    - `3. Show all movies (sorted by rating)`: Para mostrar la lista de películas ordenadas.
    - `0. Exit`: Para salir del programa.

## Cumplimiento de Sub-competencias

### SICT0301: Evalúa los componentes y SICT0302: Toma decisiones

**Análisis de complejidad de los algoritmos de ordenamiento usados.**

En el avance actual, el programa utiliza una función creada con BubbleSort.
Importante mencionar que bubblesort es promedio y peor caso O(n^2).

1. Se utiliza este algoritmo porque es el primer avance y no esperamos tener mucho problema con pequeños datasets.

2. Es importante mencionar que en este caso podemos usar quick sort ya que no nos importa que el algoritmo deba ser estable.

3. QuickSort ocupa menos memoria, la implementación esperamos ue el usuario presente pocas películas por lo que no debemos aumentar la dificultad demaciado.

4. Si queremos que aparte tome en cuenta un ordenamiento anterior debemos usar un algoritmo estable como merge sort.
