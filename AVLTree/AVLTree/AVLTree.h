#pragma once
#include <functional>
#define max(a,b) (a > b ? a : b)  
using namespace std;
template<typename T, typename Comparable = T, T NONE = 0>
class AVLTree {
	struct Node {
		T Elem;
		int h; // altura
		int n; // cantidad de elementos del nodo
		Node* left;
		Node* right;
		Node(T Elem) : Elem(Elem), left(nullptr), right(nullptr), h(0), n(1) {}
	};
	Node* root;
	int len;
	function<Comparable(T)> Key; // recibe un alumno y retorna el nombre, recibe un archivo y retorna fecha de creacion / extension / tamanio del archivo, o sea retorna un elemento comparable
	void destroy(Node* node) { // para destruir el arbol se hace en postorden
		if (node != nullptr) {
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}
	Node* add(Node* node, T Elem) {
		if (node == nullptr) {
			node = new Node(Elem);
		}
		else {
			if (Key(Elem) < Key(node->Elem)) {
				node->left = add(node->left, Elem);
			}
			else {
				node->right = add(node->right, Elem);
			}
			node = Balance(node);
		}
		return node;
	}
	T find(Node* node, Comparable val) {
		if (node == nullptr) {
			return NONE;
		}
		else if (val == Key(node->Elem)) {
			return node->Elem;
		}
		else if (val < Key(node->Elem)) {
			return find(node->left, val);
		}
		else {
			return find(node->right, val);
		}
	}
	void preorder(Node* node, function<void(T)> proc) {
		if (node != nullptr) {
			proc(node->Elem);
			preorder(node->left, proc);
			preorder(node->right, proc);
		}
	}
	void postorder(Node* node, function<void(T)> proc) {
		if (node != nullptr) {
			postorder(node->left, proc);
			postorder(node->right, proc);
			proc(node->Elem);
		}
	}
	void inorder(Node* node, function<void(T)> proc) {
		if (node != nullptr) {
			inorder(node->left, proc);
			proc(node->Elem);
			inorder(node->right, proc);
		}
	}

	int Height(Node* node) { return node == nullptr ? -1 : node->h; }
	int Lenght(Node* node) { return node == nullptr ? 0 : node->n; }
	void UpdateHeight(Node* node) {
		int hl = Height(node->left); // altura izquierda
		int hr = Height(node->right);
		node->h = 1 + max(Height(node->left), Height(node->right));
		node->n = 1 + Height(node->left) + Lenght(node->right);
	}
	Node* RotLeft(Node* node) {
		Node* NodeAux = node->right;
		node->right = NodeAux->left;
		NodeAux->left = node;
		UpdateHeight(NodeAux->left);
		UpdateHeight(NodeAux);
		return NodeAux;
	}
	Node* RotRight(Node* node) {
		Node* NodeAux = node->left;
		node->left = NodeAux->right;
		NodeAux->right = node;
		UpdateHeight(NodeAux->right);
		UpdateHeight(NodeAux);
		return NodeAux;
	}
	Node* Balance(Node* node) {
		int hl = Height(node->left);
		int hr = Height(node->right);
		if (hl - hr > 1) { // desbalanceado a la derecha
			if (Height(node->left->right) > Height(node->left->left)) { // izquierdo derecho es amayor, el hijo izquierdo rotarlo a la izquierda
				node->left = RotLeft(node->left);
			}
		}
		else if (hl - hr < -1) {
			if (Height(node->right->left) > Height(node->right->right)) {
				node->right = RotRight(node->right);
			}
		}
		else {
			UpdateHeight(node);
		}
		return node;
	}
public:
	AVLTree(function<Comparable(T)> Key = [](T a) {return a; }) : root(nullptr), len(0), Key(Key) {}
	~AVLTree() {
		destroy(root);
	}
	int size() {
		return len;
	}
	void add(T Elem) {
		root = add(root, Elem);
	}
	int Height() {
		return Height(root);
	}
	bool remove(Comparable val) {
		// Encontrar el nodo a eliminar
		// usamos dos elementos auxiliares, uno que comiensce en el nodo que queremos eliminar, y otro que apunte al padre del nodo
		Node* NodeAux = root;
		Node* Parent;
		bool Left; // pongo este Left con mayuscula para que se diferencia con el left del struct nodo
		while (NodeAux != nullptr) {
			if (val == key(NodeAux->Elem)) {
				break;
			}
			Parent = NodeAux;
			if (val < key(aux->Elem)) {
				Left = true;
				NodeAux = NodeAux->left;
			}
			else {
				Left = false;
				NodeAux = NodeAux->right;
			}
		}

		if (NodeAux == nullptr) return false;
		if (NodeAux->left == nullptr) { // primer escenario, el hijo derecho reemplaza a su padres
			if (NodeAux == root) root = NodeAux->right; // el hijo derecho sera la nueva raiz
			else if (Left) Parent->left = NodeAux->right; // si no es la raiz, el hijo derecho es el nuevo hijo izquierdo 
			else Parent->right = NodeAux->right;
			delete NodeAux;
		}
		else {
			Node* NodeAux2 = NodeAux->left; // con encontramos el mayor elemento que no tiene hijo derecho
			while (NodeAux2->right != nullptr) {
				Parent = NodeAux2; // puntero que apunta al padre de este elemento
				NodeAux2 = NodeAux2->right;
			}
			if (NodeAux2 == NodeAux2->left) NodeAux->left = NodeAux2->left; // el hijo izquierdo del aux2 sera el hijo izquierdo del elemento
			else Parent->right = NodeAux2->left;
			NodeAux->Elem = NodeAux2->Elem;
			delete NodeAux2;
		}
		delete NodeAux;
		return true;
	}
	T find(Comparable val) { // buscar que retorna primera coincidencia, falta buscar que retorne lista de coincidencias
		return find(root, val);
	}
	void preorder(function<void(T)> proc) {
		preorder(root, proc);
	}
	void postorder(function<void(T)> proc) {
		postorder(root, proc);
	}
	void inorder(function<void(T)> proc) {
		inorder(root, proc);
	}
};