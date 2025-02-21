#include <iostream>
#include "unique_ptr.h"
#include "shared_ptr.h"

int main() {
    std::cout << "Testing UniquePtr:\n";
    {
        UniquePtr<Test> ptr(new Test());
        ptr->sayHello();

        UniquePtr<Test> ptr2 = std::move(ptr);
        if (!ptr.get()) {
            std::cout << "ptr is now empty" << std::endl;
        }
    } 

    std::cout << std::endl << "Testing SharedPtr:" << std::endl;
    {
        SharedPtr<Test> sp1(new Test());
        std::cout << "Reference count: " << sp1.use_count() << std::endl;

        {
            SharedPtr<Test> sp2 = sp1; 
            std::cout << "copy: " << sp1.use_count() << std::endl;

            SharedPtr<Test> sp3 = std::move(sp2); 
            std::cout << "move: " << sp1.use_count() << std::endl;
        }

        std::cout << "scope: " << sp1.use_count() << std::endl;
    } 

    return 0;
}
