/**
*
*	animated_texture.cpp
*
*	methods assume that GL_TEXTURE_2D is enabled; any class which changes this
*	state should thus restore it before continuing.
*
*	should be changed to analyse wether blending is needed and allow a change
**/

#include"animated_texture.hpp"
//#include"../time/time_reporter.hpp"
#include"../types/smart_ptr.hpp"
#include<sdl.H>
#include"_include_opengl.hpp"
#include"quad.hpp"
#include<stdexcept>
#include"../test/debug_assertions.hpp"
#include"../types/const.hpp"
#include<cassert>
namespace aab	{
namespace visen	{
//using aab::time::FrameTicker;
//using aab::time::StuckTimeReporter;
typedef AnimatedTextureClass ATC;

/*
class TimeReporter : public aab::time::TimeReporter
{
	public:

	typedef aab::types::Smart <TimeReporter>::Ptr Ptr;

	double getChange () const
	{
		return 1;
	}

	void update ()
	{
		// nothing //
	}

};
*/

//StuckTimeReporter::Ptr timeReporter (new aab::time::StuckTimeReporter ());
//FrameTicker::Ptr ATC::stillTicker (new FrameTicker(timeReporter));




/*
AnimatedTexturePtr makeAnimatedTexture (TexturePtr texture, FrameTicker::Ptr ticker,
	int frameWidth, int frameHeight) throw (std::exception &)
{
	AnimatedTexturePtr ptr (new AnimatedTextureClass (texture, ticker,
						frameWidth, frameHeight), AnimatedTextureClass::Deleter ());

	return ptr;
}
*/

AnimatedTexturePtr makeAnimatedTexture (TexturePtr texture,
	int frameWidth, int frameHeight) //std::invalid_argument
{
	AnimatedTexturePtr ptr (new AnimatedTextureClass (texture, //AnimatedTextureClass::stillTicker,
						frameWidth, frameHeight), AnimatedTextureClass::Deleter ());

	return ptr;
}




ATC::AnimatedTextureClass (TexturePtr texture, //FrameTicker::Ptr ticker,
                           int frameWidth, int frameHeight)
://	std::invalid_argument
	//ticker (ticker),
	FramedTextureClass(texture),
	wfrac (static_cast <float> (frameWidth) / texture-> getOutputWidth ()),
	hfrac (static_cast <float> (frameHeight) / texture-> getOutputHeight ()),
	drawWidth (frameWidth),
	drawHeight (frameHeight),
	horizontalFrames (texture-> getImageWidth () / frameWidth),
	maxFrame (horizontalFrames * (texture-> getImageHeight () / frameHeight) - 1)
{
	if (frameWidth < 1 || frameWidth > texture-> getImageWidth ())
	{
		throw std::invalid_argument ("AnimatedTextureClass::AnimatedTextureClass::\tinvalid frameWidth");
	}

	if (frameHeight < 1 || frameHeight > texture-> getImageHeight ())
	{
		throw std::invalid_argument ("AnimatedTextureClass::AnimatedTextureClass::\tinvalid frameHeight");
	}
	
	updateTextureCoordinates();

	//if (ticker == 0)
	//{
	//	ticker = stillTicker;
	//}
}


ATC::~AnimatedTextureClass ()// throw ()
{
	/* nothing */
}

/*FrameTicker::Ptr ATC::getFrameTickerPtr () throw (std::exception &)
{
	return ticker;
}*/

/*
TexturePtr ATC::getTexture ()
{
	return texture;
}
*/

int ATC::getMaximumFrame () const
{
	return maxFrame;
}

void ATC::setFrame(int frame) //_DEBUG std::invalid_argument
{
    if (frame < 0 || frame > maxFrame)
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("AnimatedTextureClass::setFrame::frame in out of bounds"));
        _RELEASE_RESPONSE(frame = 0);
    }
        
    if (frame != currentFrame)
    {
        currentFrame = frame;
        updateTextureCoordinates();
    }
}

/*
void ATC::render ()
{
	//renderFrame (ticker-> getFrame ());
	renderFrame (currentFrame);
}*/

/**
void ATC::render ()
{
	//
	//	this method assumes the following:
	//	glEnable (GL_TEXTURE_2D);
	//	glEnable (GL_BLEND);
	//	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	
	texture->bind();
	renderNobind();
}

void ATC::bind() throw()
{
    texture-> bind();
}*/

