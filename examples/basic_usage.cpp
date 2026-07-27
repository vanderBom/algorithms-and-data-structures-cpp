#include <iostream>
#include <vector>
#include <cassert>
#include <exception>
#include "ds/singly_linked_list.hpp"

//     cl /EHsc /I include examples\basic_usage.cpp   for compile

template<typename T>
std::vector<T> to_vector(const SinglyLinkedList<T>& list){
    std::vector<T> out;
    for (unsigned int i = 0; i < list.size(); ++i) out.push_back(list.at(i));
    return out;
}

template<typename T>
void expect_equal(const std::vector<T>& a, const std::vector<T>& b){
    assert(a.size() == b.size());
    for (size_t i = 0; i < a.size(); ++i) assert(a[i] == b[i]);
}

void run_tests(){
    // Empty list
    SinglyLinkedList<int> L;
    assert(L.size() == 0);
    assert(L.empty());

    bool thrown = false;
    try { L.at(0); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    // push_back and insert
    L.push_back(10);
    L.push_back(20);
    L.push_back(40);
    L.insert(2, 30); // 10,20,30,40
    expect_equal(to_vector(L), std::vector<int>{10,20,30,40});

    // set
    L.set(0, 1);
    L.set(2, 2);
    L.set(3, 3); // 1,20,2,3
    expect_equal(to_vector(L), std::vector<int>{1,20,2,3});

    // push_front
    L.push_front(0); // 0,1,20,2,3
    expect_equal(to_vector(L), std::vector<int>{0,1,20,2,3});

    // pop_front
    L.pop_front(); // 1,20,2,3
    assert(L.front() == 1);

    // pop_back
    L.pop_back(); // 1,20,2
    assert(L.back() == 2);

    // contains / index_of
    assert(L.contains(20));
    assert(L.index_of(20) == 1);
    assert(!L.contains(999));
    assert(L.index_of(999) == -1);

    // erase middle
    L.erase(1); // remove 20 -> 1,2
    expect_equal(to_vector(L), std::vector<int>{1,2});

    // clear (list is non-empty) -> should succeed
    L.clear();
    assert(L.size() == 0 && L.empty());

    // clear on empty currently throws in this implementation
    thrown = false;
    try { L.clear(); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    // pop on empty should throw
    thrown = false;
    try { L.pop_front(); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    thrown = false;
    try { L.pop_back(); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    // copy constructor (deep copy)
    SinglyLinkedList<int> A;
    A.push_back(5);
    A.push_back(6);
    A.push_back(7);
    SinglyLinkedList<int> B(A);
    expect_equal(to_vector(A), to_vector(B));
    A.set(0, 42);
    // B should remain unchanged
    assert(B.at(0) == 5);

    // copy assignment
    SinglyLinkedList<int> C;
    C = A;
    expect_equal(to_vector(C), to_vector(A));

    std::cout << "All SinglyLinkedList tests passed." << std::endl;
}

int main(){
    try{
        run_tests();
    }catch(const std::exception& ex){
        std::cerr << "Test failed with exception: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
