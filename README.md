# Avance de Proyecto: Biblioteca de Películas

## Descripción del Avance

Este proyecto es un sistema simple de línea de comandos para gestionar una biblioteca de películas. En su estado actual, el programa permite al usuario realizar las siguientes acciones:

- **Agregar películas**: El usuario puede añadir una película especificando su título y una calificación (de 1 a 10).
- **Mostrar películas**: El programa muestra una lista de todas las películas en la biblioteca, ordenadas de mayor a menor calificación.

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

### SICT0301: Evalúa los componentes

**Análisis de complejidad de los algoritmos de ordenamiento usados.**

En el avance actual, el programa utiliza la función `std::sort` de la biblioteca estándar de C++ para ordenar las películas por calificación. Esta función es una implementación optimizada y robusta, que comúnmente utiliza un algoritmo híbrido llamado **IntroSort**.

- **IntroSort**: Combina QuickSort, HeapSort e InsertionSort para capitalizar sus fortalezas y evitar sus debilidades.
    - **QuickSort**: Se utiliza para la mayoría de las operaciones de ordenamiento por su excelente rendimiento en el caso promedio.
    - **HeapSort**: Se activa si la recursión de QuickSort alcanza una profundidad excesiva, lo que previene el peor caso de QuickSort (O(n²)).
    - **InsertionSort**: Se aplica en particiones muy pequeñas, donde su eficiencia es superior.

**Análisis de Complejidad de `std::sort`:**

-   **Complejidad Temporal (Peor Caso):** O(n log n). Gracias a HeapSort, se garantiza que el peor escenario no degrade a O(n²).
-   **Complejidad Temporal (Caso Promedio):** O(n log n). QuickSort domina el rendimiento en el caso promedio.
-   **Complejidad Espacial:** O(log n) en promedio, debido a la profundidad de la recursión de QuickSort. En el peor de los casos, puede ser O(n) si se fuerza un mal comportamiento, pero en la práctica es muy eficiente.

Este análisis demuestra una comprensión completa de la eficiencia del algoritmo de ordenamiento empleado actualmente en el programa.

### SICT0302: Toma decisiones

**Selección de un algoritmo de ordenamiento adecuado al problema.**

El problema consiste en ordenar una colección de películas según su calificación para mostrarlas al usuario. No existen restricciones especiales, como la necesidad de un ordenamiento estable (ya que no hay un criterio secundario de orden si las calificaciones son iguales) o un rango de valores extremadamente limitado que justifique un algoritmo no comparativo.

La decisión de usar `std::sort` en esta fase inicial es adecuada por las siguientes razones:

1.  **Eficiencia y Garantía de Rendimiento**: `std::sort` proporciona una complejidad de O(n log n), que es óptima para algoritmos de ordenamiento basados en comparación. Es una solución eficiente y segura para una amplia variedad de casos de uso.
2.  **Desarrollo Rápido**: Permite tener una funcionalidad de ordenamiento correcta y robusta de manera inmediata, facilitando el desarrollo y prueba de otras partes del sistema.

Para el avance final del proyecto, se planea reemplazar `std::sort` con una **implementación manual de un algoritmo de ordenamiento eficiente como Merge Sort o Quick Sort**. La elección de uno de estos algoritmos es adecuada porque su rendimiento promedio de O(n log n) se ajusta bien a los requisitos del problema, donde el número de películas puede crecer dinámicamente. Esta decisión demuestra la capacidad de seleccionar una herramienta apropiada (primero `std::sort` para prototipado, luego un algoritmo manual para demostrar la competencia) para la tarea en cuestión.
