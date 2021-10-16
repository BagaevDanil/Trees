#include <iostream>
#include "TreeAVL.h"

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
	
	a.Remove(5);

	a.Print();
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