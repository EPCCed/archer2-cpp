#include "complex.hpp"
#include <cmath>

Base::Base(double real) : re(real) {
}

Base::Base(double real, double imag) : re(real), im(imag) {
}

//Complex::Complex() : Base() {
//}

Complex::Complex(double real) : Base(real) {
}

Complex::Complex(double real, double imag) : Base(real, imag) {
}

double Complex::real() {
  // Return real component
  return re;
}

/* Add definition of a member function to access the imaginary component */
double Complex::imag() {
  // Return real component
  return im;
}


Complex Complex::conj() {
  // Return complex conjugate
  return Complex{re, -im};
}

/* Add definition of 'norm' member function. Hint: Look up std::sqrt from the
cmath header to help calculate the magnitude of a complex number */

/* Add definition of 'add' member function */

bool Complex::equals(Complex other_complex) {
  // Return true if the real and imaginary parts of the complex numbers are
  // equal. False otherwise.
  return (re == other_complex.re && im == other_complex.im);
}