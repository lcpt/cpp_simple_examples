#include <boost/geometry.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <iostream>

int main(void)
  {
    namespace bg = boost::geometry;
    typedef boost::geometry::model::d2::point_xy<double> point_xy;
    typedef boost::geometry::model::polygon<point_xy> polygon_type;

    std::vector< point_xy > pointList; // Store points in vector so we can assign them to a polygon
    pointList.push_back(point_xy(0,0));
    pointList.push_back(point_xy(1,0));
    pointList.push_back(point_xy(1,1));
    pointList.push_back(point_xy(0,1));
    // create polygon
    polygon_type poly;
    // assign points to polygon
    boost::geometry::assign_points(poly, pointList);


    //getting the vertices back
    for(auto it = boost::begin(boost::geometry::exterior_ring(poly)); it != boost::end(boost::geometry::exterior_ring(poly)); ++it)
      {
	const double x = boost::geometry::get<0>(*it);
	const double y = boost::geometry::get<1>(*it);
	std::cout << "x= " << x << " y= " << y << std::endl;
      }
  }
