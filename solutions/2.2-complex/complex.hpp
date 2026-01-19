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
  double real() const;
  double imag() const;

  // Compute the complex conjugate
  Complex conj() const;

  // Compute the magnitude and squared magnitude
  double norm() const;
  double norm2() const;

  // Declare comparisons
  friend bool operator==(Complex const& a, Complex const& b);
  friend bool operator!=(Complex const& a, Complex const& b);

  // Declare binary arithmetic operators
  friend Complex operator+(Complex const& a, Complex const& b);
  friend Complex operator-(Complex const& a, Complex const& b);
  friend Complex operator*(Complex const& a, Complex const& b);
  friend Complex operator/(Complex const& a, Complex const& b);
  // Question: how would you declare multiplication and division by a real number?
  friend Complex operator*(Complex const& a, double const& b);
  friend Complex operator*(double const& a, Complex const& b);

  // Unary negation
  friend Complex operator-(Complex const& a);

private:
  double re = 0.0;
  double im = 0.0;
};


#endif
