/**
*
*	context_definition.hpp
*
*   todo - add window title text to context definition?
**/

#if !defined(AAB_VISEN_CONTEXT_DEFINITION_CLASS)
#define AAB_VISEN_CONTEXT_DEFINITION_CLASS
#include<string>
namespace aab	{
namespace visen	{

enum ScreenMode
{
	windowed_mode,
	fullscreen_mode
};

enum ShadeMode
{
	flat_shade_mode,
	smooth_shade_mode
};

enum VsyncMode
{
    system_defined,
    enable_vsync,
    disable_vsync
};

class ContextDefinition
{
	public:

	ContextDefinition() :
		width (640),
		height (480),
		mode (windowed_mode),
		shadeMode(flat_shade_mode),
		nearClip (-1),
		farClip (1),
		useDepthTest(false),
		scaleX(1.0),
		scaleY(1.0),
		vsync(system_defined),
		windowTitle("Genji, SDL, OpenGL app")
	{
		// nothing to do here //
	}

	int width;
	int height;
	ScreenMode mode;
	ShadeMode shadeMode;

	int nearClip, farClip;
	bool useDepthTest;
	float scaleX, scaleY;
	VsyncMode vsync;
	std::string windowTitle;
};



}		//	visen
}		//	aab
#endif //AAB_VISEN_CONTEXT_DEFINITION_CLASS
