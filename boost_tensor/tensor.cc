#include <boost/numeric/ublas/tensor.hpp>

typedef boost::numeric::ublas::tensor<double> t_double;
int main ()
  {
    using namespace boost::numeric::ublas;
    t_double t{4,2,3};
    for (auto k = 0ul; k < t.size (2); ++ k)
      for (auto j = 0ul; j < t.size (1); ++ j)
        for (auto i = 0ul; i < t.size (0); ++ i)
          t.at(i,j,k) = 3*i + 2*j + 5*k;
        
    std::cout << t << std::endl;
    t*= 2.0;
    std::cout << t << std::endl;
    t_double sum(t+t);
    t_double prod= (-2.0)*t;
    t_double dif= sum-(2.0*t);
    std::cout << dif << std::endl;
    dif= 4.0;
    std::cout << dif << std::endl;
      
  }
