
/**
*
*
*
**/

#include"image.hpp"
#include"../maths/power_of_2.hpp"
#include"PNG_savesurf/pngfuncs.h"
#include<sdl.H>
#include<sdl_image.H>
#include"../test/exceptions.hpp"
#include<boost/filesystem.hpp>
#include<sstream>
namespace aab	{
namespace visen	{
using aab::maths::isPowerOf2;


struct ImageClass::Data
{
	SDL_Surface *surface;
};


Image makeImage (const Screen screen, const std::string &filename)//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
{
	Image ptr (new ImageClass (screen, filename), ImageClass::Deleter ());
	return ptr;
}

Image makeImage (const Screen screen, const std::string &filename, ImageClass::byte_t red,
							ImageClass::byte_t green, ImageClass::byte_t blue)//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
{
	Image ptr (new ImageClass (screen, filename, red, green, blue), ImageClass::Deleter ());
	return ptr;
}

Image makeImage (const Screen screen, const std::string &filename,
		const Colorf maskColor) //	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
{
	return makeImage (screen, filename, maskColor.getRed (),
				maskColor.getGreen (), maskColor.getBlue ());
}

Image makeImage (const Screen screen, const std::string &filename,
							const std::string &maskFilename)//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
{
	Image ptr (new ImageClass (screen, filename, maskFilename), ImageClass::Deleter ());
	return ptr;
}

Image makeImage (const Screen screen, const int width, const int height, const bool useAlpha)//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
{
	Image ptr (new ImageClass (screen, width,height,useAlpha), ImageClass::Deleter ());
	return ptr;
}


ImageClass::ImageClass (const Screen, const int width, const int height, const bool alpha):
    data (new Data ())
{
    assert(width > 0 && height > 0);
    
    int depth = alpha?32:24;
    Uint32 rmask, gmask, bmask, amask;
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = alpha?0xff000000:0;
		
    data->surface = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, depth, rmask, gmask, bmask, amask);//|SDL_SRCALPHA done automatically if amask is nonzero
    
