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

        for (unsigned int i = 0; i < arrSize ; i++){
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

    //Features of dynamic array

    //push-back
    //It has to push at the end of the array a value
    //if the array is full we have to expand it
    //or we have to insert the value at the end of the array and increment by 1 the array size

    void push_back (T& value){
        if (data==nullptr){
            resize (1);
        }else if (cap == arrSize){
            resize (cap*2);
        }
        data[arrSize] = value;
        arrSize++;
    }
}