#pragma once
#include <iostream>
#include <string>
using namespace std;

template <class T>
class MyList
{
private:

    template <class T>
    class Cell
    {
    public:
        T value;
        Cell<T>* next;
        friend ostream& operator<< (ostream& out, Cell<T>& other)
        {
            out << other.value;
            return out;
        }

        Cell()
        {
            this->next = nullptr;
        }
    };


    Cell<T>* m_key;
    int m_sizeList;
public:

    MyList();
    void Delete(int Position);
    void DeleteFront();
    void DeleteBack();
    void Add(int Position, T Value);
    void AddFront(T Value);
    void AddBack(T Value);
    void Print();
    ~MyList();
    int GetSizeList();
    T GetFront();

    Cell<T>& operator[](int Index)
    {
        if (Index < 0 || Index >= m_sizeList)
        {
            cout << "\n\nErorr: referring to a non-existent position";
            exit(12345);
        }

        Cell<T>* defaultCell = m_key;
        int i = 0;
        while (i < Index)
        {
            defaultCell = defaultCell->next;
            i++;
        }
        return *defaultCell;
    }
};

//------------------------------------------------------\\

template<class T>
inline MyList<T>::MyList()
{
    m_key = nullptr;
    m_sizeList = 0;
}

template<class T>
inline MyList<T>::~MyList()
{
    if (m_key == nullptr)
        return;
    while (m_key->next != nullptr)
    {
        Cell<T>* defaultCell = m_key;
        m_key = m_key->next;
        delete[] defaultCell;

    }
    delete[] m_key;
}

template<class T>
inline void MyList<T>::Add(int Position, T Value)
{
    if (Position < 0 || Position > m_sizeList)
    {
        cout << "\n\nErorr: adding to a non-existent position";
        exit(12345);
    }

    if (Position == 0 && m_sizeList == 0)
    {
        m_key = new Cell<T>;
        m_key->value = Value;
        m_sizeList++;
        return;
    }
    else if (Position == 0)
    {
        Cell<T>* newCell = new Cell<T>;
        newCell->next = m_key;
        newCell->value = Value;
        m_key = newCell;
        m_sizeList++;
        return;
    }

    Cell<T>* predCell;
    predCell = m_key;
    int i = 1;
    while (i < Position)
    {
        predCell = predCell->next;
        i++;
    }
    Cell<T>* nextCell;
    nextCell = predCell->next;
    Cell<T>* newCell = new Cell<T>;
    newCell->value = Value;
    predCell->next = newCell;
    newCell->next = nextCell;
    m_sizeList++;
}

template<class T>
inline void MyList<T>::AddFront(T Value)
{
    Add(0, Value);
}

template<class T>
inline void MyList<T>::AddBack(T Value)
{
    Add(m_sizeList, Value);
}

template<class T>
inline void MyList<T>::Delete(int Position)
{
    if (Position >= m_sizeList || m_sizeList < 0)
    {
        cout << "\n\nErorr: deleting a non-existent element";
        exit(12345);
    }

    if (Position == 0 && m_sizeList == 1)
    {
        delete m_key;
        m_key = nullptr;
        m_sizeList--;
        return;
    }
    else if (Position == 0)
    {
        Cell<T>* defaultCell = m_key->next;
        delete m_key;
        m_key = defaultCell;
        m_sizeList--;
        return;
    }

    Cell<T>* predCell;
    predCell = m_key;
    int i = 1;
    while (i < Position)
    {
        predCell = predCell->next;
        i++;
    }

    if (predCell->next->next == nullptr)
    {
        delete predCell->next;
        predCell->next = nullptr;
        m_sizeList--;
        return;
    }

    Cell<T>* defaultCell;
    defaultCell = predCell->next;
    predCell->next = predCell->next->next;
    delete defaultCell;
    m_sizeList--;

}

template<class T>
inline void MyList<T>::DeleteFront()
{
    Delete(0);
}

template<class T>
inline void MyList<T>::DeleteBack()
{
    Delete(m_sizeList - 1);
}

template<class T>
inline void MyList<T>::Print()
{
    Cell<T>* defaultCell;
    defaultCell = m_key;
    if (defaultCell == nullptr)
    {
        cout << "Empty list";
        return;
    }
    while (defaultCell->next != nullptr)
    {
        cout << defaultCell->value << " ";
        defaultCell = defaultCell->next;
    }
    cout << defaultCell->value << " ";
}

template<class T>
inline int MyList<T>::GetSizeList()
{
    return m_sizeList;
}

template<class T>
inline T MyList<T>::GetFront()
{
    if (!m_key)
        exit(12345);
    return m_key->value;
}