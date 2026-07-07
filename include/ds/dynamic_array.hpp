#pragma once

#include <iostream>

template <typename T>
class DynamicArray {
private:
    T* data;
    unsigned int arrSize;
    unsigned int cap;

    void resize (unsigned int newcap){
        T* newData=new T[newcap];

        for (unsigned int i = 0; i < arrSize; i++){
            newData[i] = data[i];
        }

        delete[] data; 
        data = newData;
        cap = newcap;
    }
public:
    //Constructor
    DynamicArray(){
        data = nullptr;
        arrSize = 0;
        cap = 0;
    }
    //Destructor
    ~DynamicArray(){
        delete[] data;
    }
}