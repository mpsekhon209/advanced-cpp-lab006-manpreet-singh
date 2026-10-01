#include "singly_linked_list.h"

#include <iostream>

int main() {
    SLinkedList<int> list;
    list.push_back(10);
    list.push_front(5);
    list.push_back(15);

    std::cout << "size=" << list.size() << " front=" << list.front() << "\n";
    std::cout << "contains 15? " << (list.contains(15) ? "yes" : "no") << "\n";

    return 0;
}
