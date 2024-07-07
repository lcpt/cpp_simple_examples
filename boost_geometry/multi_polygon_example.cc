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
    // create first polygon
    polygon_type poly1;
    // assign points to polygon
    boost::geometry::assign_points(poly1, pointList);

    // create another polygon.
    pointList.clear();
    pointList.push_back(point_xy(5,5));
    pointList.push_back(point_xy(6,5));
    pointList.push_back(point_xy(6,6));
    pointList.push_back(point_xy(5,6));
    // create first polygon
    polygon_type poly2;
    // assign points to polygon
    boost::geometry::assign_points(poly2, pointList);
    
    // Add polygon to multi-polygon.
    multi_polygon_type polygons;
    polygons.push_back(poly1);
    polygons.push_back(poly2);
  }

