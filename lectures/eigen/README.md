template: titleslide
# Linear Algebra for C++ (using Eigen)
## Joseph Lee, EPCC
## j.lee@epcc.ed.ac.uk

---
# Source

Original: 
- Chris Richardson (chris@bpi.cam.ac.uk)
- Rupert Nash (r.nash@epcc.ed.ac.uk)
---

# Rundown

- C++ Linear Algebra libraries: what and why?

- Eigen3:
  
  - Getting started
  
  - Matrices: Dense, Sparse, Geometry
  
  - Solvers: Dense, Sparse, Iterative
  
  - General notes
  
  - Diffusion equation demo + exercise
  

---

# Linear Algebra: What do we need?

__What for?__

- Scientific computing, PDE, simulations, finance, graphics, ML and more

__What we expect?__

Object types:

- Vectors

- Matrix: (Dense / Sparse / Diagonal / Symmetric / Column/Row major)

- Operations: Matrix (Multiplication/transpose/geometric rotation)

- Solvers (`\(Ax = b\)`, Eigenvalues) : Direct (LU/QR factorization) / Indirect (CG)

Numeric types: 

- `complex<float>` `complex<double>`
---

# Why use a library?

- Simple & easy to use : clean API
  
- Fast Performance
  
- Correctness
  
- Expressiveness
  
- Don’t reinvent the wheel

---

# Linear Algebra on C++

- Simple: **Eigen**
  
- Big & popular: **PETSc** (C)
  
- Standard: **LAPACK/LAPACK++/ScaLAPACK**

- GPU: Nvidia/AMD **(cu/roc)(BLAS/SPARSE/SOLVER)**
  
- CPU: **Intel MKL**, **OpenBLAS**
  
- Future: C++26 std library?
  
- vs: Python Numpy/Scipy
  
- <https://en.cppreference.com/w/cpp/links/libs>
- <https://en.wikipedia.org/wiki/Comparison_of_linear_algebra_libraries>
---

# Eigen3

## Numpy, but C++

“Header only” no library to link
 - `g++ -I /path/to/eigen/ my_program.cpp -o my_program`
  
Contains optimisation for ARM & Intel processors (Vectorization - SIMD instructions)
  
Easy to use interface
  
Support for dense and sparse matrices, vectors, and “arrays” (coefficient-wise ops)
  
Support for some solvers
  
Download from <https://eigen.tuxfamily.org> or e.g. apt install libeigen3-dev

---

# Matrix: Basic

```C++
#include <Eigen/Dense>

int main()
{
   Eigen::Matrix<double, 10, 10> A;
   A.setZero();
   A(9, 0) = 1.234;
   std::cout << A << std::endl;
   return 0;
}
```

This is pretty similar to `double A[10][10];`

---
# Dynamic size

```C++
int n = 64;
int m = 65;
Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> A(n, m);

A.resize(20, 20);

std::cout << “Size is ”;
std::cout << A.rows() << “ x ” << A.cols() << std::endl;
```

So this is more like a 2D version of `std::vector<double>`

---
# Convenience typedefs
```C++
MatrixNt  = Matrix<type, N, N>
MatrixXNt = Matrix<type, Dynamic, N>
MatrixNXt = Matrix<type, N, Dynamic>
VectorNt  = Matrix<type, N, 1>
RowVectorNt = Matrix<type, 1, N>
```
```
N = {2, 3, 4, X = dynamic}
t = {i = int, f = float, d = double, cf = complex<float>, cd = complex<double>}
```
e.g.:
- `Matrix3d` = 3x3 double matrix
- `Matrix3i` = 3x3 int  matrix
- `MatrixXd` = (Dynamic)x(Dynamic) double matrix
- `VectorXd` = (Dynamic) double vector

---
# Matrix arithmetics

```C++
Eigen::MatrixXd A(5, 10);
Eigen::MatrixXd B(10, 2);
Eigen::VectorXd vec(10);

Eigen::MatrixXd C = A * B;
Eigen::VectorXd w = A * vec;
```

