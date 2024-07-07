#include <boost/geometry.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

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
  }

