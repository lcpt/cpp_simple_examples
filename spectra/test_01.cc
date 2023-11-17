// To compile and run these examples, simply download the source code of Spectra and Eigen, and let the compiler know about their paths. For example:

// g++ -I/path/to/eigen -I/path/to/spectra/include -O2 example.cpp

#include <iostream>
#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <eigen3/unsupported/Eigen/ArpackSupport>


int main()
  {
    typedef Eigen::SparseMatrix<double> SparseMat;
    typedef Eigen::SimplicialLDLT<SparseMat> SparseChol;
    typedef Eigen::ArpackGeneralizedSelfAdjointEigenSolver <SparseMat, SparseChol> Arpack;
    Arpack arpack;
    typedef Eigen::Triplet<double> T;
    std::vector<T> tripletList;
    tripletList.reserve(4);
    tripletList.push_back(T(0,0,1.0));
    tripletList.push_back(T(1,1,2.0));
    tripletList.push_back(T(2,2,3.0));
    tripletList.push_back(T(0,0,2.0));
    tripletList.push_back(T(1,1,3.0));
    tripletList.push_back(T(2,2,4.0));
    // define sparse matrix A
    SparseMat A(3,3);
    A.setFromTriplets(tripletList.begin(), tripletList.end()); // mat is ready to go!
    // calculate the two smallest eigenvalues
    int nbrEigenvalues= 2;
    arpack.compute(A, nbrEigenvalues, "SM");
    // Retrieve results
    Eigen::VectorXd evalues= arpack.eigenvalues();
    
    std::cout << "arpack eigenvalues\n" << evalues.size()
	      << "\n " << evalues.transpose() << std::endl;
  }

