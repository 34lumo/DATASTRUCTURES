/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Esta implementación utiliza smart pointers para prevenir
  * fugas de memoria y problemas con la destrucción.
  */

#ifndef __BINTREE_H
#define __BINTREE_H

#include <cassert>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {

        }
        else {
            display_node(root->left, out);
            display_node(root->right, out);
            out << " " << root->elem << " ";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}

/*
COSTE
    C0  ->  si n=0 siendo n el size del preorden

    En el caso peor estamos en un arbol desequilibrado
    c1*T(n1) + c2*T(n2) + c3+ c4*n (en caso peor se recorre con el while todo el arbol)
    c1*T(n-1) + c2*T(1) + c3 +c4*n --> Coste cuadrático

    En el caso de un arbol equilibrado
    c1*T(n1) + c2*T(n2) + c3+ c4*n (en un caso equilibrado el bucle while encontraría la raíz antes del final)log n
    c1*T(n1/2) + c2*T(n2/2) + c3 +c4*n --> Coste n log n
*/
BinTree<int> reconstruccion(const vector<int>& preorden, int ini_pre, int fin_pre, const vector<int>& inorden, int ini_in, int fin_in) {
    if (ini_pre == fin_pre) {
        return BinTree<int>();
    }
    else {
        //hay que jugar con la información que nos dan los dos ordenes
        /*
        - Del preOrden sabemos que el primer dato es la raíz
        1 2 3 4 5 6 7 
        1 es la raíz del arbol
            -->HIJO IZQ[ ): ini_pre + 1 hasta ini pre + 1 + cont
            -->HIJO DER[ ): ini_pre + 1 + cont hasta fin_pre
        - En el inOrden si conocemos la raíz sabemos que a la izquierda sera la parte del hijo izquierdo y a la derecha lo del hijo derecho, coger contador de cuantos elementos hay hasta la raíz
        3 2 4 1 5 7 6
        el hijo izquierdo es 3 2 4
        el hijo derecho 5 7 6
            --> HIJO_IZQ[ ): ini_in hasta ini_in + cont
            --> HIJO_DER[ ): ini_in + cont + 1 hasta fin_in
        */
        int cont = 0;
        int root = preorden[ini_pre];
        BinTree<int> left, right;
        while (inorden[ini_in + cont] != root) {
            cont++;
        }
        //cuando salgo inorden[ini_in+cont] == root
        left = reconstruccion(preorden, ini_pre + 1, ini_pre + 1 + cont, inorden, ini_in, ini_in + cont);
        right = reconstruccion(preorden, ini_pre + 1 + cont, fin_pre, inorden, ini_in + cont + 1, fin_in);

        return BinTree<int>(left, root, right);
    }
}

BinTree<int> reconstruccion_oficial(const vector<int>& preorden, const vector<int>& inorden) {
    return reconstruccion(preorden, 0, preorden.size(), inorden, 0, inorden.size());
}

#endif
