#include <iostream>

// Needs C++20
auto add(auto x, auto y) {
    return x+y;
}

int main(void) {
    auto num = 42;
    auto real = 42.0;
    
    std::cout << add(num,10) << std::endl;
    std::cout << std::fixed << add(real,10.0) << std::endl;
    
    return 0;
}