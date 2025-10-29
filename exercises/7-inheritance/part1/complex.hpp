#ifndef CPPEX_COMPLEX_COMPLEX_HPP
#define CPPEX_COMPLEX_COMPLEX_HPP

// Simple complex number class
class Complex {
public:
  /* Add declarations to create:
  - A default constructor
  - A constructor using just a real component
  - A constructor using real and imaginary components
  */

  // Access components
  double real();
  /* Add declaration to access the imaginary component */

  // Compute the complex conjugate
  Complex conj();

  /* Add declaration for member function 'norm' that takes no arguments and
  returns the magnitude of the complex number.
  */

  /* Add declaration for an 'add' member function as so: z = i.add(j)
  I.e. For complex numbers i and j, z is the result of i + j. 
  */

  // Check if two complex numbers are equal
  bool equals(Complex other_complex);

  /* Add private member variables to store the real and imaginary components of
  the complex number. These should have type 'double' and a suitable default
  value.
  */
};

#endif