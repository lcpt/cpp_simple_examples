#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <iostream>

int main(void)
  {
    typedef boost::geometry::model::d2::point_xy<double> point;
    typedef boost::geometry::model::polygon<point> polygon;

    // Declare strategies
    const double buffer_distance = 1.0;
    const int points_per_circle = 36;
    boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy(buffer_distance);
    boost::geometry::strategy::buffer::join_round join_strategy(points_per_circle);
    boost::geometry::strategy::buffer::end_round end_strategy(points_per_circle);
    boost::geometry::strategy::buffer::point_circle circle_strategy(points_per_circle);
    boost::geometry::strategy::buffer::side_straight side_strategy;


    // Define polygons.
    std::vector< point > pointListA; // Store points in vector so we can assign them to a polygon
    pointListA.push_back(point(0,1));
    pointListA.push_back(point(2,5));
    pointListA.push_back(point(5,3));
    pointListA.push_back(point(0,1));
    
    // create polygon
    polygon polA;
    // assign points to polygon
    boost::geometry::assign_points(polA, pointListA);

    // Declare output
    boost::geometry::model::multi_polygon<polygon> result;
    
    // Declare/fill a multi_polygon
    boost::geometry::model::multi_polygon<polygon> mpol;
    mpol.push_back(polA);

    // Create the buffer of a multi polygon
    boost::geometry::buffer(polA, result,
                distance_strategy, side_strategy,
                join_strategy, end_strategy, circle_strategy);

    std::cout << "numPolygons= " << result.size() << std::endl;

    polygon poly= result[0];
    //getting the vertices back
    for(auto it = boost::begin(boost::geometry::exterior_ring(poly)); it != boost::end(boost::geometry::exterior_ring(poly)); ++it)
      {
	const double x = boost::geometry::get<0>(*it);
	const double y = boost::geometry::get<1>(*it);
	std::cout << "x= " << x << " y= " << y << std::endl;
      }

    return 0;
  }
