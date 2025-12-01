#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>
#include <stdexcept>

template <class T>
class DLink {
public:
    T value;
    DLink<T>* previous;
    DLink<T>* next;

    DLink(T val) : value(val), previous(0), next(0) {}
};

template <class T>
class DList {
public:
    DList();
    ~DList();

    void insertion(T val);                // insertar al final
    std::string toStringForward() const;  // recorrer hacia adelante
    std::string toStringBackward() const; // recorrer hacia atras
    int search(T val) const;              // buscar por valor
    void update(int index, T val);        // actualizar por indice
    void deleteAt(int index);             // eliminar por indice

private:
    DLink<T>* head;   // primer nodo
    DLink<T>* tail;   // ultimo nodo
    int size;         // numero de nodos en la lista

    void clear();     // borra toda la lista
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
    clear();
}

template <class T>
void DList<T>::clear() {
    DLink<T>* p = head;
    while (p != 0) {
        DLink<T>* q = p->next; // guarda el siguiente
        delete p;              // borra el actual
        p = q;                 // avanza
    }
    head = tail = 0;
    size = 0;
}


template <class T>
void DList<T>::insertion(T val) {
    DLink<T>* newLink = new DLink<T>(val);
    if (head == 0) {
        head = tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size++;
}

// Recorre hacia adelante y construye un string
template <class T>
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T>* p = head;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

// Recorre hacia atras y crea un string
template <class T>
std::string DList<T>::toStringBackward() const {
    std::stringstream aux;
    DLink<T>* p = tail;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

// Busca un elemento y regresa el indice
template <class T>
int DList<T>::search(T val) const {
    int index = 0;
    DLink<T>* p = head;
    while (p != 0) {
        if (p->value == val) {
            return index;
        }
        p = p->next;
        index++;
    }
    return -1;
}

// Actualiza valor en índice
template <class T>
void DList<T>::update(int index, T val) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    int pos = 0;
    DLink<T>* p = head;
    while (pos != index) {
        p = p->next;
        pos++;
    }
    p->value = val;
}

// Elimina un elementro con el indice
template <class T>
void DList<T>::deleteAt(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of bounds");
    }

    DLink<T>* p = head;
    int pos = 0;
    while (pos != index) {
        p = p->next;
        pos++;
    }

    if (p->previous != 0) {
        p->previous->next = p->next;
    } else {
        head = p->next;  // borrar en cabeza
    }

    if (p->next != 0) {
        p->next->previous = p->previous;
    } else {
        tail = p->previous;  // borrar en cola
    }

    delete p;
    size--;
}

#endif /* DLIST_H_ */
