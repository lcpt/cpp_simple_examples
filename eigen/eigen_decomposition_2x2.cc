#include <iostream>
#include <eigen3/Eigen/Dense>
 
void eigen_decomposition_2x2(const double A[2][2], double V[2][2], double d[2])
  {
    Eigen::Matrix2d AA;
    AA << A[0][0], A[0][1], A[1][0], A[1][1];
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix2d> eigensolver(AA);
    if(eigensolver.info() != Eigen::Success)
      abort();
    else
      {
	auto eigenvalues= eigensolver.eigenvalues();
	auto eigenvectors= eigensolver.eigenvectors();
	const double lambda1= eigenvalues.col(0)[0];
	const double lambda2= eigenvalues.col(0)[1];
	const double v1x= eigenvectors(0,0);
	const double v1y= eigenvectors(1,0);
	const double v2x= eigenvectors(0,1);
	const double v2y= eigenvectors(1,1);
	
	d[0]= lambda1;
	V[0][0]= v1x; // first column of V
	V[1][0]= v1y;
	d[1]= lambda2;
	V[0][1]= v2x; // second column of V
	V[1][1]= v2y;
      }
  }

int main(void)
  {
    double V[2][2]= {{0.0, 0.0}, {0.0, 0.0}};
    double d[2]= {0.0, 0.0};
    double A[2][2]= {{204.167, 0.0}, {0.0, 0.0}};
    std::cout << "A= [[" << A[0][0] << ", " <<  A[0][1] << "]\n["
	      << A[1][0] << ", " << A[1][1] << "]]" << std::endl;
    eigen_decomposition_2x2(A, V, d);
    std::cout << "eigenvalue 1: " << d[0] << std::endl;
    std::cout << "eigenvector 1: [[" << V[0][0] << "][" <<  V[1][0] << "]]" << std::endl;
    std::cout << "eigenvalue 2: " << d[1] << std::endl;
    std::cout << "eigenvector 2: [[" << V[0][1] << "][" <<  V[1][1] << "]]" << std::endl;
    std::cout << "****************************************" << std::endl;
    double B[2][2]= {{0.0, 0.0}, {0.0, 204.167}};
    std::cout << "B= [[" << B[0][0] << ", " <<  B[0][1] << "]\n["
	      << B[1][0] << ", " << B[1][1] << "]]" << std::endl;
    eigen_decomposition_2x2(B, V, d);
    std::cout << "eigenvalue 1: " << d[0] << std::endl;
    std::cout << "eigenvector 1: [[" << V[0][0] << "][" <<  V[1][0] << "]]" << std::endl;
    std::cout << "eigenvalue 2: " << d[1] << std::endl;
    std::cout << "eigenvector 2: [[" << V[0][1] << "][" <<  V[1][1] << "]]" << std::endl;
  }
