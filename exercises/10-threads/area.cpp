#include <cstdio>
#include <complex>
#include <chrono>

using complex = std::complex<double>;

// Determine if a complex number is inside the set
bool in_mandelbrot(const complex& c) {
  const auto MAXITER = 2000;
  auto z = c;
  for (auto i = 0; i < MAXITER; ++i) {
    z = z*z + c;
    if (std::norm(z) > 4.0)
      return false;
  }
  return true;
}

int main() {
  const auto NPOINTS = 2000;

  const auto scale_real = 2.5;
  const auto scale_imag = 1.125;
  const auto eps = 1.0e-7;
  const auto shift = complex{-2.0 + eps, 0.0 + eps};
  using clock = std::chrono::high_resolution_clock;
  auto start = clock::now();

  // Outer loops run over npoints, initialise z=c
  // Inner loop has the iteration z=z*z+c, and threshold test
  int num_inside = 0;
  for (int i = 0; i < NPOINTS; ++i) {
    for (int j = 0; j < NPOINTS; ++j) {
      const auto c = shift + complex{(scale_real * i) / NPOINTS,
                                     (scale_imag * j) / NPOINTS};
      if (in_mandelbrot(c))
	num_inside++;
    }
  }
  auto finish = clock::now();

  // Calculate area and error and output the results
  auto area = 2.0 * scale_real * scale_imag * double(num_inside) / double(NPOINTS * NPOINTS);
  auto error = area / double(NPOINTS);

  std::printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n", area, error);
  auto dt = std::chrono::duration<double>(finish-start);
  std::printf("Time = %12.8f seconds\n", dt.count());
}
