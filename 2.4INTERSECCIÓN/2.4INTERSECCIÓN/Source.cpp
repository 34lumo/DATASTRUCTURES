
// Autor/a: Nombre y apellidos
// email:
// Compilador y S.O. utilizado
// Nombre del problema
// Comentario general sobre la solución
// explicando como se resuelve el problema

#include "list_linked_single.h"
#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    ListLinkedSingle lista1;
    ListLinkedSingle lista2;
    int n1, n2, datos;
    // leer los datos de la entrada
    cin >> n1;
    for (int i = 0; i < n1; i++) {
        cin >> datos;
        lista1.push_back(datos);
    }
    cin >> n2;
    for (int i = 0; i < n2; i++) {
        cin >> datos;
        lista2.push_back(datos);
    }

    lista1.interseccion(lista2);

    // escribir solución
    lista1.display();
    cout << endl;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}
