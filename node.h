#ifndef NODE_H
#define NODE_H

#define OP1 "Nodo di valore: " << n.value << endl \
                               << "con successivo: " << n.next
#define OP0 "Nodo di valore: " << n.value << endl \
                               << "Privo di successore"
#include <fstream>
#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
    T value;
    Node<T> *next;

public:
    Node(T value, Node<T> *next) : value(value), next(next) {}
    Node(T value) : Node(value, NULL) {}
    Node() : Node(0, NULL) {}
    T getValue()
    {
        return this->value;
    }
    Node<T> *getNext()
    {
        return this->next;
    }
    void setValue(T val)
    {
        this->value = val;
    }
    void setNext(Node<T> *n)
    {
        this->next = n;
    }
    friend ostream &operator<<(ostream &out, const Node &n)
    {
        (n.next != NULL ? out << OP1 : out << OP0);
        return out;
    }
};

#endif
