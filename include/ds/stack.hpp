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
        
        
};