	if (! data-> surface)
	{
	    std::stringstream error;
        error << "ImageClass::ImageClass::\t" << " failed to create new surface. IMG_GetError=" << IMG_GetError();
		throw std::runtime_error (error.str());
	}

}

ImageClass::ImageClass (const Screen, const std::string &filename)
://	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
	data (new Data ())
{
    assert_file_path(filename);
    
	data-> surface = IMG_Load (filename.c_str ());

	if (! data-> surface)
	{
	    std::stringstream error;
        error << "ImageClass::ImageClass::\tfile " << filename << " failed to load. IMG_GetError=" << IMG_GetError();
		throw std::invalid_argument (error.str());
	}

    this-> convertTo32bpp (); // must use 32 bpp in order to allow pixel transformations to work without having to query pixel type etc.
    /*
	if (isTextureShaped ())
	{
		this-> convertTo24bpp ();
	}
	else
	{
		this-> convertTo32bpp ();
	}
	*/
}


ImageClass::ImageClass (const Screen, const std::string &filename, byte_t red, byte_t green, byte_t blue)
://	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
	data (new Data ())
{
	// same as above really //
	
	assert_file_path(filename);

	data-> surface = IMG_Load (filename.c_str ());

	if (! data-> surface)
	{
	    std::stringstream error;
        error << "ImageClass::ImageClass::\tfile " << filename << " failed to load. IMG_GetError=" << IMG_GetError();
		throw std::invalid_argument (error.str());
	}


	this-> convertTo32bpp ();

	// set appropriate alpha onto the bits:

	SDL_LockSurface (data-> surface);
	{

		SDL_Color * const first = (SDL_Color * const) data-> surface-> pixels;
		SDL_Color * const end = first + data-> surface-> w * data-> surface-> h;

		for (SDL_Color * pixel = first; pixel != end; ++pixel)
		{
			if (pixel-> r == red && pixel-> g == green && pixel-> b == blue)
			{
				pixel-> unused = 0;
			}
		}

	}
	SDL_UnlockSurface (data-> surface);
}


ImageClass::ImageClass (const Screen, const std::string &filename, const std::string &maskFilename)
://	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
	data (new Data ())
{
	// same as above really //
	
	assert_file_path(filename);
	assert_file_path(maskFilename);

	data-> surface = IMG_Load (filename.c_str ());

	if (! data-> surface)
	{
	    std::stringstream error;
        error << "ImageClass::ImageClass::\tfile " << filename << " failed to load. IMG_GetError=" << IMG_GetError();
		throw std::invalid_argument (error.str());
	}

	this-> convertTo32bpp ();

	// load mask image:

	SDL_Surface * mask = IMG_Load (maskFilename.c_str ());

	if (! mask)
	{
		SDL_FreeSurface (data-> surface);

	    std::stringstream error;
        error << "ImageClass::ImageClass::\tmask file " << maskFilename << " failed to load. IMG_GetError=" << IMG_GetError();
		throw std::invalid_argument (error.str());
	}

	int length = mask-> w * mask-> h;
	int surfaceLength = data-> surface-> w * data-> surface-> h;
	int maskUnitSize = mask-> format-> BytesPerPixel;

	if (maskUnitSize  < 1)
	{
		SDL_FreeSurface (data-> surface);
		SDL_FreeSurface (mask);

	    std::stringstream error;
        error << "ImageClass::ImageClass::\tmask file " << maskFilename << " has unsupported format for masking.";
		throw std::invalid_argument (error.str());
	}

	if (length > surfaceLength)
	{
		length = surfaceLength;
	}

	SDL_LockSurface (data-> surface);
	SDL_LockSurface (mask);
	{
		SDL_Color * const pixels = (SDL_Color * const) data-> surface-> pixels;
		byte_t * const masks = (byte_t * const) mask-> pixels;

		for (int i = 0; i < length; ++i)
		{
			pixels[i]. unused = masks[i * maskUnitSize];
		}

	}
	SDL_UnlockSurface (data-> surface);
	SDL_UnlockSurface (mask);

	SDL_FreeSurface (mask);
}

void ImageClass::assert_file_path(std::string filename) const // aab::test::file_not_found_error
{
    if (! boost::filesystem::exists(filename))
    {
        std::string error;
        error += "ImageClass::assert_file_path::\tfile " + filename + " does not exist.";
        throw aab::test::file_not_found_error(error);
    }
}

ImageClass::~ImageClass () //throw ()
{
	SDL_FreeSurface (data-> surface);
}


int ImageClass::getWidth () const
{
	return data-> surface-> w;
}

int ImageClass::getHeight () const
{
	return data-> surface-> h;
}

int ImageClass::getBitsPerPixel () const
{
	return data-> surface-> format-> BitsPerPixel;
}


void ImageClass::expandClearEdgesTo (int newWidth, int newHeight, ExpandDirection expand_direction) //std::runtime_error, std::invalid_argument
{

	SDL_Surface * oldSurface = data-> surface;
	SDL_Rect drawRect;// =	{, , 0, 0};
	
	switch(expand_direction)
	{    
    case EXPAND_TOP_LEFT:drawRect.x = 0;   drawRect.y = 0; break;
    case EXPAND_TOP_RIGHT:drawRect.x = (newWidth - getWidth());   drawRect.y = 0; break;
    case EXPAND_BOTTOM_LEFT:drawRect.x = 0;   drawRect.y = (newHeight - getHeight()); break;
    case EXPAND_BOTTOM_RIGHT :drawRect.x = (newWidth - getWidth());   drawRect.y = (newHeight - getHeight()); break;    
    case EXPAND_CENTRE: default: drawRect.x = (newWidth - getWidth())/2;   drawRect.y = (newHeight - getHeight())/2; break;
	}    
    
	if (newWidth < getWidth () || newHeight < getHeight ())
	{
		throw std::invalid_argument ("ImageClass::expandClearEdgesTo:: Invalid dimensions for image expansion");
	}

	if (newWidth == getWidth () && newHeight == getHeight ())
	{
		return;
	}


	data-> surface = SDL_CreateRGBSurface (0, newWidth, newHeight, getBitsPerPixel (), 0x000000ff,
										0x0000ff00, 0x00ff0000, 0xff000000);
										
	if (! data-> surface)
	{
        std::stringstream error;
        error << "ImageClass::expandClearEdgesTo:: failed to create surface. SDL_GetError=" << SDL_GetError ();
        throw std::runtime_error (error.str());
	}

	//set the alpha up so that it pastes/copies the alpha value rather than blending:

	if (SDL_SetAlpha (oldSurface, 0, 0) == -1)
	{
		SDL_FreeSurface (oldSurface);

        std::stringstream error;
        error << "ImageClass::expandClearEdgesTo:: failed to set surface alpha. SDL_GetError=" << SDL_GetError ();
        throw std::runtime_error (error.str());
	}


	if ( SDL_BlitSurface (oldSurface, NULL, data-> surface, &drawRect) == -1)
	{
		SDL_FreeSurface (oldSurface);

        std::stringstream error;
        error << "ImageClass::expandClearEdgesTo:: failed to blit old surface to new surface. SDL_GetError=" << SDL_GetError ();
        throw std::runtime_error (error.str());
	}


	SDL_FreeSurface (oldSurface);
}



void ImageClass::readPixels (PixelReadOperation & operation)
{
	SDL_LockSurface (data-> surface);
	{
		SDL_Color * const first = (SDL_Color * const) data-> surface-> pixels;
		SDL_Color * const end = first + data-> surface-> w * data-> surface-> h;

		for (SDL_Color * pixel = first; pixel != end; ++pixel)
		{
		    //operation(pixel-> r, pixel-> g, pixel-> b, pixel-> unused);
		    operation((Pixel*)pixel);
		}
	}
	SDL_UnlockSurface (data-> surface);
}

void ImageClass::readPixels (PixelReadXYOperation & operation)
{
    int x = 0, y = 0;
    
	SDL_LockSurface (data-> surface);
	{
		SDL_Color * const first = (SDL_Color * const) data-> surface-> pixels;
		SDL_Color * const end = first + data-> surface-> w * data-> surface-> h;

		for (SDL_Color * pixel = first; pixel != end; ++pixel)
		{
		    //operation(pixel-> r, pixel-> g, pixel-> b, pixel-> unused, x, y);
		    operation((Pixel *)pixel, x, y);
		    if (++x == data->surface->w)
		    {
		        x = 0;
		        ++y;
		    }
		}
	}
	SDL_UnlockSurface (data-> surface);
}

void ImageClass::transformPixels (PixelWriteOperation & operation)
{
	SDL_LockSurface (data-> surface);
	{
		SDL_Color * const first = (SDL_Color * const) data-> surface-> pixels;
		SDL_Color * const end = first + data-> surface-> w * data-> surface-> h;

		for (SDL_Color * pixel = first; pixel != end; ++pixel)
		{
		    //operation(pixel-> r, pixel-> g, pixel-> b, pixel-> unused);
		    operation((Pixel*)pixel);
		}
	}
	SDL_UnlockSurface (data-> surface);
}

void ImageClass::transformPixels (PixelWriteXYOperation & operation)
{
    int x = 0, y = 0;
    
	SDL_LockSurface (data-> surface);
	{
		SDL_Color * const first = (SDL_Color * const) data-> surface-> pixels;
		SDL_Color * const end = first + data-> surface-> w * data-> surface-> h;

		for (SDL_Color * pixel = first; pixel != end; ++pixel)
		{
		    //operation(pixel-> r, pixel-> g, pixel-> b, pixel-> unused, x, y);
		    operation((Pixel *)pixel, x, y);
		    if (++x == data->surface->w)
		    {
		        x = 0;
		        ++y;
		    }
		}
	}
	SDL_UnlockSurface (data-> surface);
}

void ImageClass::convertTo24bpp()// std::runtime_error
{
	SDL_Surface * oldSurface = data-> surface;
	SDL_PixelFormat format;

	if (data-> surface-> format-> BitsPerPixel != 24)
	{
		format.palette = NULL;
		format.BitsPerPixel = 24;
		format.BytesPerPixel = 4;
		format.Rmask = 0x000000ff;
		format.Gmask = 0x0000ff00;
		format.Bmask = 0x00ff0000;
		format.Amask = 0xff000000;
		format.Rshift = 0;
		format.Gshift = 8;
		format.Bshift = 16;
		format.Ashift = 24;
		format.colorkey = 0;
		format.alpha = 255;

		data-> surface = SDL_ConvertSurface (data-> surface, &format, 0);

		SDL_FreeSurface (oldSurface);

		if (! data-> surface)
		{
            std::stringstream error;
            error << "ImageClass::convertTo24bpp:: failed to convert surface. SDL_GetError=" << SDL_GetError ();
            throw std::runtime_error (error.str());
		}
	}
}

void ImageClass::convertTo32bpp()// std::runtime_error
{
	SDL_Surface * oldSurface = data-> surface;
	SDL_PixelFormat format;

	if (data-> surface-> format-> BitsPerPixel != 32)
	{
		format.palette = NULL;
		format.BitsPerPixel = 32;
		format.BytesPerPixel = 4;
		format.Rmask = 0x000000ff;
		format.Gmask = 0x0000ff00;
		format.Bmask = 0x00ff0000;
		format.Amask = 0xff000000;
		format.Rshift = 0;
		format.Gshift = 8;
		format.Bshift = 16;
		format.Ashift = 24;
		format.colorkey = 0;
		format.alpha = 255;

		data-> surface = SDL_ConvertSurface (data-> surface, &format, 0);

		SDL_FreeSurface (oldSurface);

		if (! data-> surface)
		{
            std::stringstream error;
            error << "ImageClass::convertTo24bpp:: failed to convert surface. SDL_GetError=" << SDL_GetError ();
            throw std::runtime_error (error.str());
		}
	}
}


bool ImageClass::isTextureShaped () const
{
	if (data-> surface-> w < 64 || data-> surface-> h < 64)
	{
		return false;
	}

	if (!isPowerOf2 (data-> surface-> h))
	{
		return false;
	}

	if (!isPowerOf2 (data-> surface-> w))
	{
		return false;
	}

	return true;
}



const void *ImageClass::accessPixels () const
{
	return data-> surface-> pixels;
}

void ImageClass::lockPixels()
{
    SDL_LockSurface (data-> surface);
}

void ImageClass::unlockPixels()
{
    SDL_UnlockSurface (data-> surface);
}

Pixel ImageClass::readPixel (const int x, const int y)const
{
    return ((Pixel *) data->surface->pixels) [x + y * data-> surface-> w];
}

Pixel * ImageClass::accessPixel (const int x, const int y)
{
    return ((Pixel *) data->surface->pixels) + x + y * data-> surface-> w;
}


bool ImageClass::saveBmp(const std::string&filename)const
{
    return ! SDL_SaveBMP(data-> surface,filename.c_str());
}
	
/*
bool ImageClass::savePng(const std::string&filename)const
{
	return ! png_save_surface(filename.c_str(), data->surface);
    
}*/

void setSDLRect(SDL_Rect&rect, const int left, const int top, const int right, const int bottom)
{
    rect.x = left;
    rect.y = top;
    rect.w = right-left;
    rect.h = bottom-top;
}

bool ImageClass::copyInto(ImageClass&other, const int x, const int y)
{
    SDL_Rect destRect;
    destRect.x = x + getWidth()/2; 
    destRect.y = y + getHeight()/2;

    return 0 == SDL_BlitSurface(data->surface, NULL, other.data->surface, &destRect);
}

bool ImageClass::copyCroppedInto(const int left, const int top, const int right, const int bottom, ImageClass&other, const int x, const int y)
{
    SDL_Rect sourceRect;
    setSDLRect(sourceRect, left, top, right, bottom);
    
    SDL_Rect destRect;
    destRect.x = x + sourceRect.w/2,
    destRect.x = y + sourceRect.h/2;

    return 0 == SDL_BlitSurface(data->surface, &sourceRect, other.data->surface, &destRect);
}

//todo - add filling methods

void ImageClass::fill(aab::visen::Colorub color)
{
    SDL_FillRect(data->surface, NULL, SDL_MapRGBA(data->surface->format, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha()));
}

void ImageClass::fill(aab::visen::Colorub color, const int left, const int top, const int right, const int bottom)
{
    SDL_Rect rect; setSDLRect(rect,left, top, right, bottom);
    SDL_FillRect(data->surface, &rect, SDL_MapRGBA(data->surface->format, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha()));
}

void ImageClass::setClipRect(const int left, const int top, const int right, const int bottom)
{
    SDL_Rect rect; setSDLRect(rect,left, top, right, bottom);
    SDL_SetClipRect(data->surface, &rect);
}

void ImageClass::removeClipRect()
{
    SDL_SetClipRect(data->surface, NULL);
}

}		//	visen
}		//	aab





