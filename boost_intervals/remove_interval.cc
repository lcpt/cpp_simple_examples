// interval_map_mwe.cpp
#include <map>
#include <set>
#include <climits>

#include <boost/icl/interval.hpp>
#include <boost/icl/interval_map.hpp>

// Set of IDs that cover a time interval
typedef std::set<unsigned int> IDSet_t;
// interval tree from intervals of timestamps to a set of ids
typedef boost::icl::interval_map<time_t, IDSet_t> IMap_t;
// a time interval
typedef boost::icl::interval<time_t> Interval_t;

#include <iostream>
// from https://stackoverflow.com/a/22027957
inline std::ostream& operator<< (std::ostream& S, const IDSet_t& X)
{
    S << '(';
    for (IDSet_t::const_iterator it = X.begin(); it != X.end(); ++it) {
        if (it != X.begin()) {
            S << ',';
        }
        S << *it;
    }
    S << ')';
    return S;
}

int main(int argc, const char *argv[])
{
    (void)argc; // suppress warning
    (void)argv; // suppress warning

    IMap_t m;

    IDSet_t s;
    s.insert(1);
    s.insert(2);
    m += std::make_pair(Interval_t::right_open(100, 200), s);

    s = IDSet_t();
    s.insert(3);
    s.insert(4);
    m += std::make_pair(Interval_t::right_open(200, 300), s);

    s = IDSet_t();
    s.insert(5);
    s.insert(6);
    m += std::make_pair(Interval_t::right_open(150, 250), s);

    std::cout << "Initial map: " << std::endl;
    std::cout << m << std::endl;

    // find operation
    IMap_t::const_iterator it = m.find(175);

    std::cout << "Interval that covers 175: ";
    std::cout << it->first << std::endl;
    std::cout << "Ids in interval: " << it->second << std::endl;

    // partially remove 5 from interval (160,180)
    s = IDSet_t();
    s.insert(5);
    m -= std::make_pair(Interval_t::right_open(160, 180), s);

    std::cout << "map with 5 partially removed:" << std::endl;
    std::cout << m << std::endl;

    // completelly remove 6
    s = IDSet_t();
    s.insert(6);
    // Note: maybe the range of the interval could be shorter if you can somehow obtain the minimum and maximum times
    m -= std::make_pair(Interval_t::right_open(0, UINT_MAX), s);

    std::cout << "map without 6: " << std::endl;
    std::cout << m << std::endl;

    // remove a time interval
    m -= Interval_t::right_open(160, 170);

    std::cout << "map with time span removed: " << std::endl;
    std::cout << m << std::endl;

    return 0;
}
