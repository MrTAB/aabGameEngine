/**
*
*	render_state.cpp
*
**/

#include"render_state.hpp"
#include"_include_opengl.hpp"
#include<cassert>
namespace aab	{
namespace visen	{


void RenderState::enableTexturing ()
{
	glEnable (GL_TEXTURE_2D);
}

void RenderState::disableTexturing ()
{
	glDisable (GL_TEXTURE_2D);
}

void RenderState::enableBlending ()
{
	glEnable (GL_BLEND);
}

void RenderState::disableBlending ()
{
	glDisable (GL_BLEND);
}

void RenderState::setBlendMethod(const BlendParameter source, const BlendParameter destination)
{
	glBlendFunc (source, destination);
}

void RenderState::setBlendMethod(const BlendParameter source, const BlendParameter destination, const float alpha)
{
    glBlendColor(0,0,0,alpha);
	glBlendFunc (source, destination);
}

void RenderState::setBlendMethod(const BlendParameter source, const BlendParameter destination, aab::visen::Colorub color)
{
    glBlendColor(color.getRedf(),color.getGreenf(),color.getBluef(),color.getAlphaf());
	glBlendFunc (source, destination);
}

void RenderState::applyBlendMethod(const BlendMethod blend)
{
    //assert(false);
	if (blend.isEnabled ())
	{
		enableBlending();
		if(blend.usesSeparateAlpha())
		{
            if(blend.hasColor())
            {
                setColourAlphaBlendMethods (blend.getSource(),
                                            blend.getDestination(),
                                            blend.getAlphaSource(),
                                            blend.getAlphaDestination(),
                                            blend.getColor());
            }
            else
            {
                setColourAlphaBlendMethods (blend.getSource(),
                                            blend.getDestination(),
                                            blend.getAlphaSource(),
                                            blend.getAlphaDestination());
            }

		}
		else
		{
            if(blend.hasColor())
            {
                setBlendMethod (blend.getSource(),blend.getDestination(), blend.getColor());
            }
            else
            {
                setBlendMethod (blend.getSource(),blend.getDestination());
            }
		}
	}
	else
	{
		disableBlending();
	}


}

void RenderState::enableLines()
{
	glPolygonMode(GL_FRONT,GL_LINE);
}

void RenderState::enableSolids()
{
	glPolygonMode(GL_FRONT,GL_FILL);
}



void RenderState::setColourAlphaBlendMethods(const BlendParameter source,
                                        const BlendParameter destination,
                                        const BlendParameter sourceA,
                                        const BlendParameter destinationA)
{
	glBlendFuncSeparate (source, destination, sourceA, destinationA);
}

void RenderState::setColourAlphaBlendMethods(const BlendParameter source,
                                        const BlendParameter destination,
                                        const BlendParameter sourceA,
                                        const BlendParameter destinationA,
                                        const float alpha)
{
    glBlendColor(0,0,0,alpha);
	glBlendFuncSeparate (source, destination, sourceA, destinationA);
}

void RenderState::setColourAlphaBlendMethods(const BlendParameter source,
                                        const BlendParameter destination,
                                        const BlendParameter sourceA,
                                        const BlendParameter destinationA,
                                        aab::visen::Colorub color)
{
    glBlendColor(color.getRedf(),color.getGreenf(),color.getBluef(),color.getAlphaf());
	glBlendFuncSeparate (source, destination, sourceA, destinationA);
}

void RenderState::setColorMask(const bool red, const bool green, const bool blue, const bool alpha)
{
    glColorMask(red,green,blue,alpha);
}

/*
void RenderState::setColourAlphaBlendMethods(BlendMethod color,BlendMethod alpha)
{
	if (color.isEnabled ())
		enableBlending();
	else
		disableBlending();

	glBlendFuncSeparate (color.getSource(),color.getDestination(), alpha.getSource(),alpha.getDestination());
}
*/



}		//	visen
}		//	aab
