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
  * Implementación del TAD Lista mediante listas enlazadas simples.
  *
  * Esta versión introduce el constructor de copia.
  */

#ifndef __LIST_LINKED_SINGLE_H
#define __LIST_LINKED_SINGLE_H

#include <cassert>
#include <iostream>
#include <string>

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(const int& elem);

    ListLinkedSingle interseccion(ListLinkedSingle& lista2);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

ListLinkedSingle ListLinkedSingle::interseccion(ListLinkedSingle& lista2) {
    Node* curr1 = this->head;
    Node* curr2 = lista2.head;
    Node* aux = nullptr;
    Node* interseccion = nullptr;
    bool primeraInterseccion = false;
    this->head = nullptr;

    while (curr1 != nullptr && curr2 != nullptr){  //hasta que se haya acabado
        if (curr1->value < curr2->value) { //el valor de la lista 1 es menor entonces se pasa al siguiente de la lista1
            aux = curr1;
            curr1 = curr1->next;
            delete aux;
            //aux = curr1->next;
            //curr1->next = nullptr;
            //curr1 = aux;
        }
        else if (curr1->value > curr2->value) { //el valor de la lista 1 es mayor entonces se pasa al siguiente de la lista2
            curr2 = curr2->next;
        }
        else { //los valores de ambas listas son iguales
            if (!primeraInterseccion) { //se encuentra la primera interseccion
                this->head = curr1;
                primeraInterseccion = true;
                interseccion = curr1;
            }
            else {
                interseccion->next = curr1;
                interseccion = interseccion->next;
            }
            //interseccion->next = nullptr;
            curr1 = curr1->next;
            curr2 = curr2->next;

        }
    }
    while (curr1 != nullptr) { //vaciar la lista 1 en caso de que haya elementos que no procesemos
        Node* aux2 = curr1;
        curr1 = curr1->next;
        delete aux2;
    }

    if (primeraInterseccion) {
        //if (curr1 != nullptr || curr2 != nullptr) { //por si acaba antes la lista 2 que no se añadan mas valores
        interseccion->next = nullptr;
        //}
    }

    return *this;
}


#endif