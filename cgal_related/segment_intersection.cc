// Author : Pierre Alliez
#include <iostream>
#include <list>
#include <vector>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_segment_primitive.h>
typedef CGAL::Simple_cartesian<double> K;
typedef K::FT FT;
typedef K::Point_3 Point;
typedef K::Plane_3 Plane;
typedef K::Segment_3 Segment;
typedef K::Triangle_3 Triangle;
typedef std::vector<Segment> SegmentVector;
typedef SegmentVector::iterator Iterator;
typedef SegmentVector::const_iterator ConstIterator;
typedef CGAL::AABB_segment_primitive<K, Iterator> Primitive;
typedef CGAL::AABB_traits<K, Primitive> Traits;
typedef CGAL::AABB_tree<Traits> Tree;
typedef Tree::Primitive_id PrimitiveId;
typedef std::list<PrimitiveId> IdList;
typedef std::pair<ConstIterator,ConstIterator> IdPair;
typedef std::list<IdPair> PairList;
typedef PairList::iterator PairIterator;

bool connected(const Segment &a, const Segment &b, const double &tol= 1e-6)
  {
    bool retval= false;
    if(&a!=&b)
      {
	const Point &pa0= a.source();
	const Point &pa1= a.target();
	const Point &pb0= b.source();
	const Point &pb1= b.target();
	const double d1= CGAL::squared_distance(pa0,pb0);
	if(d1<tol)
	  { retval= true; }
	else
	  {
	    const double d2= CGAL::squared_distance(pa0,pb1);
	    if(d2<tol)
	      { retval= true; }
	    else
	      {
		const double d3= CGAL::squared_distance(pa1,pb0);
		if(d3<tol)
		  { retval= true; }
		else
		  {
		    const double d4= CGAL::squared_distance(pa1,pb1);
		    if(d4<tol)
		      { retval= true; }
		  }
	      }
	  }
      }
    return retval;
  }

PairList getIntersections(SegmentVector &segments)
  {
    // constructs the AABB tree and the internal search tree for 
    // efficient distance computations.
    Tree tree(segments.begin(),segments.end());
    tree.accelerate_distance_queries();

    PairList pairList;
    std::set<ConstIterator> visited;    

    for(ConstIterator i= segments.begin();i!= segments.end();i++)
      {
	const Segment &s= *i;
        IdList intersectedPrimitives;
	tree.all_intersected_primitives(s,std::back_inserter(intersectedPrimitives));
	visited.insert(i);
        for(IdList::iterator j= intersectedPrimitives.begin();j!= intersectedPrimitives.end();j++)
          {
	    const Iterator k= *j;
	    if(visited.find(k)!=visited.end())
	      {
	        const auto &is= *k;
	        const bool itself= (&is==&s);
	        const bool conn= connected(is,s);
	        if(!itself && !conn)
	          pairList.push_back(IdPair(i,k));
	      }
	  }
      }
    return pairList;
  }

int main(void)
  {
    Point a(0.0, 0.0, 0.0);
    Point b(1.0, 0.0, 0.0);
    Point c(1.0, 1.0, 0.0);
    Point d(0.0, 1.0, 0.0);
    Point e(0.0, 0.0, 1.0);
    Point f(1.0, 0.0, 1.0);
    Point g(1.0, 1.0, 1.0);
    Point h(0.0, 1.0, 1.0);
    
    SegmentVector segments;
    segments.push_back(Segment(a,b));
    segments.push_back(Segment(b,c));
    segments.push_back(Segment(c,d));
    segments.push_back(Segment(d,a));
    segments.push_back(Segment(e,f));
    segments.push_back(Segment(f,g));
    segments.push_back(Segment(g,h));
    segments.push_back(Segment(h,e));
    // Intersections to detect
    segments.push_back(Segment(a,g));
    segments.push_back(Segment(d,f));

    PairList pairList= getIntersections(segments);
    for(PairIterator i= pairList.begin(); i!= pairList.end();i++)
      {
	IdPair idPair= *i;
        std::cout << "intersection: " << *idPair.first << " x " << *idPair.second << std::endl;
      }
    // // counts #intersections with a plane query
    // Plane plane_query(a,b,d);
    // std::cout << tree.number_of_intersected_primitives(plane_query)
    //     << " intersections(s) with plane" << std::endl;
    // // counts #intersections with a triangle query
    // Triangle triangle_query(a,b,c);
    // std::cout << tree.number_of_intersected_primitives(triangle_query)
    //     << " intersections(s) with triangle" << std::endl;
    // // computes the closest point from a point query 
    // Point point_query(2.0, 2.0, 2.0);
    // Point closest = tree.closest_point(point_query);
    // std::cerr << "closest point is: " << closest << std::endl;
    return EXIT_SUCCESS;
}
