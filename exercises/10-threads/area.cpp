#include <cstdio>
#include <complex>
#include <chrono>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>

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

void area(
  int start,
  int stop,
  int npoints,
  double scale_real,
  double scale_imag,
  int& num_inside,
  std::mutex& mutex
) {
  const auto eps = 1.0e-7;
  const auto shift = complex{-2.0 + eps, 0.0 + eps};

  for (int i = start; i < stop; ++i) {
    for (int j = 0; j < npoints; ++j) {
      const auto c = shift + complex{
        (scale_real * i) / npoints,
        (scale_imag * j) / npoints
      };
      if (in_mandelbrot(c)) {
        mutex.lock();
        num_inside++;
        mutex.unlock();
      }
    }
  }
}

int main() {
  const auto NPOINTS = 2000;
  const auto scale_real = 2.5;
  const auto scale_imag = 1.125;
  
  using clock = std::chrono::high_resolution_clock;
  auto start = clock::now();

  std::mutex mutex;
  int num_inside = 0;

  int n_threads = 16;
  std::vector<std::thread> threads;

  int points_per_thread = NPOINTS / n_threads;
  int i = 0;
  int j = 0;

  for (int id = 0; id < n_threads; ++id) {
    i = id * points_per_thread;
    j = i + points_per_thread;
    threads.push_back(
      std::thread(
        area, i, j, NPOINTS, scale_real, scale_imag, std::ref(num_inside), std::ref(mutex)
      )
    );
  }

  // Wait for all threads to finish
  for (auto&& thread : threads) {
    thread.join();
  }

  auto finish = clock::now();

  // Calculate area and error and output the results
  auto area = 2.0 * scale_real * scale_imag * double(num_inside) / double(NPOINTS * NPOINTS);
  auto error = area / double(NPOINTS);

  std::printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n", area, error);
  auto dt = std::chrono::duration<double>(finish-start);
  std::printf("Time = %12.8f seconds\n", dt.count());
}
