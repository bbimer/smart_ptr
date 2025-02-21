#include <iostream>
#include "unique_ptr.h"

int main() {
    UniquePtr<Test> ptr(new Test()); 
    ptr->sayHello(); 

    UniquePtr<Test> ptr2 = std::move(ptr); 
    if (!ptr.get()) {
        std::cout << "ptr is now empty\n";
    }

    return 0;
}
