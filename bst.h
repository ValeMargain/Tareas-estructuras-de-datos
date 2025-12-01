#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>
#include <vector>     
#include <algorithm> 

template <class T> class BST;

template <class T>
class Node {
private:
	T value;
	Node *left, *right;

	Node<T>* predecesor();

public:
	Node(T);
	Node(T, Node<T>*, Node<T>*);
	void add(T);
	bool find(T);
	void remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
    void postorder(std::stringstream&) const; 

	friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri)
	: value(val), left(le), right(ri) {}

template <class T>
void Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) left->add(val);
		else left = new Node<T>(val);
	} 
    else { 
		if (right != 0) right->add(val);
		else right = new Node<T>(val);
	}
}

template <class T>
bool Node<T>::find(T val) {
	if (val == value) return true;
	if (val < value) return (left != 0 && left->find(val));
	if (val > value) return (right != 0 && right->find(val));
	return false;
}

template <class T>
Node<T>* Node<T>::predecesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (left == 0) {
		if (right != 0) {
			right = 0;
		}
		return ri;
	}

	if (left->right == 0) {
		left = left->left;
		le->left = 0;
		return le;
	}

	Node<T> *parent, *child;
	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

template <class T>
void Node<T>::remove(T val) {
	Node<T> * succ, *old;

	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				succ = left->predecesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				succ = right->predecesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				right = succ;
				delete old;
			} else {
				right->remove(val);
			}
		}
	}
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left) left->inorder(aux);
    if (aux.str().size() > 1) aux << " ";
    aux << value;
    if (right) right->inorder(aux);
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void Node<T>::postorder(std::stringstream &aux) const {
    if (left) left->postorder(aux);
    if (right) right->postorder(aux);

    if (aux.str().size() > 1) aux << " ";
    aux << value;
}


template <class T>
class BST {
private:
	Node<T> *root;

	int height(Node<T>*) const;
	bool ancestors(Node<T>*, T, std::vector<T>&) const; 
	int level(Node<T>*, T, int) const;
	void levelByLevel(std::stringstream&) const;
	int max(int a, int b) const { return (a > b ? a : b); }

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
    
	std::string inorder() const;
	std::string preorder() const; 
	std::string visit() const;
	int height() const;
	std::string ancestors(T) const;
	int whatlevelamI(T) const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void BST<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->predecesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
	}
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
int BST<T>::height(Node<T>* n) const {
    if (n == 0) return 0;
    return 1 + max(height(n->left), height(n->right));
}

template <class T>
int BST<T>::height() const {
    return height(root);
}

template <class T>
bool BST<T>::ancestors(Node<T>* n, T val, std::vector<T>& ancestors_list) const {
    if (n == 0) return false;
    if (n->value == val) return true;

    if (ancestors(n->left, val, ancestors_list) || ancestors(n->right, val, ancestors_list)) {
        ancestors_list.push_back(n->value);
        return true;
    }
    return false;
}

template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux;
    std::vector<T> ancestors_list;

    aux << "[";

    if (!empty()) {
        if (ancestors(root, val, ancestors_list)) {
            std::reverse(ancestors_list.begin(), ancestors_list.end());

            for (size_t i = 0; i < ancestors_list.size(); ++i) {
                if (i > 0) aux << " ";
                aux << ancestors_list[i];
            }
        }
    }

    aux << "]";
    return aux.str();
}

template <class T>
int BST<T>::level(Node<T>* n, T val, int lvl) const {
    if (n == 0) return -1;
    if (n->value == val) return lvl;

    int left = level(n->left, val, lvl + 1);
    if (left != -1) return left;

    return level(n->right, val, lvl + 1);
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    return level(root, val, 1);
}

template <class T>
void BST<T>::levelByLevel(std::stringstream& aux) const {
    if (root == 0) return;

    Node<T>* queue[1000]; 
    int ini = 0, fin = 0;

    queue[fin++] = root;

    while (ini < fin) {
        Node<T>* n = queue[ini++];

        if (aux.str().size() > 1) aux << " "; 
        aux << n->value;

        if (n->left != 0) queue[fin++] = n->left;
        if (n->right != 0) queue[fin++] = n->right;
    }
}

template <class T>
std::string BST<T>::visit() const {
    std::stringstream pre, ino, post, lvl;

    pre << "[";
    ino << "[";
    post << "[";
    lvl << "[";

    if (!empty()) {
        root->preorder(pre);
        root->inorder(ino);
        root->postorder(post);
        levelByLevel(lvl);
    }

    pre << "]";
    ino << "]";
    post << "]";
    lvl << "]";

    return pre.str() + "\n" + ino.str() + "\n" + post.str() + "\n" + lvl.str();
}

#endif /* BST_H_ */