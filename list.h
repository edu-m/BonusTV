#ifndef LIST_H
#define LIST_H
#include "node.h"
#include <iostream>
using namespace std;

template <class T>
class List
{
private:
    int length;
    Node<T> *testa;

public:
    List(int length, Node<T> *testa) : length(length), testa(testa) {}
    List() : List(0, NULL) {}

    Node<T> *getHead()
    {
        return this->testa;
    }

    int getLength()
    {
        return this->length;
    }

    void insert(T value)
    {
        Node<T> *app = new Node<T>(value);
        this->insert(app);
    }

    void insertAscending(T value)
    {
        Node<T> *temp = new Node<T>(value);
        if (testa == NULL)
        {
            this->insert(value);
            return;
        }
        if (testa->getValue() > value)
        {
            this->insertHead(value);
            return;
        }
        Node<T> *current = testa;
        while (current->getValue() < value)
        {
            current = current->getNext();
        }

        temp->setPrev(current->getPrev());
        temp->setNext(current);
        current->getPrev()->setNext(temp);
        current->setPrev(temp);
        length++;
    }

    void insert(Node<T> *n)
    {
        if (testa == NULL)
        {
            testa = n;
            length++;
            return;
        }
        Node<T> *curr = testa;
        while (curr->getNext() != NULL)
        {
            curr = curr->getNext();
        }
        curr->setNext(n);
        length++;
    }

    bool isNodePresent(T val)
    {
        if (length == 0)
            return false;
        Node<T> *n = testa;
        while (n != NULL)
        {
            if (n->getValue() == val)
                return true;
            n = n->getNext();
        }
        return false;
    }

    Node<T> *seekNode(T val)
    {
        if (length == 0)
            return NULL;
        Node<T> *n = testa;
        while (n->getValue() != NULL)
        {
            if (n->getValue() == val)
                return n;
            n = n->getNext();
        }
        return NULL;
    }

    void deleteNode(Node<T> *n)
    {
        if (n == this->getHead())
        {
            this->testa = testa->getNext();
            this->length = length - 1;
            delete n;
            return;
        }
        Node<T> *prev = testa;
        Node<T> *curr = testa->getNext();
        while (curr != NULL)
        {
            if (curr == n)
            {
                prev->setNext(curr->getNext());
                length--;
                return;
            }
            prev = curr;
            curr = curr->getNext();
        }
    }

    Node<T> *deleteNode(T value)
    {
        if (this->seekNode(value))
        {
            if (testa->getValue() == value)
            {
                Node<T> *temp = testa;
                testa = testa->getNext();
                length--;
                return temp;
            }
            Node<T> *prev = testa;
            Node<T> *curr = testa->getNext();
            while (curr != NULL)
            {
                if (curr->getValue() == value)
                {
                    prev->setNext(curr->getNext());
                    length--;
                    return curr;
                }
                prev = curr;
                curr = curr->getNext();
            }
        }
        return NULL;
    }

    void print()
    {
        Node<T> *nk = this->getHead();
        while (nk != NULL)
        {
            cout << nk << endl;
            nk = nk->getNext();
        }
    }

    ~List()
    {
        Node<T> *ptr;

        for (ptr = testa; testa; ptr = testa)
        {
            testa = testa->getNext();
            delete ptr;
        }
    }
};

#endif