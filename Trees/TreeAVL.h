#pragma once
#include <iostream>
using namespace std;

template <class T>
class TreeAVL
{
private:
	//

	template <class T>
	class Node
	{
	public:
		int key;
		T value;
		unsigned int height;
		Node<T>* left;
		Node<T>* right;

		Node(int Key, T Value)
		{
			this->key = Key;
			this->value = Value;
			left = right = nullptr;
			height = 0;
		}
	};

	Node<T>* m_head;
	unsigned int GetHeight(Node<T>* Unit);
	int GetBalanceFactor(Node<T>* p);
	void FixHeight(Node<T>* p);
	Node<T>* RotateRight(Node<T>* p);
	Node<T>* RotateLeft(Node<T>* q);
	Node<T>* Balance(Node<T>* p);
	Node<T>* InsertPrivate(Node<T>* Unit, int Key, T Value);
	void PrintTreePrivate(Node<T>* Unit);
	Node<T>* PrintPrivate(Node<T>* Unit);

	Node<T>* FindMin(Node<T>* p);
	Node<T>* RemoveMin(Node<T>* p);
	Node<T>* RemovePrivate(Node<T>* p, int k);

public:
	TreeAVL(int Key, T Value);
	TreeAVL();
	void Insert(int Key, T Value);
	void Remove(int k);
	void PrintTree();
	void Print();
};

//-------------------------------------------------------------------------------\\

template<class T>
inline TreeAVL<T>::TreeAVL(int Key, T Value)
{
	m_head = new Node<T>(Key, Value);
}

template<class T>
inline TreeAVL<T>::TreeAVL()
{
	m_head = nullptr;
}

template<class T>
inline unsigned int TreeAVL<T>::GetHeight(Node<T>* Unit)
{
	return (Unit ? (Unit->height) : (0));
}

template<class T>
inline int TreeAVL<T>::GetBalanceFactor(Node<T>* Unit)
{
	return (GetHeight(Unit->right) - GetHeight(Unit->left));
}

template<class T>
inline void TreeAVL<T>::FixHeight(Node<T>* Unit)
{
	unsigned int InitChildLeft = GetHeight(Unit->left);
	unsigned int InitChildRight = GetHeight(Unit->right);
	Unit->height = ((InitChildLeft > InitChildRight) ? (InitChildLeft) : (InitChildRight)) + 1;
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::RotateRight(Node<T>* Unit)
{
	Node<T> *UnitLeftChild = Unit->left;
	
	Unit->left = UnitLeftChild->right;
	UnitLeftChild->right = Unit;
	FixHeight(Unit);
	FixHeight(UnitLeftChild);
	return(UnitLeftChild);
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::RotateLeft(Node<T>* Unit)
{
	Node<T> *UnitRightChild = Unit->right;

	Unit->right = UnitRightChild->left;
	UnitRightChild->left = Unit;
	FixHeight(Unit);
	FixHeight(UnitRightChild);
	return(UnitRightChild);
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::Balance(Node<T>* Unit)
{
	FixHeight(Unit); //--
	int BalanceFactor = GetBalanceFactor(Unit);

	if (BalanceFactor == 2) //RotateLeft
	{
		if (GetBalanceFactor(Unit->right) < 0) //BigRotateLeft
			Unit->right = RotateRight(Unit->right);
		Unit = RotateLeft(Unit);
	}
	else if (BalanceFactor == -2) //RotateRight
	{
		if (GetBalanceFactor(Unit->left) > 0) //BigRotateRight
			Unit->left = RotateRight(Unit->left);
		Unit = RotateRight(Unit);
	}
	return Unit;
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::InsertPrivate(Node<T>* Unit, int Key, T Value)
{
	if (!Unit)
		return (new Node<T>(Key, Value));

	if (Key < Unit->key)
		Unit->left = InsertPrivate(Unit->left, Key, Value);
	else if (Key > Unit->key)
		Unit->right = InsertPrivate(Unit->right, Key, Value);
	else
		exit(666666);

	return (Balance(Unit));
}

template<class T>
inline void TreeAVL<T>::Insert(int Key, T Value)
{
	m_head = TreeAVL<T>::InsertPrivate(m_head, Key, Value);
}

template<class T>
inline void TreeAVL<T>::PrintTreePrivate(Node<T>* Unit)
{
	if (!Unit)
		return;
	cout << "\n\n\n[" << Unit->key << "]" << Unit->value;
	cout << "\n|\t\\\n";
	if (!Unit->left)
		cout << "[null]";
	else
		cout << "[" << Unit->left->key << "]" << Unit->left->value;
	if (!Unit->right)
		cout << "\t[null]";
	else
		cout << "\t[" << Unit->right->key << "]" << Unit->right->value;

	PrintTreePrivate(Unit->right);
	PrintTreePrivate(Unit->left);
}

template<class T>
inline void TreeAVL<T>::PrintTree()
{
	Node<T>* demo = m_head;
	TreeAVL<T>::PrintTreePrivate(demo);
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::FindMin(Node<T>* Unit)
{
	return (Unit->left) ? (FindMin(Unit->left)) : (Unit);
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::RemoveMin(Node<T>* Unit)
{
	if (Unit->left == 0)
		return Unit->right;

	Unit->left = RemoveMin(Unit->left);
	return Balance(Unit);
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::RemovePrivate(Node<T>* Unit, int Key)
{
	if (!Unit)
		exit(666666);

	if (Key < Unit->key)
		Unit->left = RemovePrivate(Unit->left, Key);
	else if (Key > Unit->key)
		Unit->right = RemovePrivate(Unit->right, Key);
	else
	{
		Node<T>* UnitLeftChild = Unit->left;
		Node<T>* UnitRightChild = Unit->right;
		delete Unit;
		if (!UnitRightChild) 
			return UnitLeftChild;

		Node<T>* minNode = FindMin(UnitRightChild);
		minNode->right = RemoveMin(UnitRightChild);
		minNode->left = UnitLeftChild;
		return Balance(minNode);
	}
	return Balance(Unit);
}

template<class T>
inline void TreeAVL<T>::Remove(int Key)
{
	m_head = RemovePrivate(m_head, Key);
}

template<class T>
inline void TreeAVL<T>::Print()
{
	Node<T> *demo = m_head;
	PrintPrivate(demo);
}

template<class T>
inline TreeAVL<T>::Node<T>* TreeAVL<T>::PrintPrivate(Node<T>* Unit)
{
	if (Unit == 0)
		return Unit;

	//cout << "[" << Unit->key << "] " << Unit->value << " "; 

	Unit->left = PrintPrivate(Unit->left);
	//if (Unit->left)
		//cout << "[" << Unit->left->key << "] " << Unit->left->value << " ";
	cout << "[" << Unit->key << "]=>" << Unit->value << "  ";
	Unit->right = PrintPrivate(Unit->right);
	//if (Unit->right)
		//cout << "[" << Unit->right->key << "] " << Unit->right->value << " ";
	
	return(Unit);
}