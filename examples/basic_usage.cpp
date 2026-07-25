#include <iostream>
#include "ds/singly_linked_list.hpp"
//     cl /EHsc /I include examples\basic_usage.cpp   for compile

int main (){

    SinglyLinkedList<int> List1;
    List1.push_front(1);
    List1.push_front(2);

    List1.print();


    std::cin.get(); 
    return 0;
}
