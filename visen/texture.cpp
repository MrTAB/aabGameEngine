
/**
*
*	texture.cpp
*
*	methods assume that GL_TEXTURE_2D is enabled; any class which changes this
*	state should thus restore it before continuing.
*
*	should be changed to analyse wether blending is needed and allow a change
*
*	change GL_RGBA to GL_RGBA8 ?
*
*	writing to a textures pixeldata: can update a portion of the texels, wthout changing size etc
*		glBindTexture(GL_TEXTURE_2D, textureID);;
*		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
*	you can use glCopyTexSubImage2D to copy texels from the framebuffer!
*
*
**/

#include"texture.hpp"
#include"render_state.hpp"
#include"error_trap.hpp"
#include"../maths/power_of_2.hpp"
#include"../types/mutable_closer.hpp"
#include<sdl.H>
#include"_include_opengl.hpp"
#include<exception>
#include<stdexcept>
#include<vector>
#include<cassert>
namespace aab	{
namespace visen	{
using aab::maths::isPowerOf2;
using aab::maths::nextPowerOf2;
//using aab::time::FrameTicker;
using aab::types::MutableCloser;
typedef TextureClass TC;

class TextureClose
{
	private:

		GLuint &id;

	public:

	explicit TextureClose (GLuint &id) : id (id)
	{
	}

	void operator ()()
	{
		glDeleteTextures (1, &id);
	}
};

typedef MutableCloser <TextureClose> TextureCloser;




struct TextureClass::Data
{
	/*	OpenGL ID of the image.
	*/
	GLuint textureId;

	/* Width and height of the original image
	*/
	int imageWidth;
	int imageHeight;

	/* Width and height of the created texture: This may be larger than the original image.
	*/
	int textureWidth;
	int textureHeight;

};


TexturePtr makeTexture (Screen screen, Image image)
//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{
	TexturePtr ptr (new TextureClass (screen, image), TextureClass::Deleter ());
	return ptr;
}

TexturePtr makeTexture (Screen screen, const std::string &filename)
//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
{
	TexturePtr ptr (new TextureClass (screen, filename), TextureClass::Deleter ());
	return ptr;
}

TexturePtr makeTexture (Screen screen, const std::string &filename,
			TextureClass::byte_t red, TextureClass::byte_t green, TextureClass::byte_t blue)
//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
{
	TexturePtr ptr (new TextureClass (screen, filename, red, green, blue), TextureClass::Deleter ());
	return ptr;
}

TexturePtr makeTexture (Screen screen, const std::string &filename, const Colorf mask)
//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
{
	return makeTexture (screen, filename, mask.getRed (), mask.getGreen (), mask.getBlue ());
}

TexturePtr makeTexture (Screen screen, const std::string &filename, const std::string &maskFilename)
//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
{
	TexturePtr ptr (new TextureClass (screen, filename, maskFilename), TextureClass::Deleter ());
	return ptr;
}

TexturePtr makeTexture (Screen screen,  unsigned int width, unsigned int height, bool useAlpha)
//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
{
	TexturePtr ptr (new TextureClass (screen, width, height, useAlpha), TextureClass::Deleter ());
	return ptr;
}

TexturePtr makeTexture (Screen screen,  unsigned int width, unsigned int height, bool useAlpha, aab::visen::Colorub color)
//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
{
	TexturePtr ptr (new TextureClass (screen, width, height, useAlpha, color), TextureClass::Deleter ());
	return ptr;
}
/*
TexturePtr makeNullTexture ()
//	throw (std::exception &)
{
	TexturePtr ptr (0);
	return ptr;
}*/

TC::TextureClass (Screen screen, Image image)
://std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
	data (new Data ())
{
	fillData (image);
	correctImageSize (image);
	createTexture (image);
	accessBlendMethod().disable();
}


TC::TextureClass (Screen screen, const std::string &filename)
://std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
	data (new Data ())
{
	Image image = makeImage (screen, filename);

	fillData (image);
	correctImageSize (image);
	createTexture (image);
	accessBlendMethod().disable();
}

TC::TextureClass (Screen screen, const std::string &filename, byte_t red, byte_t green, byte_t blue)
://std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
	data (new Data ())
{
	Image image = makeImage (screen, filename, red, green, blue);

	fillData (image);
	correctImageSize (image);
	createTexture (image);
	accessBlendMethod().makeTransparent();

}


TC::TextureClass (Screen screen, const std::string &filename, const std::string &maskFilename)
://std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
	data (new Data ())
{
	Image image = makeImage (screen, filename, maskFilename);

	fillData (image);
	correctImageSize (image);
	createTexture (image);
	accessBlendMethod().makeTransparent();
}

TC::TextureClass (Screen, unsigned int width, unsigned int height, bool useAlpha)
://std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
	data (new Data ())
{
	createTexture (width,height,useAlpha);
}

TC::TextureClass (Screen, unsigned int width, unsigned int height, bool useAlpha, aab::visen::Colorub color)
://std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
	data (new Data ())
{
	createTexture (width,height,useAlpha,color);
}

unsigned int TC::getId()const
{
    return data->textureId;
}


void TC::fillData (Image image)
{
	data-> imageWidth = image-> getWidth ();
	data-> imageHeight = image-> getHeight ();
	data-> textureWidth = data-> imageWidth;
	data-> textureHeight = data-> imageHeight;
}

int TC::getClearBorderX()const
{
    return (data->textureWidth - data->imageWidth)/2.f;
}

int TC::getClearBorderY()const
{
    return (data->textureHeight - data->imageHeight)/2.f;
}

bool TC::correctedStoredSizes()
{
	bool changedDimension = false;

	if (! isPowerOf2 (data-> imageWidth))
	{
		data-> textureWidth = nextPowerOf2 (data-> imageWidth);
		changedDimension = true;
	}

	if (! isPowerOf2 (data-> imageHeight))
	{
		data-> textureHeight = nextPowerOf2 (data-> imageHeight);
		changedDimension = true;
	}

	if (data-> textureWidth < 64)
	{
		data-> textureWidth = 64;
		changedDimension = true;
	}

	if (data-> textureHeight < 64)
	{
		data-> textureHeight = 64;
		changedDimension = true;
	}
	
	return changedDimension;
}

void TC::correctImageSize (Image image) // std::runtime_error, std::invalid_argument
{
	if (correctedStoredSizes())
	{
		image-> expandClearEdgesTo (data-> textureWidth, data-> textureHeight);
	}
}

void TC::createTexture (Image image) //std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{

