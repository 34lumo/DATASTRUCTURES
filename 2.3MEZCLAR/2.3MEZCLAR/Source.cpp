
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

    // leer los datos de la entrada
    ListLinkedSingle lista1;
    ListLinkedSingle lista2;
    int n1;
    cin >> n1;
    while (n1 != 0) {
        lista1.push_back(n1);
        cin >> n1;
    }
    int n2;
    cin >> n2;
    while (n2 != 0) {
        lista2.push_back(n2);
        cin >> n2;
    }

    lista1.mezclar(lista2);

    // escribir solución
    lista1.display();
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
        cout << endl;
    }

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}
