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
#include <memory>

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
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
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

 template<typename T>struct tSol {
    bool esBusq;
    T min;
    T max;
};

template <typename T> void SOLes_de_busqueda(const BinTree<T>& tree) {
    tSol<T> sol = es_de_busqueda(tree);
    if (sol.esBusq) {
        std::cout << "SI";
    }
    else {
        std::cout << "NO";
    }
}


template <typename T> tSol<T> es_de_busqueda(const BinTree<T>& tree) {
    /*
    if (tree.empty()) {
        return { true, INT_MAX, INT_MIN};
    }
    */
    if (tree.empty()) {
        return { true, T(), T() };
    }
    else if (tree.left().empty() && tree.right().empty()) {
        return{ true, tree.root(), tree.root() };
    }
    else {
        tSol<T> iz = es_de_busqueda(tree.left());
        tSol<T> der = es_de_busqueda(tree.right());

        tSol<T> solucion;
        if (!tree.left().empty() && !tree.right().empty()) {
            solucion.esBusq = iz.esBusq && der.esBusq && tree.root() > iz.max && tree.root() < der.min;
            solucion.max = std::max(tree.root(), der.max);
            solucion.min = std::min(tree.root(), iz.min);
        }
        else if (tree.left().empty()) {
            solucion.esBusq = der.esBusq && tree.root() < der.min;
            solucion.max = std::max(tree.root(), der.max);
            solucion.min = tree.root();
        }
        else if (tree.right().empty()){
            solucion.esBusq = iz.esBusq && tree.root() > iz.max;
            solucion.max = tree.root();
            solucion.min = std::min(tree.root(), iz.min);
        }

        return solucion;
    }
}

#endif