void ATC::renderNobind ()
{
	//
	//	this method assumes the following:
	//	glEnable (GL_TEXTURE_2D);
	//	glEnable (GL_BLEND);
	//	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	
	const float hw = this-> drawWidth / 2;
	const float hh = this-> drawHeight / 2;
	float phw = hw;
	float phh = hh;
	
    /*if (static_cast<int>(drawWidth)%2)
    {
        phw += 1.0f;
    }
    if (static_cast<int>(drawHeight)%2)
    {
        phh += 1.0f;
    }
    */

	glBegin (GL_QUADS);
	{
		glTexCoord2f(texCoord[0].x,texCoord[0].y);
		glVertex2f (-hw, -hh);

		glTexCoord2f(texCoord[1].x,texCoord[1].y);
		glVertex2f (-hw, phh);

		glTexCoord2f(texCoord[2].x,texCoord[2].y);
		glVertex2f (phw, phh);

		glTexCoord2f(texCoord[3].x,texCoord[3].y);
		glVertex2f (phw, -hh);

	}
	glEnd ();

}


void ATC::updateTextureCoordinates()
{
	float xframe = currentFrame % horizontalFrames;
	float yframe = currentFrame / horizontalFrames;

	float wfrac = this-> wfrac;
	float hfrac = this-> hfrac;
	float tx = 0 + xframe * wfrac;
	float ty = hfrac + yframe * hfrac;
	//float hw = this-> drawWidth / 2;
	//float hh = this-> drawHeight / 2;
	
	texCoord[static_cast<unsigned int>(texCoordPos[0])].set(tx, ty - hfrac);
	texCoord[static_cast<unsigned int>(texCoordPos[1])].set(tx, ty);
	texCoord[static_cast<unsigned int>(texCoordPos[2])].set(tx + wfrac, ty);
	texCoord[static_cast<unsigned int>(texCoordPos[3])].set(tx + wfrac, ty - hfrac);
}

/*
void ATC::renderFrame (int frame)
{
	//
	//	this method assumes the following:
	//	glEnable (GL_TEXTURE_2D);
	//	glEnable (GL_BLEND);
	//	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	
    if (frame < 0 || frame > maxFrame)
    {
        throw std::invalid_argument("frame in out of bounds");
    }

	texture-> bind();

	//float xframe = frame % horizontalFrames;
	//float yframe = frame / horizontalFrames;

	//float wfrac = this-> wfrac;
	//float hfrac = this-> hfrac;
	//float tx = 0 + xframe * wfrac;
	//float ty = hfrac + yframe * hfrac;
	float hw = this-> drawWidth / 2;
	float hh = this-> drawHeight / 2;

	glBegin (GL_QUADS);
	{
	    
		//glTexCoord2f (tx, ty - hfrac);//1
		glTexCoord2f(texCoord[0].x,texCoord[0].y);
		glVertex2f (-hw, -hh);

		//glTexCoord2f (tx, ty);//2
		glTexCoord2f(texCoord[1].x,texCoord[1].y);
		glVertex2f (-hw, hh);

		//glTexCoord2f (tx + wfrac, ty);//3
		glTexCoord2f(texCoord[2].x,texCoord[2].y);
		glVertex2f (hw, hh);

		//glTexCoord2f (tx + wfrac, ty - hfrac);//4
		glTexCoord2f(texCoord[3].x,texCoord[3].y);
		glVertex2f (hw, -hh);
		


	}
	glEnd ();

}
*/

/*
void ATC::renderFrameHFlipped (int frame)
{
	//
	//	this method assumes the following:
	//	glEnable (GL_TEXTURE_2D);
	//	glEnable (GL_BLEND);
	//	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	
    if (frame < 0 || frame > maxFrame)
    {
        throw std::invalid_argument("frame in out of bounds");
    }

	texture-> bind();

	float xframe = frame % horizontalFrames;
	float yframe = frame / horizontalFrames;

	float wfrac = this-> wfrac;
	float hfrac = this-> hfrac;
	float tx = 0 + xframe * wfrac;
	float ty = hfrac + yframe * hfrac;
	float hw = this-> drawWidth / 2;
	float hh = this-> drawHeight / 2;

	glBegin (GL_QUADS);
	{
	    // todo update to use texture coords
		glTexCoord2f (tx + wfrac, ty - hfrac);//4
		glVertex2f (-hw, -hh);

		glTexCoord2f (tx + wfrac, ty);//3
		glVertex2f (-hw, hh);

		glTexCoord2f (tx, ty);//2
		glVertex2f (hw, hh);

		glTexCoord2f (tx, ty - hfrac);//1
		glVertex2f (hw, -hh);
	}
	glEnd ();

}
*/

