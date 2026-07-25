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
    
};