	/*
	*	this method assumes the following:
	*	glEnable (GL_TEXTURE_2D);
	*/

	ErrorTrap trap ("TextureClass::createTexture::");


	glGenTextures (1, &(data-> textureId));

	// these two lines ensure that any escape before a call to keep() will call glDeleteTextures
	TextureClose textureClose (data-> textureId);
	TextureCloser textureCloser (textureClose);


	glBindTexture (GL_TEXTURE_2D, data-> textureId);

	if (image-> getBitsPerPixel() == 32)
	{
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, data-> textureWidth, data-> textureHeight, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, image-> accessPixels ());
	}
	else if (image-> getBitsPerPixel() == 24)
	{
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, data-> textureWidth, data-> textureHeight, 0,
			GL_RGB, GL_UNSIGNED_BYTE, image-> accessPixels ());
	}
	else
	{
		// something has went wrong here:

		throw std::invalid_argument ("TextureClass::createTexture::\tInvalid Image format");
	}

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	trap.tryRaise ();

	// no exceptions: keep texture.
	textureCloser.keep ();
}

void TC::createTexture (unsigned int width, unsigned int height, bool useAlpha) //std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{

	/*
	*	this method assumes the following:
	*	glEnable (GL_TEXTURE_2D);
	*/

	ErrorTrap trap ("TextureClass::createTexture::");
	
	data-> imageWidth = width;
	data-> imageHeight = height;
	data-> textureWidth = width;
	data-> textureHeight = height;
    correctedStoredSizes();
    
	glGenTextures (1, &(data-> textureId));

	// these two lines ensure that any escape before a call to keep() will call glDeleteTextures
	TextureClose textureClose (data-> textureId);
	TextureCloser textureCloser (textureClose);


	glBindTexture (GL_TEXTURE_2D, data-> textureId);

	if (useAlpha)
	{
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, data-> textureWidth, data-> textureHeight, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}
	else
	{
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, data-> textureWidth, data-> textureHeight, 0,
			GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	trap.tryRaise ();

	// no exceptions: keep texture.
	textureCloser.keep ();
	
	if(useAlpha)
	{
	    accessBlendMethod().makeTransparent();
	}
	else
	{
	    accessBlendMethod().disable();
	}
}

struct RGB
{
    uint8_t r, g, b;
};

