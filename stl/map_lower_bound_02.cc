// map::lower_bound/upper_bound
#include <iostream>
#include <map>

int main ()
{
  std::map<double,int> mymap;
  std::map<double,int>::iterator itlow,itup;

  mymap[0.0]=20;
  mymap[1.0]=40;
  mymap[2.0]=60;
  mymap[3.0]=80;
  mymap[4.0]=100;

  itlow= mymap.lower_bound (2.0);  // itlow points to 2.0
  itup= mymap.upper_bound (3.0);   // itup points to 4.0 (not 3.0!)

  std::cout << "mymap.lower_bound (2.0)= " << (*itlow).first << "->" << (*itlow).second << std::endl;
  std::cout << "mymap.upper_bound (3.0)= " << (*itup).first << "->" << (*itup).second << std::endl;

  return 0;
}
