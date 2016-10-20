/**
*
*	framed_texture.cpp
*
*	methods assume that GL_TEXTURE_2D is enabled; any class which changes this
*	state should thus restore it before continuing.
*
*	should be changed to analyse wether blending is needed and allow a change
**/

#include"framed_texture.hpp"
//#include"../time/time_reporter.hpp"
#include"../types/smart_ptr.hpp"
#include<sdl.H>
#include"_include_opengl.hpp"
#include<stdexcept>
#include"../test/debug_assertions.hpp"
namespace aab	{
namespace visen	{
//using aab::time::FrameTicker;
//using aab::time::StuckTimeReporter;
typedef FramedTextureClass FTC;

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
//FrameTicker::Ptr FTC::stillTicker (new FrameTicker(timeReporter));




/*
AnimatedTexturePtr makeAnimatedTexture (TexturePtr texture, FrameTicker::Ptr ticker,
	int frameWidth, int frameHeight) throw (std::exception &)
{
	AnimatedTexturePtr ptr (new AnimatedTextureClass (texture, ticker,
						frameWidth, frameHeight), AnimatedTextureClass::Deleter ());

	return ptr;
}
*/

/*
FramedTexturePtr makeFramedTexture (TexturePtr texture,
	int frameWidth, int frameHeight) //std::invalid_argument
{
	FramedTexturePtr ptr (new AnimatedTextureClass (texture, //AnimatedTextureClass::stillTicker,
						frameWidth, frameHeight), AnimatedTextureClass::Deleter ());

	return ptr;
}*/




FTC::FramedTextureClass (TexturePtr texture)
://	std::invalid_argument
	//ticker (ticker),
	texture (texture),
	currentFrame(0)
{
    // nothing //
}


FTC::~FramedTextureClass ()// throw ()
{
	/* nothing */
}

/*FrameTicker::Ptr FTC::getFrameTickerPtr () throw (std::exception &)
{
	return ticker;
}*/

/*
int FTC::getMaximumFrame () const
{
	return maxFrame;
}*/


/*
void FTC::render ()
{
	//renderFrame (ticker-> getFrame ());
	renderFrame (currentFrame);
}*/

void FTC::render ()
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

void FTC::bind() throw()
{
    texture-> bind();
}




/*
void FTC::renderFrame (int frame)
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
void FTC::renderFrameHFlipped (int frame)
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
void FTC::renderFrameVFlipped (int frame)
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
void FTC::renderUnboundFrame (int frame)
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



/*
void FTC::updateTicker ()
{
	ticker-> update ();
}

bool FTC::hasFrameTickerPtr () const
{
	return true;
}
*/


}		//	visen
}		//	aab

