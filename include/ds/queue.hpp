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

        void pop(){
            if (data.size() == 0) throw std::out_of_range("Queue is empty");
            else data.pop_front();
        }

        T front() const{
            if (data.size() == 0) throw std::out_of_range("Queue is empty");
            else return data.front();
        }

        T back() const{
            if (data.size() == 0) throw std::out_of_range("Queue is empty");
            else return data.back();
        }

        unsigned int size() const{
            return data.size();
        }

        bool empty() const{
            return data.empty();
        }

        void clear(){
            data.clear();
        }
};