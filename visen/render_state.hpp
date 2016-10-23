/**
*
*	render_state.hpp
*
*   Allows explicit changing of certain program wide graphical state values
*
*	note that textures, and thus sprites require texturing to be enabled before their use.
*	Screen automatically enables texturing
*	Blending is handled on a per-texture basis.
*	add wireframe glPolygonMode
**/

#if !defined(AAB_VISEN_RENDER_STATE_CLASS)
#define AAB_VISEN_RENDER_STATE_CLASS
#include"blend_method.hpp"
#include"color.hpp"
namespace aab	{
namespace visen	{

class RenderState
{
	public:

	static void enableTexturing ();
	static void disableTexturing ();
	static void enableBlending ();
	static void disableBlending ();
	static void setBlendMethod(const BlendParameter source, const BlendParameter destination);
    static void setBlendMethod(const BlendParameter source, const BlendParameter destination, aab::visen::Colorub color);
    static void setBlendMethod(const BlendParameter source, const BlendParameter destination, const float alpha);
	static void applyBlendMethod(const BlendMethod);
	static void setColourAlphaBlendMethods(const BlendParameter source,
                                        const BlendParameter destination,
                                        const BlendParameter sourceA,
                                        const BlendParameter destinationA);
	static void setColourAlphaBlendMethods(const BlendParameter source,
                                        const BlendParameter destination,
                                        const BlendParameter sourceA,
                                        const BlendParameter destinationA,
                                        aab::visen::Colorub color);
	static void setColourAlphaBlendMethods(const BlendParameter source,
                                        const BlendParameter destination,
                                        const BlendParameter sourceA,
                                        const BlendParameter destinationA,
                                        const float alpha);
                                        
    static void setColorMask(const bool red, const bool green, const bool blue, const bool alpha = true);
    
	static void enableLines();static void enableSolids();
};





}		//	visen
}		//	aab
#endif //AAB_VISEN_RENDER_STATE_CLASS
