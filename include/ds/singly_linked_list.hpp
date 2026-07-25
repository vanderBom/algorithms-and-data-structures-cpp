#pragma once

#include <iostream>

/*

*/

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T* data;
        Node* next;
    };

    Node* head;
    Node* tail;
    unsigned int listSize;
public:
    SinglyLinkedList(){
        head = nullptr;
        tail = nullptr;
        listSize = 0;
    }
    ~SinglyLinkedList(){
        Node* current=head;
        Node* nextNode;
        while(current != nullptr){
            nextNode = current->next;
            delete current->data;
            delete current;
            current = nextNode;
        }
    }
    void push_front(const T& value){
        Node* newNode = new Node;
        newNode->data = new T(value);
        if (head == nullptr){
            head = newNode;
            tail = newNode;
            newNode->next=nullptr;
        } else {
            newNode->next = head;
            head = newNode;
        }
        listSize++;
    }

    void push_back(const T& value){
        Node* newNode = new Node;
        newNode->data= new T(value);
        newNode->next=nullptr;
        if (head ==nullptr){
            head = newNode;
            tail=newNode;
        }else{
            tail->next=newNode;
            tail=newNode;
        }
        listSize++;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr){
            std::cout << *(current->data) << '\n';
            current = current->next;
        }
    }
};