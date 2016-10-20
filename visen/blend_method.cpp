/**
*
*	blend_method.cpp
*
**/

#include"blend_method.hpp"
#include"_include_opengl.hpp"
namespace aab	{
namespace visen	{
    


namespace blend {
	const BlendParameter blend_zero = GL_ZERO;
	const BlendParameter blend_one = GL_ONE;
	const BlendParameter blend_src_color = GL_SRC_COLOR;
	const BlendParameter blend_one_minus_src_color = GL_ONE_MINUS_SRC_COLOR;
	const BlendParameter blend_dst_color = GL_DST_COLOR;
	const BlendParameter blend_one_minus_dst_color = GL_ONE_MINUS_DST_COLOR;
	const BlendParameter blend_src_alpha = GL_SRC_ALPHA;
	const BlendParameter blend_one_minus_src_alpha = GL_ONE_MINUS_SRC_ALPHA;
	const BlendParameter blend_dst_alpha = GL_DST_ALPHA;
	const BlendParameter blend_one_minus_dst_alpha = GL_ONE_MINUS_DST_ALPHA;
	const BlendParameter blend_constant_color = GL_CONSTANT_COLOR;
	const BlendParameter blend_one_minus_constant_color = GL_ONE_MINUS_CONSTANT_COLOR;
	const BlendParameter blend_constant_alpha = GL_CONSTANT_ALPHA;
	const BlendParameter blend_one_minus_constant_alpha = GL_ONE_MINUS_CONSTANT_ALPHA;
	const BlendParameter blend_src_alpha_saturate = GL_SRC_ALPHA_SATURATE;
	const BlendParameter blend_srcone_color = GL_SRC1_COLOR;
	const BlendParameter blend_one_minus_srcone_color = GL_ONE_MINUS_SRC1_COLOR;
	const BlendParameter blend_srcone_alpha = GL_SRC1_ALPHA;
	const BlendParameter blend_one_minus_srcone_alpha = GL_ONE_MINUS_SRC1_ALPHA;
} // namespace blend

BlendMethod::BlendMethod():source(blend::blend_one), destination(blend::blend_zero),enabled (true),colored(false), separate(false)
{
	// nothing to do here //
}

BlendMethod::BlendMethod (BlendParameter sourceIn, BlendParameter destinationIn):
	enabled (true), source(sourceIn), destination(destinationIn),colored(false), separate(false)
{
	// nothing to do here //
}


BlendMethod::BlendMethod (BlendParameter sourceIn, BlendParameter destinationIn, BlendParameter alphaSourceIn, BlendParameter alphaDestinationIn):
	enabled (true), source(sourceIn), destination(destinationIn),sourceA(alphaSourceIn), destinationA(alphaDestinationIn), colored(false), separate(true)
{
	// nothing to do here //
}

void BlendMethod::set (BlendParameter sourceIn, BlendParameter destinationIn)
{
	source = sourceIn; destination = destinationIn;
	separate = false;
}

void BlendMethod::set (BlendParameter sourceIn, BlendParameter destinationIn, BlendParameter alphaSourceIn, BlendParameter alphaDestinationIn)
{
	source = sourceIn;
	destination = destinationIn;
	sourceA = alphaSourceIn;
	destinationA = alphaDestinationIn;
	separate = true;
}

void BlendMethod::makeTransparent()
{
    enable();
	source = blend::blend_src_alpha;
	destination = blend::blend_one_minus_src_alpha;
	separate = false;
}

void BlendMethod::makeDefault()
{
	source = blend::blend_one;
	destination = blend::blend_zero;
	separate = false;
}

/*
void BlendMethod::makeSilhouette() - todo - add to header and cascade build.
{
    enable();
	source = blend::blend_zero;
	destination = blend::blend_one_minus_src_alpha;
	separate = false;
}*/

void BlendMethod::makeAdditive()
{
    enable();
	source = blend::blend_src_alpha;
	destination = blend::blend_one;
	separate = false;
}


void BlendMethod::enable ()
{
	enabled = true;
}

void BlendMethod::disable ()
{
	enabled = false;
}




}		//	visen
}		//	aab
