#include <iostream>
#include "TreeAVL.h"

struct node // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(node* p)
{
	return p ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* minNode = findmin(r);
		minNode->right = removemin(r);
		minNode->left = q;
		return balance(minNode);
	}
	return balance(p);
}


void PrintF(node *Unit)
{
	if (Unit)
		cout << Unit->key << ") ";
	else
		return;

	if (Unit->left)
		cout << Unit->left->key << " | ";
	if (Unit->right)
		cout << Unit->right->key << "\n";

	PrintF(Unit->right);
	PrintF(Unit->left);
}


int main()
{
	TreeAVL<int> a;
	a.Insert(5, 453);
	a.Insert(7, 453);
	a.Insert(1, 453);
	a.Insert(4, 453);
	a.Insert(23, 453);
	a.Insert(11, 453);
	a.Insert(29, 453);

	a.Print();

	//node a(3);
	//insert(&a ,5);
	//insert(&a ,7);
	//insert(&a ,1);
	//PrintF(&a);
}

/*
template<class T>
inline TreeAVL<T>::TreeAVL(int Key, T Value)
{
	m_head = new Node<T>(Key, Value);
}

template<class T>
inline unsigned int TreeAVL<T>::GetHeight(Node<T>* Unit)
{
	return Unit ? (Unit->height) : 0;
}

template<class T>
inline int TreeAVL<T>::BalanceFactor(Node<T>* Unit)
{
	return GetHeight(Unit->right) - GetHeight(Unit->left);
}

template<class T>
inline void TreeAVL<T>::FixHeight(Node<T>* Unit)
{
	unsigned int unitChildLeft = GetHeight(Unit->left);
	unsigned int unitChildRight = GetHeight(Unit->right);
	Unit->height = (unitChildLeft > unitChildRight ? unitChildLeft : unitChildRight) + 1;
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::RotateRight(Node<T>* p) // правый поворот вокруг p
{
	Node<T>* q = p->left;
	p->left = q->right;
	q->right = p;
	FixHeight(p);
	FixHeight(q);
	return q;
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::RotateLeft(Node<T>* q) // левый поворот вокруг q
{
	Node<T>* p = q->right;
	q->right = p->left;
	p->left = q;
	FixHeight(q);
	FixHeight(p);
	return p;
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::Balance(Node<T>* p) // балансировка узла p
{
	FixHeight(p);
	if (BalanceFactor(p) == 2)
	{
		if (BalanceFactor(p->right) < 0)
			p->right = RotateRight(p->right);
		return RotateLeft(p);
	}
	if (BalanceFactor(p) == -2)
	{
		if (BalanceFactor(p->left) > 0)
			p->left = RotateLeft(p->left);
		return RotateRight(p);
	}
	return p; // балансировка не нужна
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::InsertF(Node<T>* p, int k, T value)
{
	if (!p) return new Node<T>(k, value);
	if (k < p->key)
		p->left = InsertF(p->left, k, value);
	else
		p->right = InsertF(p->right, k, value);
	return Balance(p);
}

template<class T>
inline void TreeAVL<T>::Insert(int Key, T Value)
{
	m_head = TreeAVL<T>::InsertF(m_head, Key, Value);
}

template<class T>
inline void TreeAVL<T>::PrintF(Node<T>* Unit)
{
	if (Unit)
		cout << "\n" << Unit->key << ") ";
	else
		return;

	if (Unit->left)
		cout << Unit->left->key;
	if (Unit->right)
		cout << " | " << Unit->right->key << "\n";

	PrintF(Unit->right);
	PrintF(Unit->left);
}

template<class T>
inline void TreeAVL<T>::Print()
{
	Node<T>* demo = m_head;
	TreeAVL<T>::PrintF(demo);
}*/