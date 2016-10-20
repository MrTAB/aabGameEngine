
/**
*
*
*
**/

#include"screen.hpp"
#include"error_trap.hpp"
#include<sdl.H>
#include"_include_opengl.hpp"
#include"PNG_savesurf/pngfuncs.h"
#include"../test/exceptions.hpp"
#include"../test/debug_assertions.hpp"
#include<cmath>
#include<sstream>
namespace aab	{
namespace visen	{



struct ScreenClass::Data
{
	SDL_Surface *surface;
	float scaleX, scaleY;
	GLbitfield clearFields;
	float nearClip, farClip;
};

bool ScreenClass::exists (false);


Screen startScreen (int width, int height, ScreenMode mode)// aab::test::already_instantiated_error, std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{
	if (ScreenClass::exists)
	{
		throw aab::test::already_instantiated_error("Screen startScreen(int,int,ScreenMode) cannot be called if a screen currently exists.");
	}

	ContextDefinition contextDefinition;
	contextDefinition.width = width;
	contextDefinition.height = height;
	contextDefinition.mode = mode;
	contextDefinition.scaleX = 1.0;
	contextDefinition.scaleY = 1.0;

	Screen screen (new ScreenClass (contextDefinition), ScreenClass::Deleter ());
	ScreenClass::exists = true;

	return screen;
}

Screen startScreen (const ContextDefinition& contextDefinition)// aab::test::already_instantiated_error, std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{
	if (ScreenClass::exists)
	{
		throw aab::test::already_instantiated_error("Screen startScreen(const ContextDefinition&) cannot be called if a screen currently exists.");
	}
	
	Screen screen (new ScreenClass (contextDefinition), ScreenClass::Deleter ());
	ScreenClass::exists = true;

	return screen;
}




ScreenClass::ScreenClass (const ContextDefinition& def):// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
	data (new Data ())
{

	Uint32 initFlags = SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK;
	Uint32 videoFlags;
	Uint32 bpp;
	const SDL_VideoInfo * videoInfo;

	if (def.width < 1 || def.height < 1)
	{
		throw std::invalid_argument ("ScreenClass::ScreenClass::\tdesired dimensions too small.");
	}

	if (def.nearClip > def.farClip)
	{
		throw std::invalid_argument ("ScreenClass::ScreenClass::\tContextDefinition nearClip must not be greater than farClip.");
	}

	switch (def.mode)
	{
		case windowed_mode:
		{
			videoFlags = SDL_OPENGL;//|SDL_RESIZABLE;
		}
		break;

		case fullscreen_mode:
		{
			videoFlags = SDL_OPENGL|SDL_FULLSCREEN;
		}
		break;

		default:
		{
			throw std::invalid_argument ("ScreenClass::ScreenClass::\tinvalid screen Mode");
		}

		break;
	}


	if (SDL_Init (initFlags) != 0)
	{
	    std::stringstream error;
	    error << "ScreenClass::ScreenClass::\tSDL_Init failed:\t" << SDL_GetError ();
		throw std::runtime_error (error.str());
	}

	if (::SDL_WasInit (SDL_INIT_EVERYTHING) != initFlags)
	{
		throw std::runtime_error ("ScreenClass::ScreenClass::\tSDL_WasInit failed.");
	}

    setCaption(def.windowTitle);
    
	videoInfo = SDL_GetVideoInfo ();

	if (! videoInfo)
	{
		SDL_Quit();

		throw std::runtime_error ("ScreenClass::ScreenClass::\tSDL_GetVideoInfo failed.");
	}


	bpp = videoInfo -> vfmt -> BitsPerPixel;


	/* todo: revise these for performance */

	SDL_GL_SetAttribute (SDL_GL_RED_SIZE,		8);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE,		8);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE,		8);
	SDL_GL_SetAttribute (SDL_GL_ALPHA_SIZE,		8);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER,	true);
	switch(def.vsync)
	{
        case enable_vsync:
        {
            SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1); // v-sync?. Note - is depricated from SDL 1.3 (using 1.24)
            break;
        }        
        case disable_vsync:
        {
            SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0); // v-sync?. Note - is depricated from SDL 1.3 (using 1.24)
            break;
        }        
        case system_defined:
        default:
        {
            break;
        } 
	}
	if (def.useDepthTest)
	{
	    SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE,		16);
	}
    
	data-> surface = SDL_SetVideoMode (def.width, def.height, bpp, videoFlags);

	if (data-> surface == NULL)
	{
		SDL_Quit();

		throw std::runtime_error ("ScreenClass::ScreenClass::\tSDL_SetVideoMode failed.");
	}

    
	hideCursor ();

	ErrorTrap trap ("ScreenClass::ScreenClass::");
	
	data->scaleX = def.scaleX;
	data->scaleY = def.scaleY;
	data->nearClip = def.nearClip;
	data->farClip = def.farClip;
    resetProjection();
    


	glEnable (GL_CULL_FACE);

	if (def.useDepthTest)
	{
		glEnable (GL_DEPTH_TEST);
		data->clearFields = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT;
	}
	else
	{
		glDisable (GL_DEPTH_TEST);
		data->clearFields = GL_COLOR_BUFFER_BIT;
	}

	glShadeModel (def.shadeMode == smooth_shade_mode? GL_SMOOTH : GL_FLAT);
	glDisable (GL_DITHER);

	// standard output for ops:

	glEnable (GL_TEXTURE_2D);
	//glEnable (GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glMatrixMode (GL_TEXTURE);
	glLoadIdentity ();
	
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        throw std::runtime_error("ScreenClass::ScreenClass::\tGlew failed to initialize.");
    }
    if (GLEW_VERSION_1_3)
    {
        //OpenGL 1.3 is supported!
    }
    
    //glewGetString(GLEW_VERSION);
    
    
    //todo - keep updated with any any extension groups which are being used:

	if(! GLEW_ARB_vertex_buffer_object) // glGenBuffers// glBindBuffer// glBufferData // glDeleteBuffers // glBufferSubData
	{
        throw std::runtime_error("ScreenClass::ScreenClass::\tProgram requiries GLEW_ARB_vertex_buffer_object to run. This has not been found on your system. Updating graphics drivers may resolve this error.");
	}
	
	//if(! GLEW_ARB_draw_elements_base_vertex) // glDrawElementsBaseVertex
	//{
    //    throw std::runtime_error("ScreenClass::ScreenClass::\tProgram requiries GLEW_ARB_draw_elements_base_vertex to run. This has not been found on your system. Updating graphics drivers may resolve this error.");
	//}
	
	
	if(! GL_EXT_draw_range_elements) // glDrawRangeElementsEXT
	{
        throw std::runtime_error("ScreenClass::ScreenClass::\tProgram requiries GL_EXT_draw_range_elements to run. This has not been found on your system. Updating graphics drivers may resolve this error.");
	}
	
	trap.tryRaise ();

}


