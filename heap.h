#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

template <class T>
class Heap {
private:
	T *data;
	unsigned int capacity;
	unsigned int count;

	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);

public:
	Heap(unsigned int);
	~Heap();
	bool empty() const;
	bool full() const;
	void push(T);
	T pop();
	T top() const;
	void clear();
	unsigned int size() const;
	std::string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int sze) {
	capacity = sze;
	data = new T[capacity];
	if (data == nullptr) {
		throw std::runtime_error("OutOfMemory");
	}
	count = 0;
}

template <class T>
Heap<T>::~Heap() {
	delete[] data;
	data = nullptr;
	capacity = 0;
	count = 0;
}

template <class T>
bool Heap<T>::empty() const {
	return (count == 0);
}

template <class T>
bool Heap<T>::full() const {
	return (count == capacity);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return (2 * pos) + 1;
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return (2 * pos) + 2;
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;

	if (le < count && data[le] < data[min]) {
		min = le;
	}
	if (ri < count && data[ri] < data[min]) {
		min = ri;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
void Heap<T>::push(T val) {
	if (full()) {
		throw std::runtime_error("Overflow");
	}

	unsigned int pos = count;
	count++;

	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

template <class T>
T Heap<T>::pop() {
	if (empty()) {
		throw std::runtime_error("NoSuchElement");
	}

	T aux = data[0];
	data[0] = data[--count];
	heapify(0);
	return aux;
}

template <class T>
T Heap<T>::top() const {
	if (empty()) {
		throw std::runtime_error("NoSuchElement");
	}
	return data[0];
}

template <class T>
unsigned int Heap<T>::size() const {
	return count;
}

template <class T>
void Heap<T>::clear() {
	count = 0;
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";
	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		}
		aux << data[i];
	}
	aux << "]";
	return aux.str();
}

#endif /* HEAP_H_ */