More:

Dot product: `v.dot(w)`

Cross product: `v.cross(w)`

Transpose: `A.transpose()`

Set constant:
`A.setZeros(rows, cols)`, `A.setOnes(rows, cols)`, `A.setConstant(rows, cols, value)`, `A.setRandom(rows, cols)`

---
#  Element-wise ops with `Array`s

For example:
```C++
Eigen::Matrix3d A, B;
// set all values to 2.0
A.array() = 2.0;

// set each element of A to sin() of the same element in B
A.array() = B.array().sin();

Eigen::Array3d W;
W = W * A;  // Error - cannot mix Array with Matrix
```

---
# View other data as a `Matrix` or `Array`

Mix and match with `std::vector` or any contiguous layout

It is easy to “overlay” existing memory with an Eigen `Array` or `Matrix`:

```C++
std::vector<double> a(1000);

Eigen::Map<Eigen::Matrix<double, 100, 10>> a_eigen(a.data());

a_eigen(10, 0) = 1.0;

Eigen::Map<Eigen::MatrixXd> a2_eigen(a.data(), 10, 100);
```
---
# Sparse matrix: Basic

When dealing with very large matrices with many zeros (e.g. from Differential Equations), store as sparse matrices

```C++
#include <Eigen/Sparse>

SparseMatrix<std::complex<float> > mat(1000,2000); 
// declares a 1000x2000 column-major compressed sparse matrix of complex<float>

SparseMatrix<double,RowMajor> mat(1000,2000); 
// declares a 1000x2000 row-major compressed sparse matrix of double

SparseVector<std::complex<float> > vec(1000);
// declares a column sparse vector of complex<float> of size 1000

SparseVector<double,RowMajor> vec(1000); 
// declares a row sparse vector of double of size 1000
```

---
# Sparse matrix
Simplest way to create a sparse matrix is to build a triplet:
```C++
typedef Triplet<double> T;
std::vector<T> tripletList;
tripletList.reserve(estimation_of_entries);
for(...)
{
// ...
tripletList.push_back(T(i,j,v_ij));
}
SparseMatrixType m(rows,cols);
m.setFromTriplets(tripletList.begin(), tripletList.end());
// m is ready to go!
```
Operators:
- Sparse: `SM.transpose()`, `SM.adjoint()`…
- Sparse-Sparse: `SM1 + SM2`, `SM1 *SM2` …
- Sparse-Dense: `DM2 = DM1 + SM1` , `DM2 = SM1* DM2`

---
# Matrix: Geometry

```C++
#include <Eigen/Geometry>
```
- 2D Rotations: 
```C++ 
 Rotation2D<float> rot2(angle_in_radian)
 ```
- 3D Rotaions: 
```C++
AngleAxis<float> AA(angle_in_radian, Vector3f(ax,ay,az))
```
- Quarternion, ND-Transformations…

---
# Solvers

Simple example: `\(Ax = b\)`
```C++
#include <iostream>
#include <Eigen/Dense>

int main()
{
    Eigen::Matrix3f A;
    Eigen::Vector3f b;
    A << 1,2,3, 4,5,6, 7,8,10;
    b << 3, 3, 4;
    std::cout << "Here is the matrix A:\n" << A << std::endl;
    std::cout << "Here is the vector b:\n" << b << std::endl;
    Eigen::Vector3f x = A.colPivHouseholderQr().solve(b); #HERE
    std::cout << "The solution is:\n" << x << std::endl;
}
```
2 steps:
- Decompose
- Solve

---
# Decompositions:

E.g. 
- PartialPivLU
  
- FullPivLU
  
- HouseholderQR
  
- ColPivHousehoulderQR

Varying matrix requirements, speed, reliability, accuracy, optimization


<https://eigen.tuxfamily.org/dox/group__TopicLinearAlgebraDecompositions.html>
<https://eigen.tuxfamily.org/dox/group__DenseDecompositionBenchmark.html>
---
# Other solvers
### Singular values
E.g. JacobiSVD, BDCSVD
  
