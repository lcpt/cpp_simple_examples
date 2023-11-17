// To compile and run these examples, simply download the source code of Spectra and Eigen, and let the compiler know about their paths. For example:

// g++ -I/path/to/eigen -I/path/to/spectra/include -O2 example.cpp

#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <Spectra/GenEigsSolver.h>
#include <Spectra/MatOp/SparseGenMatProd.h>
#include <iostream>
#include <deque>

using namespace Spectra;

int main()
{
    // A band matrix with 1 on the main diagonal, 2 on the below-main subdiagonal,
    // and 3 on the above-main subdiagonal
    const int n = 6;
    Eigen::SparseMatrix<double> M(n, n);

    typedef Eigen::Triplet<double> T;
    std::deque<T> tripletList;
    tripletList.push_back(T(0,0,1.0));
    tripletList.push_back(T(1,1,2.0));
    tripletList.push_back(T(2,2,3.0));
    tripletList.push_back(T(3,3,4.0));
    tripletList.push_back(T(4,4,5.0));
    tripletList.push_back(T(5,5,6.0));
    tripletList.push_back(T(0,0,2.0));
    tripletList.push_back(T(1,1,3.0));
    tripletList.push_back(T(2,2,4.0));
    tripletList.push_back(T(3,3,5.0));
    tripletList.push_back(T(4,4,6.0));
    tripletList.push_back(T(5,5,7.0));
    
    M.setFromTriplets(tripletList.begin(), tripletList.end()); // mat is ready to go!

    // Construct matrix operation object using the wrapper class SparseGenMatProd
    SparseGenMatProd<double> op(M);

    // Construct eigen solver object, requesting the smallest three eigenvalues
    GenEigsSolver<SparseGenMatProd<double>> eigs(op, 2, 4);

    // Initialize and compute
    eigs.init();
    int nconv = eigs.compute(SortRule::SmallestMagn);

    // Retrieve results
    Eigen::VectorXcd evalues;
    if(eigs.info() == CompInfo::Successful)
        evalues = eigs.eigenvalues();

    std::cout << "Eigenvalues found:\n" << evalues << std::endl;

    return 0;
}

