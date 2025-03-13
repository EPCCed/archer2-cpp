#include <iostream>
#include "poly.hpp"


void base::forcast(){
 std::cout << "The forcast is Rain" << std::endl;
}

void child::forcast(){
 std::cout << "The forcast is Sunny" << std::endl;
}

void child::predict(){
	base::forcast();
};


