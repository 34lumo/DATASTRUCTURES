
// Autor/a: Nombre y apellidos
// email:
// Compilador y S.O. utilizado
// Nombre del problema
// Comentario general sobre la solución
// explicando como se resuelve el problema

#include "stack_linkedlist.h"
#include <stack>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    StackLinkedList<char> pila;
    string fila;
    char c;
    // leer los datos de la entrada
    getline(cin, fila);
    if (!std::cin)  // fin de la entrada
        return false;

    for (int i = 0; i < fila.length(); i++) {
        c = fila[i];
        if (c == '(' || c == '[' || c == '{') {
            pila.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (c == ')' && !pila.empty() && pila.top() == '(') {
                pila.pop();
            }
            else if (c == ']' && !pila.empty() && pila.top() == '[') {
                pila.pop();
            }
            else if (c == '}' && !pila.empty() && pila.top() == '{') {
                pila.pop();
            }
            else {
                cout << "NO" << endl;
                return true; //para que se acabe cuando encuentre algun parentesis que no
            }
        }
    }
    //en caso de que solo haya un parentesis abierto para poder diferenciar
    if (pila.empty())
        cout << "SI" << endl;
    else
        cout << "NO" << endl;

    // escribir sol

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
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

