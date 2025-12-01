#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list>

template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
public:
	
	void ordenaBurbuja(std::vector<T>&);
	void ordenaSeleccion(std::vector<T>&);
	void ordenaMerge(std::vector<T>&);

	int busqSecuencial(const std::vector<T>&, T);
	int busqBinaria(const std::vector<T>&, T);
};


template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	int i = low, j = mid + 1, k = low;

	while (i <= mid && j <= high) {
		if (A[i] < A[j]) {
			B[k++] = A[i++];
		} else {
			B[k++] = A[j++];
		}
	}
	while (i <= mid) {
		B[k++] = A[i++];
	}
	while (j <= high) {
		B[k++] = A[j++];
	}
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	if ( (high - low) < 1 ) {
		return;
	}
	int mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}


template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &v) {
	for (int i = v.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (v[j] > v[j + 1]) {
				swap(v, j, j + 1);
			}
		}
	}
}

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &v) {
	int pos;
	for (int i = v.size() - 1; i > 0; i--) {
		pos = 0;
		for (int j = 1; j <= i; j++) {
			if (v[j] > v[pos]) {
				pos = j;
			}
		}
		if (pos != i) {
			swap(v, i, pos);
		}
	}
}

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &v) {
	std::vector<T> tmp(v.size());
	mergeSplit(v, tmp, 0, v.size() - 1);
}

template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &v, T val) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == val) {
			return i;
		}
	}
	return -1;
}

template <class T>
int Sorts<T>::busqBinaria(const std::vector<T> &v, T val) {
	int low = 0, high = v.size() - 1, mid;

	while (low <= high) {
		mid = (low + high) / 2;
		if (v[mid] == val) {
			return mid;
		} else if (val < v[mid]) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return -1;
}

#endif /* SORTS_H_ */
