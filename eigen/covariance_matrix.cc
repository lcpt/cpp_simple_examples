#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

MatrixXd computeCovarianceMatrix(const MatrixXd& data) {
    // Calculate the mean of each column
    RowVectorXd mean = data.colwise().mean();
    
    // Subtract the mean from each column
    MatrixXd centered = data.rowwise() - mean;
    
    // Compute the covariance matrix
    MatrixXd cov = (centered.adjoint() * centered) / double(data.rows() - 1);
    
    return cov;
}

int main() {
    // Example data: 4 samples with 3 variables each
    MatrixXd data(4, 3);
    data << 4.0, 2.0, 0.6,
            4.2, 2.1, 0.59,
            3.9, 2.0, 0.58,
            4.3, 2.1, 0.62;

    cout << "Data matrix:" << endl << data << endl << endl;

    // Compute the covariance matrix
    MatrixXd covMatrix = computeCovarianceMatrix(data);

    cout << "Covariance matrix:" << endl << covMatrix << endl;

    return 0;
}
