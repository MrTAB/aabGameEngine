/**
*
*	blend_method.hpp
*
*   Defines and stores the method used to blend pixels during default fragment 
*   processing. Used by textures.
*
**/

#if !defined(AAB_VISEN_BLEND_METHOD_CLASS)
#define AAB_VISEN_BLEND_METHOD_CLASS
#include"../types/push_pop.hpp"
#include"color.hpp"
namespace aab	{
namespace visen	{


typedef int BlendParameter;

namespace blend { // allows a using declaration to locally import these constants
	extern const BlendParameter blend_zero;
	extern const BlendParameter blend_one;
	extern const BlendParameter blend_src_color;
	extern const BlendParameter blend_one_minus_src_color;
	extern const BlendParameter blend_dst_color;
	extern const BlendParameter blend_one_minus_dst_color;
	extern const BlendParameter blend_src_alpha;
	extern const BlendParameter blend_one_minus_src_alpha;
	extern const BlendParameter blend_dst_alpha;
	extern const BlendParameter blend_one_minus_dst_alpha;
	extern const BlendParameter blend_constant_color;
	extern const BlendParameter blend_one_minus_constant_color;
	extern const BlendParameter blend_constant_alpha;
	extern const BlendParameter blend_one_minus_constant_alpha;
	extern const BlendParameter blend_src_alpha_saturate;
	extern const BlendParameter blend_srcone_color;
	extern const BlendParameter blend_one_minus_srcone_color;
	extern const BlendParameter blend_srcone_alpha;
	extern const BlendParameter blend_one_minus_srcone_alpha;
} //namespace blend

class BlendMethod
{
	private:

		BlendParameter source, destination, sourceA,destinationA;
		bool enabled;
		bool colored;
		Colorub color;
		bool separate;

	public:

	BlendMethod();
	BlendMethod (BlendParameter source, BlendParameter destination);
	BlendMethod (BlendParameter source,
              BlendParameter destination,
              BlendParameter alphaSource,
              BlendParameter alphaDestination);

	BlendParameter getSource() const { return source; }
	BlendParameter getDestination() const { return destination; }
	BlendParameter getAlphaSource() const { return sourceA; }
	BlendParameter getAlphaDestination() const { return destinationA; }
	void set(BlendParameter source, BlendParameter destination);
	void set(BlendParameter source,
          BlendParameter destination,
          BlendParameter alphaSource,
          BlendParameter alphaDestination);
	void makeTransparent();
	void makeDefault();
	void makeAdditive();

	void enable ();
	void disable ();

	bool isEnabled()const
	{
	    return enabled;
	}
	
	void setColor(Colorub color_in) { color = color_in; colored = true; };
	void removeColor() { colored = false; }
	Colorub getColor()const { return color; }
	bool hasColor()const { return colored; }
	bool usesSeparateAlpha()const{ return separate; }

};




}		//	visen
}		//	aab
#endif //AAB_VISEN_BLEND_METHOD_CLASS
