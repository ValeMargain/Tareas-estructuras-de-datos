#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}

template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
	~List();

    void insertion(T val);
    int search(T val) const;
    void update(int pos, T val);
    void deleteAt(int pos);
    bool empty() const;
    void addFirst(T val);
    std::string toString() const;
private:
	Link<T> *head;
	int 	size;

};

template <class T>
List<T>::List() : head(nullptr), size(0) {}

template <class T>
List<T>::~List() {
    Link<T>* p;
    while (head != nullptr) {
        p = head->next;
        delete head;
        head = p;
    }
    size = 0;
}

template <class T>
List<T>::List(const List<T>& other) : head(nullptr), size(0) {
    Link<T>* p = other.head;
    while (p != nullptr) {
        insertion(p->value);
        p = p->next;
    }
}


template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
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

template <class T>
bool List<T>::empty() const {
	return (head == 0);
}


template <class T>
void List<T>::addFirst(T val)  {
	Link<T> *newLink;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw std::out_of_range("Índice fuera de rango");
	}
	newLink->next = head;
	head = newLink;
	size++;
}

template <class T>
void List<T>::insertion(T val) {
    Link<T> *newLink, *p;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw std::out_of_range("Índice fuera de rango");
	}

	if (empty()) {
		addFirst(val);
		return;
	}

	p = head;
	while (p->next != 0) {
		p = p->next;
	}

	newLink->next = 0;
	p->next = newLink;
	size++;
}


template <class T>
int List<T>::search(T val) const{
    Link<T>* p = head;
   int index = 0;

    while (p != nullptr) {
        if (p->value == val) {
            return index; // encontrado
        }
        p = p->next;
        index++;
    }
    return -1;
  
}

template <class T>
void List<T>::update(int pos, T val){
    Link<T>* p = head;
   int index = 0;

    while (p != nullptr) {
        if (index == pos) {
            
            p ->value= val;
        }
        p = p->next;
        index++;
    }
}

template <class T>
void List<T>::deleteAt(int index) {
        if (head == nullptr) return;

        if (index == 0) {
            Link<T> *tmp = head;
            head = head->next;
            delete tmp;
            return;
        }

        Link<T> *p = head;
        int i = 0;
        while (p->next != nullptr && i < index - 1) {
            p = p->next;
            i++;
        }

        if (p->next != nullptr) {
            Link<T> *tmp = p->next;
            p->next = tmp->next;
            delete tmp;
        }
    }

#endif