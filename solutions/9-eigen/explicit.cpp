#include <Eigen/Dense>

#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    int n = 20;
    int steps = 200;
    std::vector<double> Avec(n * n);


    // Set up matrix A
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

    std::cout << "A = \n" << A << std::endl
              << std::endl;


    // T_n
    Eigen::VectorXd b(n);
    b.setZero();
    b.head(n / 2).array() = 1.0;

    std::ofstream f;
    f.open("explicit_sim.txt");
    for (int i = 0; i < steps; ++i)
    {
        f << b.transpose() << std::endl;
        // update time-step T_{n+1} = A.T_{n}
        b = A * b;
    }

    std::cout << b.transpose() << std::endl;

    return 0;
}