#ifndef CPPEX_COMPLEX_COMPLEX_HPP
#define CPPEX_COMPLEX_COMPLEX_HPP

// Simple complex number class
template <typename T>
class Complex {
public:
  // Default value is zero
  Complex() = default;
  Complex(T real);
  Complex(T real, T imag);

  // Access components
  T real() const;
  T imag() const;

  // Compute the complex conjugate
  Complex conj() const;

  // Compute the magnitude and squared magnitude
  double norm() const;
  T norm2() const;

  // Declare comparisons
  template <typename U, typename V>
  friend bool operator==(Complex<U> const& a, Complex<V> const& b);
  template <typename U, typename V>
  friend bool operator!=(Complex<U> const& a, Complex<V> const& b);

  // Declare binary arithmetic operators
  template <typename U>
  friend Complex<U> operator+(Complex<U> const& a, Complex<U> const& b);
  template <typename U>
  friend Complex<U> operator-(Complex<U> const& a, Complex<U> const& b);
  template <typename U>
  friend Complex<U> operator*(Complex<U> const& a, Complex<U> const& b);
  template <typename U>
  friend Complex<U> operator/(Complex<U> const& a, Complex<U> const& b);

  // Unary negation
  template <typename U>
  friend Complex<U> operator-(Complex<U> const& a);

private:
  T re = 0.0;
  T im = 0.0;
};

template <typename T>
Complex<T>::Complex(T real) : re(real) {}

template <typename T>
Complex<T>::Complex(T real, T imag) : re(real), im(imag) {}

template <typename T>
T Complex<T>::real() const {
  return re;
}

template <typename T>
T Complex<T>::imag() const {
  return im;
}

template <typename T>
Complex<T> Complex<T>::conj() const {
  return Complex<T>{re, -im};
}

template <typename T>
double Complex<T>::norm() const {
  return std::sqrt(norm2());
}

template <typename T>
T Complex<T>::norm2() const {
  return re*re + im*im;
}

template <typename U, typename V>
bool operator==(Complex<U> const& a, Complex<V> const& b) {
  return (a.re == b.re) && (a.im == b.im);
}

template <typename U, typename V>
bool operator!=(Complex<U> const& a, Complex<V> const& b) {
  return !(a == b);
}

template <typename T>
Complex<T> operator+(Complex<T> const& a, Complex<T> const& b) {
  return Complex<T>{a.re + b.re, a.im + b.im};
}

template <typename T>
Complex<T> operator-(Complex<T> const& a, Complex<T> const& b) {
  return Complex<T>{a.re - b.re, a.im - b.im};
}

template <typename T>
Complex<T> operator*(Complex<T> const& a, Complex<T> const& b) {
  return Complex<T>{a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
}

template <typename T>
Complex<T> operator-(Complex<T> const& a) {
  return Complex<T>{-a.re, -a.im};
}

#endif
