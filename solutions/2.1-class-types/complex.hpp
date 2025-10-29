#ifndef CPPEX_COMPLEX_COMPLEX_HPP
#define CPPEX_COMPLEX_COMPLEX_HPP

// Simple complex number class
class Complex {
public:
  // Default value is zero
  Complex() = default;
  // Construct purely real complex
  Complex(double real);
  // Construct from real and imaginary parts
  Complex(double real, double imag);

  // Access components
  double real();
  double imag();

  // Compute the complex conjugate
  Complex conj();

  // Compute the magnitude
  double norm();

  // Add two complex numbers
  Complex add(Complex other_complex);

  // Check if two complex numbers are equal
  bool equals(Complex other_complex);

private:
  double re = 0.0;
  double im = 0.0;
};

#endif
