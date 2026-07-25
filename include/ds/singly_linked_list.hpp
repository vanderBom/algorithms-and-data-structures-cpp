#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

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

    void pop_front(){
        if (head==nullptr){
            throw std::out_of_range("Invalid operation: list is empty");
        }

        if (head == tail){
            delete head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
            listSize--;
            return;
        }
        Node* current = head;
        head = current->next;
        delete current->data;
        delete current;
        listSize--;
    }

    void pop_back(){
        if (head==nullptr) throw std::out_of_range("Invalid operation: list is empty");
        
        if (head==tail){
            delete head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
            listSize--;
            return;
        }

        Node* current = head;
        while (current->next != tail){
            current = current->next;
        }
        delete tail->data;
        delete tail;
        tail = current;
        tail->next = nullptr;
        listSize--;
    }

    void insert (unsigned int pos, const T& value){

        if (pos > listSize) throw std::out_of_range("Invalid operation: index > listSize or index < 0");

        if (pos == 0){push_front (value); return;}

        if (pos == listSize ) {push_back (value); return;}

        Node* current = head;
        for (unsigned int i = 0 ; i != pos -1 ; i++){
            current = current->next;
        }
        Node* newNode = new Node;
        newNode->data = new T(value);
        newNode-> next = current->next;
        current->next = newNode;    
        listSize++;
    }

    void erase(unsigned int pos){
        if (pos >= listSize ) throw std::out_of_range("Invalid operation: index > listSize or index < 0");

        if (pos == 0){pop_front(); return;}

        if (pos == listSize -1 ){pop_back(); return;}

        Node* current = head;
        for (unsigned int i = 0 ; i != pos -1 ; i++){
            current = current->next;
        }
        Node* trash = current->next;
        current->next=trash->next;
        delete trash->data;
        delete trash;
        listSize--;
    }

    const T& at (unsigned int pos) const {
        if (pos >= listSize) throw std::out_of_range("Invalid operation: index > listSize or index < 0");
        Node* current = head;
        for (unsigned int i = 0 ; i != pos ; i++){
            current = current->next;
        }
        return *(current->data);
    }

    void set (unsigned int pos, const T& value){
        if (pos >= listSize) throw std::out_of_range("Invalid operation: index > listSize or index < 0");
        Node* current = head;
        for (int i = 0; i < pos  ; i++){
            current = current->next;
        }
        delete current->data;
        current->data = new T(value);

    }

    const T& front() const {
        if (head==nullptr) throw std::out_of_range("Invalid operation: empty list");
        return *(head->data);
    }

    const T& back() const{
        if (tail==nullptr) throw std::out_of_range("Invalid operation: empty list");
        return *(tail->data);
    }

    unsigned int size () const {
        return listSize;
    } 

    bool empty() const{
        if (listSize == 0) return true; else return false;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr){
            std::cout << *(current->data) << '\n';
            current = current->next;
        }
    }
};