/*
void ATC::renderFrameVFlipped (int frame)
{
	//
	//	this method assumes the following:
	//	glEnable (GL_TEXTURE_2D);
	//	glEnable (GL_BLEND);
	//	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	
    if (frame < 0 || frame > maxFrame)
    {
        throw std::invalid_argument("frame in out of bounds");
    }

	texture-> bind();

	float xframe = frame % horizontalFrames;
	float yframe = frame / horizontalFrames;

	float wfrac = this-> wfrac;
	float hfrac = this-> hfrac;
	float tx = 0 + xframe * wfrac;
	float ty = hfrac + yframe * hfrac;
	float hw = this-> drawWidth / 2;
	float hh = this-> drawHeight / 2;

	glBegin (GL_QUADS);
	{
	    // todo update to use texture coords
		glTexCoord2f (tx, ty);//2
		glVertex2f (-hw, -hh);

		glTexCoord2f (tx, ty - hfrac);//1
		glVertex2f (-hw, hh);

		glTexCoord2f (tx + wfrac, ty - hfrac);//4
		glVertex2f (hw, hh);

		glTexCoord2f (tx + wfrac, ty);//3
		glVertex2f (hw, -hh);
	}
	glEnd ();

}

*/

/*
void ATC::renderUnboundFrame (int frame)
{
	//
	//	this method assumes the following:
	//	glEnable (GL_TEXTURE_2D);
	//	glEnable (GL_BLEND);
	//	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
    if (frame < 0 || frame > maxFrame)
    {
        throw std::invalid_argument("frame in out of bounds");
    }

	float xframe = getFrameX(frame);
	float yframe = getFrameY(frame);

	float wfrac = this-> wfrac;
	float hfrac = this-> hfrac;
	float tx = 0 + xframe * wfrac;
	float ty = hfrac + yframe * hfrac;
	float hw = this-> drawWidth / 2;
	float hh = this-> drawHeight / 2;

	glBegin (GL_QUADS);
	{
	    // todo update to use texture coords
		glTexCoord2f (tx, ty - hfrac);
		glVertex2f (-hw, -hh);

		glTexCoord2f (tx, ty);
		glVertex2f (-hw, hh);

		glTexCoord2f (tx + wfrac, ty);
		glVertex2f (hw, hh);

		glTexCoord2f (tx + wfrac, ty - hfrac);
		glVertex2f (hw, -hh);
	}
	glEnd ();

}
*/

float ATC::getFrameX(int frame) const
{
	return frame % horizontalFrames;
}

float ATC::getFrameY(int frame) const
{
	return frame / horizontalFrames;
}

void ATC::getCCWTextureCoordinatesFor(unsigned int frame, Vertex * first) const
{
    if (frame > maxFrame)
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("AnimatedTextureClass::getTextureCoordinatesFor::\tinvalid frame."));
        _RELEASE_RESPONSE(return);
    }
    
    assert(first);
    
    cfloat xframe = getFrameX(frame);
    cfloat yframe = getFrameY(frame);

    cfloat wfrac = getTextureCoordinateWidth(); //game_constant::gl_tile_length;//texture->getTextureCoordinateWidth();
    cfloat hfrac = getTextureCoordinateHeight(); //game_constant::gl_tile_length;//texture->getTextureCoordinateHeight();
    cfloat tx = 0 + xframe * wfrac;
    cfloat ty = hfrac + yframe * hfrac;    
						
    /*tile_vertices[  quad_index].textCoord.set(tx,       ty-hfrac);
    tile_vertices[++quad_index].textCoord.set(tx,       ty);
    tile_vertices[++quad_index].textCoord.set(tx+wfrac, ty);
    tile_vertices[++quad_index].textCoord.set(tx+wfrac, ty-hfrac);*/
    
    static_cast<aab::visen::CCWQuad*>(static_cast<void*>(first))->setTextureCoordinates(tx,ty,wfrac,hfrac);  
}

