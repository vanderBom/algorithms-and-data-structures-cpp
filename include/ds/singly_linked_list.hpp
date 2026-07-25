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
};