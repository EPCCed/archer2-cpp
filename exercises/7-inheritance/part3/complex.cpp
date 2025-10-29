#include "complex.hpp"
#include <cmath>

Complex::Complex(double real) : re(real) {
}

Complex::Complex(double real, double imag) : re(real), im(imag) {
}

double Complex::real() {
  // Return real component
}

/* Add definition of a member function to access the imaginary component */

Complex Complex::conj() {
  // Return complex conjugate
}

/* Add definition of 'norm' member function. Hint: Look up std::sqrt from the
cmath header to help calculate the magnitude of a complex number */

/* Add definition of 'add' member function */

bool Complex::equals(Complex other_complex) {
  // Return true if the real and imaginary parts of the complex numbers are
  // equal. False otherwise.
}