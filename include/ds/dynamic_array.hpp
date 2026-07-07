#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
/*
It has to have...
resize() resize the array   READY

push_back(value) insert a value in the array     READY
insert(i, value) insert a value in a especific position shifting right the other elements   READY

pop_back() delete the last value in the array   READY  
remove(i) delete a value in a index position    READY   

at(i) returns a value in a index position   READY 
set (i , value) set a value in a especific position     READY
size() returns the size of the array
cap() returns the capacity of the array

clear() empyts the array
contains(value) returns a boolean if the value is in the array or not
intexOf(value) returns the index of a value position
inEmpty() returns a boolean if the array is empty or not

*/
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


    void push_back (T& value){
        if (data==nullptr){
            resize (1);
        }else if (cap == arrSize){
            resize (cap*2);
        }
        data[arrSize] = value;
        arrSize++;
    }
    void insert (unsigned int pos, T& value){
        if (pos>arrSize){
            throw std::out_of_range("Invalid operation: index > size");
        }else{
            if (data==nullptr){
                resize (1);
            }else if (cap == arrSize){
                resize (cap*2);
            }
            for (int i = arrSize; i>pos; --i){
                data[i]=data[i-1];
            }
            data[pos]=value;
            arrSize++;
        }
    }

    void pop_back (){
        if (data==nullptr) throw std::out_of_range("data is NULL"); 
        else if (arrSize == 0) throw std::out_of_range("data id empty");
        else arrSize--;
    }
    void erase(unsigned int pos){
        if (pos>=arrSize) throw std::out_of_range("index > Size");
        else{
            for (unsigned int i = pos; i < arrSize-1; ++i){
                data[i]=data[i+1];
            }
                arrSize--;
        }
    }

    T at(unsigned int pos) const{
        if (pos>=arrSize) throw std::out_of_range("index > Size");
        else {
            return data[pos];
        }
    }

    void set(unsigned int pos, T& value){
        if (pos>=arrSize) throw std::out_of_range("index > Size");
        else{
            data[pos]=value;
        }
    }

    
}