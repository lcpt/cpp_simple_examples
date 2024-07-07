#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <iostream>

int main(void)
  {
    typedef boost::geometry::model::d2::point_xy<double> point_xy;
    typedef boost::geometry::model::polygon<point_xy> polygon_type;
    typedef boost::geometry::model::multi_polygon<polygon_type> multi_polygon_type;

    std::vector< point_xy > pointList; // Store points in vector so we can assign them to a polygon
    pointList.push_back(point_xy(0,0));
    pointList.push_back(point_xy(1,0));
    pointList.push_back(point_xy(1,1));
    pointList.push_back(point_xy(0,1));
    // create polygon
    polygon_type poly;
    // assign points to polygon
    boost::geometry::assign_points(poly, pointList);
    
    // Declare strategies
    const double buffer_distance = 0.25;
    const int points_per_circle = 36;
    boost::geometry::strategy::buffer::distance_symmetric<double> distance_strategy(buffer_distance);
    boost::geometry::strategy::buffer::join_round join_strategy(points_per_circle);
    boost::geometry::strategy::buffer::end_round end_strategy(points_per_circle);
    boost::geometry::strategy::buffer::point_circle circle_strategy(points_per_circle);
    boost::geometry::strategy::buffer::side_straight side_strategy;
    
    // Declare output
    boost::geometry::model::multi_polygon<polygon_type> result;
    
    // Create the buffer of a multi polygon
    boost::geometry::buffer(poly, result,
                distance_strategy, side_strategy,
                join_strategy, end_strategy, circle_strategy);

    const size_t numPolygons= result.size();
    std::cout << "numPolygons= " << numPolygons << std::endl;
    
    return 0;
  }
