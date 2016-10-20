
/**
*
*	display_absorber.cpp
*
**/

#include"display_absorber.hpp"
namespace aab	{
namespace visen	{

DisplayAbsorber::DisplayAbsorber (DisplayList list, bool allow):// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
	list (list),
	stopped (false)
{
	list-> open (allow);
}

DisplayAbsorber::~DisplayAbsorber () //throw ()
{
	stop ();
}

void DisplayAbsorber::stop ()
{
	if (! stopped)
	{
		list-> close ();
		stopped = true;
	}
}

}	//	visen
}	//	aab


