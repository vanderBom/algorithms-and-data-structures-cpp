#include <iostream>
#include "ds/singly_linked_list.hpp"
//     cl /EHsc /I include examples\basic_usage.cpp   for compile

int main (){

    SinglyLinkedList<int> List1;
    List1.push_back(10);
    List1.push_back(20);
    
    List1.print();

    std::cout<<"Arriba de esto esta la lista con 4"<<std::endl;

    List1.erase(1);
    List1.print();


    std::cin.get(); 
    return 0;
}
