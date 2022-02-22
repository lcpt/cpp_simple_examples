// The next line includes <boost/date_time/posix_time/posix_time.hpp>
// and a few lines of adapter code.
#include <boost/icl/ptime.hpp>
#include <iostream>
#include <boost/icl/interval_map.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::icl;

// Type set<string> collects the names of party guests. Since std::set is
// a model of the itl's set concept, the concept provides an operator += 
// that performs a set union on overlap of intervals.
typedef std::set<string> GuestSetT;

void boost_party()
{
    GuestSetT mary_harry;
    mary_harry.insert("Mary");
    mary_harry.insert("Harry");

    GuestSetT diana_susan;
    diana_susan.insert("Diana");
    diana_susan.insert("Susan");

    GuestSetT peter;
    peter.insert("Peter");

    // A party is an interval map that maps time intervals to sets of guests
    interval_map<ptime, GuestSetT> party;

    party.add( // add and element
      make_pair(
        interval<ptime>::right_open(
          time_from_string("2008-05-20 19:30"),
          time_from_string("2008-05-20 23:00")),
        mary_harry));

    party += // element addition can also be done via operator +=
      make_pair(
        interval<ptime>::right_open(
          time_from_string("2008-05-20 20:10"),
          time_from_string("2008-05-21 00:00")),
        diana_susan);

    party +=
      make_pair(
        interval<ptime>::right_open(
          time_from_string("2008-05-20 22:15"),
          time_from_string("2008-05-21 00:30")),
        peter);


    interval_map<ptime, GuestSetT>::iterator it = party.begin();
    cout << "----- History of party guests -------------------------\n";
    while(it != party.end())
    {
        interval<ptime>::type when = it->first;
        // Who is at the party within the time interval 'when' ?
        GuestSetT who = (*it++).second;
        cout << when << ": " << who << endl;
    }

}


int main()
{
    cout << ">>Interval Container Library: Sample boost_party.cpp <<\n";
    cout << "-------------------------------------------------------\n";
    boost_party();
    return 0;
}
