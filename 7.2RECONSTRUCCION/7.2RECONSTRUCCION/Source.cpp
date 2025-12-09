
// Autor/a: Nombre y apellidos
// email:
// Compilador y S.O. utilizado
// Nombre del problema
// Comentario general sobre la solución
// explicando como se resuelve el problema
#include "Header.h"
#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int num, dato;
    vector<int> preOrden;
    vector<int> inOrden;
    BinTree<int> tree;
    cin >> num;

    if (num == 0)
        return false;

    for (int i = 0; i < num; i++) {
        cin >> dato;
        preOrden.push_back(dato);
    }

    for (int i = 0; i < num; i++) {
        cin >> dato;
        inOrden.push_back(dato);
    }

    tree = reconstruccion_oficial(preOrden, inOrden);

    // escribir sol
    tree.display(cout);
    cout << endl;

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}
 