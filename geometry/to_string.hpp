/**
*
*	to_string.hpp
*
*   Methods to convert various geometry types to string
**/

#if !defined(AAB_GEOMETRY_TO_STRING_METHODS)
#define AAB_GEOMETRY_TO_STRING_METHODS
#include"line_equation.hpp"
#include"line_segment.hpp"
#include"point.hpp"
#include"vector.hpp"
#include"panel.hpp"
#include<string>
#include<sstream>
namespace aab	{
namespace geometry{

std::string toString (const LineEquation le)
{
    std::ostringstream ostring;
    ostring	<< le.getXCoefficient() << "*x + " << le.getYCoefficient() << "*y + " << le.getCCoefficient();

    return ostring.str ();
}

std::string toString (const LineSegment ls)
{
    std::ostringstream ostring;
    ostring	<< "(" << ls.getFirstPoint() << ", " << ls.getSecondPoint() << ")";

    return ostring.str ();
}

std::string toString (const Panel p)
{
    std::ostringstream ostring;
    ostring	<< "("
            << "left: "		<< p.left		<< ", "
            << "bottom: "	<< bottom	<< ", "
            << "right: "	<< right	<< ", "
            << "top: "		<< top		<< ")";

    return ostring.str ();
}

std::string toString (const Point p)
{
    std::ostringstream ostring;
    ostring << "(" << trimIfNearZero (x) << "," << trimIfNearZero (y) << ")";

    return ostring.str ();
}
	
std::string toString (const Vector v)
{
    std::ostringstream ostring;
    ostring << "[" << floats::trimIfNearZero (x) << "," << floats::trimIfNearZero (y) << "]";

    return ostring.str ();
}
	

}	// geometry
}	// aab
#endif // AAB_GEOMETRY_TO_STRING_METHODS







