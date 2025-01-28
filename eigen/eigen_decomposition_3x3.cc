#include <iostream>
#include <eigen3/Eigen/Dense>
 
void eigen_decomposition_3x3(const double A[3][3], double V[3][3], double d[3])
  {
    Eigen::Matrix3d AA;
    AA << A[0][0], A[0][1], A[0][2],
      A[1][0], A[1][1], A[1][1],
      A[2][0], A[2][1], A[2][1];
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver(AA);
    if(eigensolver.info() != Eigen::Success)
      abort();
    else
      {
	auto eigenvalues= eigensolver.eigenvalues();
	auto eigenvectors= eigensolver.eigenvectors();
	const double lambda1= eigenvalues.col(0)[0];
	const double lambda2= eigenvalues.col(0)[1];
	const double lambda3= eigenvalues.col(0)[2];
	const double v1x= eigenvectors(0,0);
	const double v1y= eigenvectors(1,0);
	const double v1z= eigenvectors(2,0);
	const double v2x= eigenvectors(0,1);
	const double v2y= eigenvectors(1,1);
	const double v2z= eigenvectors(2,1);
	const double v3x= eigenvectors(0,2);
	const double v3y= eigenvectors(1,2);
	const double v3z= eigenvectors(2,2);
	
	d[0]= lambda1;
	V[0][0]= v1x; // first column of V
	V[1][0]= v1y;
	V[2][0]= v1z;
	d[1]= lambda2;
	V[0][1]= v2x; // second column of V
	V[1][1]= v2y;
	V[2][1]= v2z;
	d[2]= lambda3;
	V[0][2]= v3x; // third column of V
	V[1][2]= v3y;
	V[2][2]= v3z;
      }
  }

int main(void)
  {
    double V[3][3]= {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    double d[3]= {0.0, 0.0, 0.0};
    double A[3][3]= {{204.167, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    std::cout << "A= [[" << A[0][0] << ", " <<  A[0][1] << ", " <<  A[0][2]
	      << "]\n["
	      << A[1][0] << ", " << A[1][1] << ", " << A[1][2]
	      << "]\n["
	      << A[2][0] << ", " << A[2][1] << ", " << A[2][2]
	      << "]]" << std::endl;
    eigen_decomposition_3x3(A, V, d);
    std::cout << "eigenvalue 1: " << d[0] << std::endl;
    std::cout << "eigenvector 1: [[" << V[0][0] << "][" <<  V[1][0] << "][" <<  V[2][0]  << "]]" << std::endl;
    std::cout << "eigenvalue 2: " << d[1] << std::endl;
    std::cout << "eigenvector 2: [[" << V[0][1] << "][" <<  V[1][1] << "][" <<  V[2][1]  << "]]" << std::endl;
    std::cout << "eigenvalue 3: " << d[2] << std::endl;
    std::cout << "eigenvector 3: [[" << V[0][2] << "][" <<  V[1][2] << "][" <<  V[2][2]  << "]]" << std::endl;
    std::cout << "****************************************" << std::endl;
    double B[3][3]=  {{0.0, 0.0, 0.0}, {0.0, 204.167, 0.0}, {0.0, 0.0, 0.0}};
    std::cout << "B= [[" << B[0][0] << ", " <<  B[0][1] << ", " <<  B[0][2]
	      << "]\n["
	      << B[1][0] << ", " << B[1][1] << ", " << B[1][2]
	      << "]\n["
	      << B[2][0] << ", " << B[2][1] << ", " << B[2][2]
	      << "]]" << std::endl;
    eigen_decomposition_3x3(B, V, d);
    std::cout << "eigenvalue 1: " << d[0] << std::endl;
    std::cout << "eigenvector 1: [[" << V[0][0] << "][" <<  V[1][0] << "][" <<  V[2][0]  << "]]" << std::endl;
    std::cout << "eigenvalue 2: " << d[1] << std::endl;
    std::cout << "eigenvector 2: [[" << V[0][1] << "][" <<  V[1][1] << "][" <<  V[2][1]  << "]]" << std::endl;
    std::cout << "eigenvalue 3: " << d[2] << std::endl;
    std::cout << "eigenvector 3: [[" << V[0][2] << "][" <<  V[1][2] << "][" <<  V[2][2]  << "]]" << std::endl;
    std::cout << "****************************************" << std::endl;
    double C[3][3]=  {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 204.167}};
    std::cout << "C= [[" << C[0][0] << ", " <<  C[0][1] << ", " <<  C[0][2]
	      << "]\n["
	      << C[1][0] << ", " << C[1][1] << ", " << C[1][2]
	      << "]\n["
	      << C[2][0] << ", " << C[2][1] << ", " << C[2][2]
	      << "]]" << std::endl;
    eigen_decomposition_3x3(C, V, d);
    std::cout << "eigenvalue 1: " << d[0] << std::endl;
    std::cout << "eigenvector 1: [[" << V[0][0] << "][" <<  V[1][0] << "][" <<  V[2][0]  << "]]" << std::endl;
    std::cout << "eigenvalue 2: " << d[1] << std::endl;
    std::cout << "eigenvector 2: [[" << V[0][1] << "][" <<  V[1][1] << "][" <<  V[2][1]  << "]]" << std::endl;
    std::cout << "eigenvalue 3: " << d[2] << std::endl;
    std::cout << "eigenvector 3: [[" << V[0][2] << "][" <<  V[1][2] << "][" <<  V[2][2]  << "]]" << std::endl;
  }
