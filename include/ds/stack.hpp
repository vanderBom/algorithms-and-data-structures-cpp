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
        
}