#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class Stack {
    private:
        DynamicArray<T> data;
    public:
        Stack() = default;
        
        void push(const T& value){
            data.push_back(value);
        }
        void pop(){
            if (data.size() == 0) throw std::out_of_range("Stack is empty");
            else data.pop_back();
        }
        T top() const{
            if (data.size() == 0) throw std::out_of_range("Stack is empty");
            else return data.at(data.size()-1);
        }
        unsigned int size() const{
            return data.size();
        }
        bool empty(){
            if (data.size() == 0) return true;
            else return false;
        }
        void clear(){
            data.clear();
        }
};