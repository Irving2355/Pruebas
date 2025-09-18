/*
  ABB: Inserción y recorridos con comentarios
  --------------------------------------------------------
  Este programa implementa un Árbol Binario de Búsqueda (ABB)
  con operaciones de inserción y recorridos en:
    - Preorden  (Raíz, Izquierda, Derecha)
    - Inorden   (Izquierda, Raíz, Derecha)  -> en ABB produce la lista ordenada
    - Postorden (Izquierda, Derecha, Raíz)

  Se ejecutan dos ejercicios:
    1) {1,2,3,4,5,6,7,8,9}       (árbol degenerado hacia la derecha)
    2) {1,4,87,2,6,9,0}          (árbol más variado)

  Complejidad:
    - Inserción: O(h), donde h es la altura del árbol.
      * Mejor caso: O(log n) si está balanceado.
      * Peor caso:  O(n) si se degenera (como en el Ejercicio 1).
    - Recorridos: O(n), visitan cada nodo una sola vez.

  Compilación (g++):
    g++ -std=c++17 -O2 abb.cpp -o abb
*/

#include <iostream>
using namespace std;

/* Nodo de un ABB: almacena un entero y punteros a hijos izquierdo y derecho. */
struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;
    explicit Nodo(int v) : dato(v), izq(nullptr), der(nullptr) {}
};

/*
  Clase ABB que encapsula:
  - Puntero a la raíz.
  - Inserción recursiva.
  - Recorridos (preorden, inorden, postorden).
  - Liberación de memoria (destructor) para evitar fugas.
*/
class ABB {
public:
    ABB() : raiz(nullptr) {}
    ~ABB() { liberar(raiz); }  // Llama a liberar() para borrar todos los nodos.

    /* Inserta un valor en el ABB (envoltura pública). */
    void insertar(int v) { raiz = insertarRec(raiz, v); }

    /* Imprime los recorridos agregando un salto de línea al final. */
    void preorden() const { preordenRec(raiz); cout << '\n'; }
    void inorden()  const { inordenRec(raiz);  cout << '\n'; }
    void postorden()const { postordenRec(raiz);cout << '\n'; }

    /* Elimina todos los nodos y deja el árbol vacío (útil si se reutiliza el objeto). */
    void limpiar() { liberar(raiz); raiz = nullptr; }

private:
    Nodo* raiz;

    /*
      Inserción recursiva:
      - Si el subárbol está vacío, crea un nuevo nodo.
      - Si v < dato del nodo actual -> va al subárbol izquierdo.
      - En otro caso (v >= dato)     -> va al subárbol derecho.
        Nota: Aquí enviamos duplicados a la derecha por simplicidad.
              Alternativamente, podrías ignorarlos o llevar una cuenta.
    */
    static Nodo* insertarRec(Nodo* nodo, int v) {
        if (nodo == nullptr) return new Nodo(v);
        if (v < nodo->dato) nodo->izq = insertarRec(nodo->izq, v);
        else                nodo->der = insertarRec(nodo->der, v);
        return nodo; // Retorna la raíz del subárbol (posiblemente modificada).
    }

    /* PREORDEN: visita raíz, luego subárbol izquierdo, luego derecho. */
    static void preordenRec(Nodo* nodo) {
        if (!nodo) return;            // Caso base: subárbol vacío.
        cout << nodo->dato << ' ';    // 1) Raíz
        preordenRec(nodo->izq);       // 2) Izquierda
        preordenRec(nodo->der);       // 3) Derecha
    }

    /* INORDEN: visita izquierdo, raíz, derecho (en ABB => valores ordenados). */
    static void inordenRec(Nodo* nodo) {
        if (!nodo) return;
        inordenRec(nodo->izq);        // 1) Izquierda
        cout << nodo->dato << ' ';    // 2) Raíz
        inordenRec(nodo->der);        // 3) Derecha
    }

    /* POSTORDEN: visita izquierdo, derecho y al final la raíz. */
    static void postordenRec(Nodo* nodo) {
        if (!nodo) return;
        postordenRec(nodo->izq);      // 1) Izquierda
        postordenRec(nodo->der);      // 2) Derecha
        cout << nodo->dato << ' ';    // 3) Raíz
    }

    /*
      Libera memoria de manera postorden (izq, der, raíz) para asegurar
      que los hijos se borren antes que su padre. Evita memory leaks.
    */
    static void liberar(Nodo* nodo) {
        if (!nodo) return;
        liberar(nodo->izq);
        liberar(nodo->der);
        delete nodo;
    }
};

/*
  Función auxiliar para ejecutar un "caso" (lista de inserciones) y
  mostrar sus tres recorridos. Se crea un ABB local por cada ejercicio
  para que no se mezclen los datos entre casos.
*/
void ejecutarEjercicio(const char* titulo, const int* datos, int n) {
    cout << "=== " << titulo << " ===\n";
    ABB arbol;

    // Inserta cada elemento del arreglo en el ABB:
    for (int i = 0; i < n; ++i) {
        arbol.insertar(datos[i]);
    }

    // Muestra los tres recorridos:
    cout << "Preorden:  "; arbol.preorden();
    cout << "Inorden:   "; arbol.inorden();
    cout << "Postorden: "; arbol.postorden();
    cout << '\n';
}

int main() {
    // ---------------- Ejercicio 1 ----------------
    // Inserciones ordenadas: el ABB se vuelve una lista (peor caso de altura).
    int e1[] = {1,2,3,4,5,6,7,8,9};
    ejecutarEjercicio("Ejercicio 1 (1..9)", e1, sizeof(e1)/sizeof(e1[0]));

    // ---------------- Ejercicio 2 ----------------
    // Inserciones variadas: estructura menos degenerada.
    int e2[] = {1,4,87,2,6,9,0};
    ejecutarEjercicio("Ejercicio 2 (1,4,87,2,6,9,0)", e2, sizeof(e2)/sizeof(e2[0]));

    return 0; // Fin del programa.
}