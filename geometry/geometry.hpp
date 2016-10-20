/**
*
*	geometry.hpp
*
*	Include this to include all headers under the geometry namespace.
*	No need to link to the static library libgeometry.a to define the classes as they are all inline (at this time)
*
*   Does not include the to_string.hpp which provides methods for string conversion.
*   Include separately if desired.
*
**/

#if !defined(AAB_GEOMETRY)
#define AAB_GEOMETRY
#include"floats.hpp"
#include"line_equation.hpp"
#include"line_segment.hpp"
#include"panel.hpp"
#include"point.hpp"
#include"vector.hpp"
namespace aab	{
namespace geometry{

	// nothing //

}	// geometry
}	// aab
#endif // AAB_GEOMETRY

