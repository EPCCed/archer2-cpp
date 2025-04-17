#include <Eigen/Dense>

#include <fstream>
#include <iostream>
#include <vector>

int main()
{
  int n = 12;

  std::vector<double> Avec(n * n);

  Eigen::Map<Eigen::MatrixXd> A(Avec.data(), n, n);
  A = Eigen::MatrixXd::Identity(n, n);

  double delta = 0.4;

  for (int i = 0; i < n - 1; ++i)
  {
    A(i + 1, i) += delta;
    A(i + 1, i + 1) += -delta;

    A(i, i) += -delta;
    A(i, i + 1) += +delta;
  }

  std::cout << A << std::endl << std::endl;

  Eigen::VectorXd b(n);
  b.setZero();
  b.head(n / 2).array() = 1.0;

  std::ofstream f;
  f.open("a.txt");
  for (int i = 0; i < 20; ++i)
  {
    std::cout << b.transpose() << std::endl;
    f << b << std::endl << std::endl << std::endl;
    b = A * b;
  }

  std::cout << b.transpose() << std::endl;

  return 0;
}
