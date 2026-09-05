#pragma once

#include <iostream>
#include <stdexcept>
#include "singly_linked_list.hpp"

template <typename T>
class Queue {
    private: //Atributes for queue
        SinglyLinkedList<T> data;
    public: //Methods for queue
        Queue() = default;

        ~Queue() = default;
        
        void push(const T& value){
            data.push_back(value);
        }
    //Todo: Implement pop method

    //Todo: Implement front method

    //Todo: Implement back method

    //Todo: Implement size method

    //Todo: Implement empty method

    //Todo: Implement clear method
}