void ATC::getClippedTextureCoordinatesFor 
    (const unsigned int frame, Vertex * first, const float left,
     const float bottom, const float right, const float top) const 
{
    if (frame > maxFrame)
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("AnimatedTextureClass::getClippedTextureCoordinatesFor::\tinvalid frame."));
        _RELEASE_RESPONSE(return);
    }
    
    assert(first);    
    
    cfloat full_w = getFrameWidth();
    cfloat full_h = getFrameHeight();
    cfloat full_x = 0.5f*(full_w) + getFrameX(frame);
    cfloat full_y = 0.5f*(full_h) + getFrameY(frame);
    
    cfloat x1 = full_x + full_w*left;
    cfloat y1 = full_y + full_h*bottom;
    cfloat x2 = full_x + full_w*right;
    cfloat y2 = full_y + full_h*top;

	//first[0].textCoord.x = x1; first[0].textCoord.y = y1;	
	//first[1].textCoord.x = x1; first[1].textCoord.y = y2;	
	//first[2].textCoord.x = x2; first[2].textCoord.y = y1;
	//first[3].textCoord.x = x2; first[3].textCoord.y = y2;
	
	static_cast<aab::visen::StripQuad*>(static_cast<void*>(first))->setTexturePanel(x1,y1,x2,y2);
}

void ATC::getCCWClippedTextureCoordinatesFor 
    (const unsigned int frame, Vertex * first, const float left,
     const float bottom, const float right, const float top) const 
{
    if (frame > maxFrame)
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("AnimatedTextureClass::getClippedTextureCoordinatesFor::\tinvalid frame."));
        _RELEASE_RESPONSE(return);
    }
    
    assert(first);
    
    cfloat full_w = getFrameWidth();
    cfloat full_h = getFrameHeight();
    cfloat full_x = 0.5f*(full_w) + getFrameX(frame);
    cfloat full_y = 0.5f*(full_h) + getFrameY(frame);
    
    cfloat x1 = full_x + full_w*left;
    cfloat y1 = full_y + full_h*bottom;
    cfloat x2 = full_x + full_w*right;
    cfloat y2 = full_y + full_h*top;

	//first[0].textCoord.x = x1; first[0].textCoord.y = y1;	
	//first[1].textCoord.x = x1; first[1].textCoord.y = y2;	
	//first[2].textCoord.x = x2; first[2].textCoord.y = y2;
	//first[3].textCoord.x = x2; first[3].textCoord.y = y1;
	
	static_cast<aab::visen::CCWQuad*>(static_cast<void*>(first))->setTexturePanel(x1,y1,x2,y2);
}


void ATC::getStripTextureCoordinatesFor(unsigned int frame, Vertex * first) const
{
    if (frame > maxFrame)
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("AnimatedTextureClass::getTextureCoordinatesFor::\tinvalid frame."));
        _RELEASE_RESPONSE(return);
    }
    
    cfloat xframe = getFrameX(frame);
    cfloat yframe = getFrameY(frame);

    cfloat wfrac = getTextureCoordinateWidth(); //game_constant::gl_tile_length;//texture->getTextureCoordinateWidth();
    cfloat hfrac = getTextureCoordinateHeight(); //game_constant::gl_tile_length;//texture->getTextureCoordinateHeight();
    cfloat tx = 0 + xframe * wfrac;
    cfloat ty = hfrac + yframe * hfrac;    
						
    /*tile_vertices[  quad_index].textCoord.set(tx,       ty-hfrac);
    tile_vertices[++quad_index].textCoord.set(tx,       ty);
    tile_vertices[++quad_index].textCoord.set(tx+wfrac, ty);
    tile_vertices[++quad_index].textCoord.set(tx+wfrac, ty-hfrac);*/
    
    static_cast<aab::visen::StripQuad*>(static_cast<void*>(first))->setTextureCoordinates(tx,ty,wfrac,hfrac);  
}
bool ATC::isValidFrame (unsigned int frame) const
{
    return frame <= maxFrame;
}

/*
void ATC::updateTicker ()
{
	ticker-> update ();
}

bool ATC::hasFrameTickerPtr () const
{
	return true;
}
*/


}		//	visen
}		//	aab

