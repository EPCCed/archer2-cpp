#include <iostream>

int sum(int a, int b) {
  return a + b;
}

double sum(double a, double b) {
  return a + b;
}

int i1 = 1;
int i2 = 2;
double d1 = 1.0;
double d2 = 2.0;
unsigned u42 = 42;
std::string name = "Alice";
std::string file = "data.csv";


int main(void) {
    std::cout << sum(i1, i2) << std::endl;
    std::cout << sum(3, 72) << std::endl;
    std::cout << sum(i1, u42) << std::endl;
    std::cout << sum(d2, d1) << std::endl;
    std::cout << sum(d2, 1e6) << std::endl;
    std::cout << sum(d2, i1) << std::endl;
    std::cout << sum(name, file) << std::endl;

    return 0;
}