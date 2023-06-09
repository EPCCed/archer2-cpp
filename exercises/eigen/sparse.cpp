#include <Eigen/Dense>
#include <Eigen/Sparse>

#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    int n = 20;
    int steps = 200;

    Eigen::SparseMatrix<double> A;
    A.resize(n, n);

    double delta = 0.4;

    std::vector<Eigen::Triplet<double>> fill;
    fill.reserve(n * 4);

    for (int i = 0; i < n - 1; ++i)
    {
        fill.push_back(Eigen::Triplet<double>(i + 1, i, delta));
        fill.push_back(Eigen::Triplet<double>(i + 1, i + 1, -delta));
        fill.push_back(Eigen::Triplet<double>(i, i, 1.0 - delta));
        fill.push_back(Eigen::Triplet<double>(i, i + 1, delta));
    }
    fill.push_back(Eigen::Triplet<double>(n - 1, n - 1, 1.0));
    A.setFromTriplets(fill.begin(), fill.end());

    std::cout << A << std::endl;

    Eigen::VectorXd b(n);
    b.head(n / 2).array() = 1.0;
    b.tail(n / 2).array() = 0.0;

    std::cout << b.transpose() << std::endl;

    std::ofstream f;
    f.open("sparse_sim.txt");
    for (int i = 0; i < steps; ++i)
    {
        f << b.transpose() << std::endl;
        b = A * b;
    }

    std::cout << b.transpose() << std::endl;

    return 0;
}