ScreenClass::~ScreenClass() //throw ()
{
	ScreenClass::exists = false;
	SDL_Quit();
}

void ScreenClass::resetProjection()
{
	ErrorTrap trap ("ScreenClass::ScreenClass::");

	glViewport( 0, 0, data->surface->w, data->surface->h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, data->surface->w*data->scaleX, data->surface->h*data->scaleY, 0, data->nearClip, data->farClip);
	//glOrtho (0, def.width, def.height, 0, def.nearClip, def.farClip);
	//glOrtho (0, 2*def.width, 2*def.height, 0, def.nearClip, def.farClip);
	
	trap.tryRaise ();
}


int ScreenClass::getContextWidth () const
{
	return data-> surface-> w;
}

int ScreenClass::getContextHeight () const
{
	return data-> surface-> h;
}

void ScreenClass::update ()
{
	//glFlush (); - not required!
	SDL_GL_SwapBuffers ();
}

void ScreenClass::clear ()
{
	glClear (data->clearFields);
}

void ScreenClass::setClearColor (byte_t red, byte_t green, byte_t blue)
{
	glClearColor ( float (red / 255.0), float (green / 255.0), float (blue / 255.0), 0.0f);
}

void ScreenClass::setClearColor (Colorf color)
{
	setClearColor (color.getRed (), color.getGreen (), color.getBlue ());
}

void ScreenClass::setCaption (const std::string windowName)
{
	SDL_WM_SetCaption (windowName.c_str (), windowName.c_str ());
}

void ScreenClass::showCursor ()
{
	SDL_ShowCursor (SDL_ENABLE);
}


void ScreenClass::hideCursor ()
{
	SDL_ShowCursor (SDL_DISABLE);
}

void ScreenClass::minimise ()
{
	SDL_WM_IconifyWindow ();
}

float ScreenClass::getScaleX () const
{
	return data->scaleX;
}

float ScreenClass::getScaleY () const
{
	return data->scaleY;
}

bool ScreenClass::hasDoubleBuffering()const
{
    int value;
    SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &value);
    
    return value;
}



}	//	visen
}	//	aab


