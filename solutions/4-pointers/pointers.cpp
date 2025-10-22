#include <iostream>
#include <memory>


int main() {

  // Print as you go
  // Print the value of x
  // Print the address of x
  // Print the pointer to x
  // Print the dereferenced pointer to x
  // Print the address of the pointer to x

  std::cout
    << "-----------------------" << std::endl
    << " Intialise x and x_ptr " << std::endl
    << "-----------------------" << std::endl;

  // Create an int x and set it to a value
  int x = 8;

  // Create a pointer to x called x_ptr
  int *x_ptr = &x;

  // Do all of the printing for x and x_ptr
  std::cout
    << "     x: " << x      << std::endl
    << "    &x: " << &x     << std::endl
    << " x_ptr: " << x_ptr  << std::endl
    << "*x_ptr: " << *x_ptr << std::endl
    << "&x_ptr: " << &x_ptr << std::endl;


  std::cout << std::endl
    << "-------------------------------------------------" << std::endl
    << " Dereference x_ptr to increment x's value by one " << std::endl
    << "-------------------------------------------------" << std::endl;

  // Dereference the pointer to x to increment x's value by one
  *x_ptr += 1;

  // Do all of the printing for x and x_ptr
  std::cout
    << "     x: " << x      << std::endl
    << "    &x: " << &x     << std::endl
    << " x_ptr: " << x_ptr  << std::endl
    << "*x_ptr: " << *x_ptr << std::endl
    << "&x_ptr: " << &x_ptr << std::endl;


  std::cout << std::endl
    << "---------------------------------" << std::endl
    << " Initialise y, y0_ptr and y1_ptr " << std::endl
    << "---------------------------------" << std::endl;

  // Create a double array y of size 4 and give it some values
  int y[4] = {0, 1, 2, 3};

  // Create pointers to the 0th and 1st elements in y
  // Call them y0_ptr and y1_ptr
  int *y0_ptr = &y[0];
  int *y1_ptr = &y[1];

  // Do all of the printing but for y, y0_ptr, and y1_ptr
  std::cout
    << "      y: " << y       << std::endl
    << "     &y: " << &y      << std::endl
    << " y0_ptr: " << y0_ptr  << std::endl
    << "*y0_ptr: " << *y0_ptr << std::endl
    << "&y0_ptr: " << &y0_ptr << std::endl
    << " y1_ptr: " << y1_ptr  << std::endl
    << "*y1_ptr: " << *y1_ptr << std::endl
    << "&y1_ptr: " << &y1_ptr << std::endl;


  std::cout << std::endl
    << "------------------" << std::endl
    << " Increment y0_ptr " << std::endl
    << "------------------" << std::endl;

  // Increment the y0_ptr pointer
  y0_ptr += 1;

  // Do all of the printing but for y, y0_ptr, and y1_ptr
  std::cout
    << "      y: " << y       << std::endl
    << "     &y: " << &y      << std::endl
    << " y0_ptr: " << y0_ptr  << std::endl
    << "*y0_ptr: " << *y0_ptr << std::endl
    << "&y0_ptr: " << &y0_ptr << std::endl
    << " y1_ptr: " << y1_ptr  << std::endl
    << "*y1_ptr: " << *y1_ptr << std::endl
    << "&y1_ptr: " << &y1_ptr << std::endl << std::endl;

  return 0;
}