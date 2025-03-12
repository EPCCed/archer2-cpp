#ifndef CPPEX_COMPLEX_COMPLEX_HPP
#define CPPEX_COMPLEX_COMPLEX_HPP

// Simple complex number class
/* Add template typename definition here */
class Complex {
public:
  // Default value is zero
  Complex() = default;
  Complex(double real);
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
  /* What if I want to add a Complex<double> to a Complex<int>?
     What would be returned in this case? What should the return type
     be to make this flexible?
  */
  friend Complex operator+(Complex const& a, Complex const& b);
  friend Complex operator-(Complex const& a, Complex const& b);
  friend Complex operator*(Complex const& a, Complex const& b);
  friend Complex operator/(Complex const& a, Complex const& b);
  // Question: how would you declare multiplication and division by a real number?

  // Unary negation
  friend Complex operator-(Complex const& a);

private:
  double re = 0.0;
  double im = 0.0;
};


#endif
