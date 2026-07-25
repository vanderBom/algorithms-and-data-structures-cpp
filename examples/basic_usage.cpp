#include <iostream>
#include "ds/singly_linked_list.hpp"
//     cl /EHsc /I include examples\basic_usage.cpp   for compile

int main (){

    SinglyLinkedList<int> List1;
    List1.push_back(10);
    List1.push_back(20);
    List1.push_back(40);
    List1.insert(2,30);
    List1.print();

    std::cout<<"Arriba de esto esta la lista con 4"<<std::endl;

    List1.set(0, 1);
    List1.set(2, 2);
    List1.set(3, 3);
    List1.print();


    std::cin.get(); 
    return 0;
}