void TC::createTexture (unsigned int width, unsigned int height, bool useAlpha, aab::visen::Colorub color) //std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{
    // TODO - TEST
    
	/*
	*	this method assumes the following:
	*	glEnable (GL_TEXTURE_2D);
	*/

	ErrorTrap trap ("TextureClass::createTexture::");

	data-> imageWidth = width;
	data-> imageHeight = height;
	data-> textureWidth = width;
	data-> textureHeight = height;
    correctedStoredSizes();
    
	glGenTextures (1, &(data-> textureId));

	// these two lines ensure that any escape before a call to keep() will call glDeleteTextures
	TextureClose textureClose (data-> textureId);
	TextureCloser textureCloser (textureClose);


	glBindTexture (GL_TEXTURE_2D, data-> textureId);
	

	if (useAlpha)
	{
	    std::vector<Colorub> pixels;
	    pixels.assign(data-> textureWidth*data-> textureHeight, color);
	    
	    const int wdiff = data->textureWidth - data->imageWidth;
	    const int hdiff = data->textureHeight - data->imageHeight;
	    if(wdiff)
	    {	        
	        for(int y = 0; y < data->textureHeight; ++y)
	        {
	            for(int x = 0; x < wdiff/2; ++x)
	            {
	                pixels[x + y*data->textureWidth].setAlpha(0);
	            }
	            for(int x = data->textureWidth-wdiff/2; x < data->textureWidth; ++x)
	            {
	                pixels[x + y*data->textureWidth].setAlpha(0);
	            }
	        }
	    }
	    if(hdiff)
	    {
	        if(wdiff)
	        {
                for(int x = wdiff/2; x < data->textureWidth-wdiff/2; ++x)
                {
                    for(int y = 0; y < hdiff/2; ++y)
                    {
                        pixels[x + y*data->textureWidth].setAlpha(0);
                    }
                    for(int y = data->textureHeight-hdiff/2; y < data->textureHeight; ++y)
                    {
                        pixels[x + y*data->textureWidth].setAlpha(0);
                    }
                }
	        }
	        else
	        {
                for(int x = 0; x < data->textureWidth; ++x)
                {
                    for(int y = 0; y < hdiff/2; ++y)
                    {
                        pixels[x + y*data->textureWidth].setAlpha(0);
                    }
                    for(int y = data->textureHeight-hdiff/2; y < data->textureHeight; ++y)
                    {
                        pixels[x + y*data->textureWidth].setAlpha(0);
                    }
                }

	        }
	    }
	    
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, data-> textureWidth, data-> textureHeight, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	}
	else
	{
	    RGB rgb = {color.getRed(), color.getGreen(), color.getBlue() };
	    std::vector<RGB> pixels;
	    pixels.assign(data-> textureWidth*data-> textureHeight, rgb);
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, data-> textureWidth, data-> textureHeight, 0,
			GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
	}

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	trap.tryRaise ();

	// no exceptions: keep texture.
	textureCloser.keep ();
	
	if(useAlpha)
	{
	    accessBlendMethod().makeTransparent();
	}
	else
	{
	    accessBlendMethod().disable();
	}
}


TC::~TextureClass () //throw ()
{
	glDeleteTextures (1, &(data-> textureId));
}


void TC::bind () //throw ()
{
	glBindTexture (GL_TEXTURE_2D, data-> textureId);
	RenderState::applyBlendMethod (blendMethod);
}


int TC::getImageWidth () const
{
	return data-> imageWidth;
}

int TC::getImageHeight () const
{
	return data-> imageHeight;
}


int TC::getOutputWidth () const
{
	return data-> textureWidth;
}

int TC::getOutputHeight () const
{
	return data-> textureHeight;
}

/*
bool TC::hasFrameTickerPtr () const
{
	return false;
}

FrameTicker::Ptr TC::getFrameTickerPtr ()//throw (std::exception &)
{
	throw std::exception ();
}
*/

void TC::render ()
{
	//
	//	this method assumes the following:
	//	glEnable (GL_TEXTURE_2D);
	//
	this-> bind ();
	this-> renderNobind ();
}

void TC::renderNobind ()
{
	//
	//	this method assumes the following:
	//	glEnable (GL_TEXTURE_2D);
	//

	const float hw = data-> textureWidth / 2;
	const float hh = data-> textureHeight / 2;
	float phw = hw;
	float phh = hh;

    /*if (static_cast<int>(data->textureWidth)%2)
    {
        phw = phw + 1.0f;
    }
    if (static_cast<int>(data->textureHeight)%2)
    {
        phh = phh + 1.0f;
    }*/

	glBegin (GL_QUADS);
	{
		//glTexCoord2f (0, 0);
		glTexCoord2f(texCoord[0].x,texCoord[0].y);
		
		glVertex2f (-hw, -hh);

		//glTexCoord2f (0, 1);
		glTexCoord2f(texCoord[1].x,texCoord[1].y);
		glVertex2f (-hw, phh);

		//glTexCoord2f (1, 1);
		glTexCoord2f(texCoord[2].x,texCoord[2].y);
		glVertex2f (phw, phh);

		//glTexCoord2f (1, 0);
		glTexCoord2f(texCoord[3].x,texCoord[3].y);
		glVertex2f (phw, -hh);

	}
	glEnd ();
}

namespace texture
{
    unsigned int getMaxTextureUnits()
    {
        return GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
    }

    void setActiveTextureUnit(unsigned int unit)
    {
        assert((unit)<=GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
        glActiveTexture(GL_TEXTURE0+unit);
    }

    void establishTextureUnit(unsigned int unit)
    {
        assert((unit)<=GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
        glActiveTexture(GL_TEXTURE0+unit);
        glEnable(GL_TEXTURE_2D);
    }
}


}	//	visen
}	//	aab