### Eigenvalues/vectors
E.g. SelfAdjointEigenSolver, ComplexEigenSolver

### Sparse Solver
E.g. SparseLU, SparseQR, SimplicialLLT, SimplicialLDLT 

---

# Iterative Solvers

```C++
#include <Eigen/IterativeLinearSolvers>
```
Useful for solving `\(Ax = b\)` where `\(A\)` is large and sparse

E.g.
- ConjugateGradient
 
- LeastSquaresConjugateGradient

- BICGSTAB
  
Use with preconditioner

---
# General Notes:
Eigen does a lot of checks in debug mode:

- Turn optimisation on: `-O2` etc

- Turn off debug: `-DNDEBUG`

Can use external BLAS/LAPACK library (e.g. MKL, OpenBLAS) by enabling macro

- e.g. `EIGEN_USE_BLAS`
---
# Demo: diffusion equation

Solve diffusion equation

$$\frac{\partial T}{\partial t} = k \frac{\partial^2 T}{\partial x^2}$$

in 1D using an explicit method

Each timestep can be iterated by using `\(T_{n+1} = A T_n\)`

1. Create an initial vector for `\(T\)`
   
2. Create a dense matrix for `\(A\)`
   
3. Matrix multiply `\(A\)` several times


See `exercises/eigen/explicit.cpp`

---
# Diffusion equation (explicit) 

Subscript means time, square brackets position

`$$T_{n+1}[i] = T_n[i] + \frac{k \Delta t}{\Delta x^2}(T_n[i-1] - 2T_n[i] + T_n[i+1])$$`

Our matrix equation is now:

`$$T_{n+1} = A.T_{n}$$`

Left-hand side is unknown (next time step)

Let: `\(\delta = k\Delta t/ \Delta x^2\)`

```
A = [ 1-ẟ ẟ    0    0    0 …        ]
    [ ẟ   1-2ẟ ẟ    0    0 …        ]
    [ 0   ẟ    1-2ẟ ẟ    0 …        ]
    [ 0   0    ẟ    1-2ẟ ẟ    0  0 …] 
    [ 0   0    0    ẟ    1-2ẟ ẟ  0 …]
	
```
---
# Code:

```C++ 
    int n = 20;
    int steps = 200;
    std::vector<double> Avec(n * n);
```
```C++
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
```

```C++
// T_n
    Eigen::VectorXd b(n);
    b.setZero();
    b.head(n / 2).array() = 1.0;
```
---
# Diffusion equation (implicit)
More stable: <https://en.wikipedia.org/wiki/Explicit_and_implicit_methods>

Subscript means time, square brackets position

`$$T_{n+1}[i] - \frac{k \Delta t}{\Delta x^2} (T_{n+1}[i-1] - 2*T_{n+1}[i] + T_{n+1}[i+1]) = T[i]$$`

Left-hand side is unknown (next time step)
`$$A.T_{n+1} = T_n$$`

```
A = [ 1+ẟ   -ẟ     0      0       0     …] 
    [ -ẟ   1+2ẟ   -ẟ      0       0     …]
    [ 0     -ẟ   1+2ẟ    -ẟ       0     …]
    [ 0      0    -ẟ    1+2ẟ      -ẟ    …] 
    [ 0      0     0     -ẟ      1+2ẟ   …]
 
```
The matrix A is very similar - just flip the sign of the delta terms

---
# Exercise: Diffusion equation (sparse)

Hints:

```C++
#include <Eigen/Sparse>
```
```C++
std::vector<Eigen::Triplet<double>> fill;
    fill.reserve(...);
```
```C++
for (int i = 0; i < n - 1; ++i)
    {
        fill.push_back(Eigen::Triplet<double>(...);
        ...
    }
```
```C++
A.setFromTriplets(fill.begin(), fill.end());
```

See `exercises/eigen/sparse.cpp`