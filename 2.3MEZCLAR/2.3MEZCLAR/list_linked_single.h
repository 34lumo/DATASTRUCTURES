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

    //FUNCION MEZCLAR
    ListLinkedSingle mezclar(ListLinkedSingle& other);

    void push_back(const int& elem);

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

ListLinkedSingle ListLinkedSingle::mezclar(ListLinkedSingle& lista2) {
    Node* current1 = head;
    Node* current2 = lista2.head;
    Node* siguiente = nullptr;

    if (current1 == nullptr) {
        head = lista2.head;
        lista2.head = nullptr;
        return *this;

    }
    else if (current2 == nullptr) {
        return *this;
    }
    else {
        if (current1->value <= current2->value) { 
            lista2.head = nullptr;
        }
        else { //caso en el que el primer elemnto menor este en la lista 2
            head = lista2.head;
            lista2.head = nullptr;

        }

        while (current1 != nullptr && current2 != nullptr) {
            if (current1->value <= current2->value) {
                if (current1->next == nullptr) {
                    current1->next = current2;
                    return *this;
                }
                else if (current1->next->value <= current2->value) {//quedarse en la misma lista
                    current1 = current1->next;
                }
                else { //apunta a la de abajo
                    siguiente = current1->next;
                    current1->next = current2;
                    current1 = siguiente;
                }
            }
            else {
                if (current2->next == nullptr) {
                    current2->next = current1;
                    return *this;
                }
                else if (current2->next->value < current1->value) {//te quedas en la lista de abajo
                    current2 = current2->next;
                }
                else { //apunta a la de arriba
                    siguiente = current2->next;
                    current2->next = current1;
                    current2 = siguiente;
                }

                //previo = current1;
                //siguiente = current2->next;
                //current2->next = current1;
                //current2 = siguiente;
                //current1 = current1->next;

            }
    }

    }
    return *this;
}


#endif
