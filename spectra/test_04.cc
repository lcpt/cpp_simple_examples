// To compile and run these examples, simply download the source code of Spectra and Eigen, and let the compiler know about their paths. For example:

// g++ -I/path/to/eigen -I/path/to/spectra/include -O2 example.cpp

#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <Spectra/SymGEigsShiftSolver.h>
#include <Spectra/MatOp/SymShiftInvert.h>
#include <Spectra/MatOp/SparseSymMatProd.h>
#include <iostream>
 
using namespace Spectra;
 
int main()
{
    // We are going to solve the generalized eigenvalue problem
    //     A * x = lambda * B * x,
    // where A is symmetric and B is positive definite
    const int n = 100;
 
    // Define the A matrix
    Eigen::MatrixXd M = Eigen::MatrixXd::Random(n, n);
    Eigen::MatrixXd A = M + M.transpose();
 
    // Define the B matrix, a tridiagonal matrix with 2 on the diagonal
    // and 1 on the subdiagonals
    Eigen::SparseMatrix<double> B(n, n);
    B.reserve(Eigen::VectorXi::Constant(n, 3));
    for (int i = 0; i < n; i++)
    {
        B.insert(i, i) = 2.0;
        if (i > 0)
            B.insert(i - 1, i) = 1.0;
        if (i < n - 1)
            B.insert(i + 1, i) = 1.0;
    }
 
    // Construct matrix operation objects using the wrapper classes
    // A is dense, B is sparse
    using OpType = SymShiftInvert<double, Eigen::Dense, Eigen::Sparse>;
    using BOpType = SparseSymMatProd<double>;
    OpType op(A, B);
    BOpType Bop(B);
 
    // Construct generalized eigen solver object, seeking three generalized
    // eigenvalues that are closest to zero. This is equivalent to specifying
    // a shift sigma = 0.0 combined with the SortRule::LargestMagn selection rule
    SymGEigsShiftSolver<OpType, BOpType, GEigsMode::ShiftInvert>
        geigs(op, Bop, 3, 6, 0.0);
 
    // Initialize and compute
    geigs.init();
    int nconv = geigs.compute(SortRule::LargestMagn);
 
    // Retrieve results
    Eigen::VectorXd evalues;
    Eigen::MatrixXd evecs;
    if (geigs.info() == CompInfo::Successful)
    {
        evalues = geigs.eigenvalues();
        evecs = geigs.eigenvectors();
    }
 
    std::cout << "Number of converged generalized eigenvalues: " << nconv << std::endl;
    std::cout << "Generalized eigenvalues found:\n" << evalues << std::endl;
    std::cout << "Generalized eigenvectors found:\n" << evecs.topRows(10) << std::endl;
 
    return 0;
}
