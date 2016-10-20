/**
*
*	texture_atlas.cpp
*
*	methods assume that GL_TEXTURE_2D is enabled; any class which changes this
*	state should thus restore it before continuing.
*
*
*
*   NOTE: Should be optimised to pre-calculate the texture coordinates and store themf or each frame, rather than working them out each time.
*   The original width and height may need to be retained to allow each sprite to be drawn
**/

//TODO change to use unsigned frame width and heights

#include"texture_atlas.hpp"
#include<sdl.H>
#include"_include_opengl.hpp"
#include"../test/debug_assertions.hpp"
namespace aab	{
namespace visen	{

typedef TextureAtlasClass TAC;


TextureAtlasPtr makeTextureAtlas (TexturePtr texture) //std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{
	TextureAtlasPtr ptr (new TextureAtlasClass (texture), TextureAtlasClass::Deleter ());

	return ptr;
}


TAC::TextureAtlasClass (TexturePtr texture)://std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
    FramedTextureClass(texture)
{
    // nothing //
}


TAC::~TextureAtlasClass () throw ()
{
	// nothing //
}

void TAC::addFrame (int x, int y, int width, int height) //_DEBUG std::invalid_argument
{
    AtlasFrame frame;
    
    const float textureWidth = texture->getOutputWidth();
    const float textureHeight = texture->getOutputHeight();
    
    frame.width = width;
    frame.height = height;
    frame.x1 = static_cast<float>(x)/textureWidth;
    frame.y1 = static_cast<float>(y)/textureHeight;
    frame.x2 = static_cast<float>(x+width)/textureWidth;
    frame.y2 = static_cast<float>(y+height)/textureHeight;
    
    frames.push_back(frame);
    
    if (currentFrame < 0)
    {
        setFrame(0);
    }
}

void TAC::addFrames (FrameDefinition * framesIn, unsigned int frameCount) //_DEBUG std::invalid_argument
{
    #ifdef _DEBUG
        if (frameCount > AAB_VISEN_TEXTURE_ATLAS_MAX_FRAMES)
        {
            throw std::invalid_argument("TextureAtlasClass::addFrames:: frame count abnormally large - extend maximum frames or check code");
        }
        if (! framesIn)
        {
            throw std::invalid_argument("TextureAtlasClass::addFrames:: FrameDefinition * framesIn is NULL");
        }
    #endif
        
    const float textureWidth = texture->getOutputWidth();
    const float textureHeight = texture->getOutputHeight();
    AtlasFrame frame;
    
    for (unsigned int t = 0; t < frameCount; t++)
    { 
        frame.x1 = static_cast<float>(framesIn[t].x)/textureWidth;
        frame.y1 = static_cast<float>(framesIn[t].y)/textureHeight;
        frame.x2 = static_cast<float>(framesIn[t].x+framesIn[t].w)/textureWidth;
        frame.y2 = static_cast<float>(framesIn[t].y+framesIn[t].h)/textureHeight;
        frame.width = framesIn[t].w;
        frame.height = framesIn[t].h;
        /*
        frame.x1 = static_cast<float>(framesIn[4*t])/textureWidth;
        frame.y1 = static_cast<float>(framesIn[4*t+1])/textureHeight;
        frame.x2 = static_cast<float>(framesIn[4*t]+framesIn[4*t+2])/textureWidth;
        frame.y2 = static_cast<float>(framesIn[4*t+1]+framesIn[4*t+3])/textureHeight;
        frame.width = framesIn[4*t+2];
        frame.height = framesIn[4*t+3];
        */
        frames.push_back(frame);
    }
    
    if (currentFrame < 0)
    {
        setFrame(1);
    }
}

/*
TexturePtr TAC::getTexture ()
{
	return texture;
}
*/

int TAC::getMaximumFrame () const
{
	return static_cast<int>(frames.size()) - 1;
}


bool TAC::isValidFrame (unsigned int frame) const
{
    return static_cast<int>(frame) <= getMaximumFrame(); //todo - optimize - same as animated texture so move to framed_texture 
}

void TAC::setFrame(int frame) //_DEBUG std::invalid_argument
{
    if (frame < 0 || frame >= static_cast<signed int>(frames.size()))
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("TextureAtlasClass::setFrame::\tframe in out of bounds."));
        _RELEASE_RESPONSE(frame = 0);        
    }
        
    if (frame != currentFrame)
    {
        currentFrame = frame;
        updateTextureCoordinates(frames[currentFrame]);
    }
}

/*
void TAC::setFrameHFlipped(int frame)
{
    if (frame < 0 || frame >= frames.size())
    {
        throw std::invalid_argument("frame in out of bounds");
    }
        
    if (frame != currentFrame)
    {
        currentFrame = frame;
        updateTextureCoordinates(frames[currentFrame]); //todo - create this method - CHANGE to be H flipped from source
    }
}
*/

/*
void TAC::render ()
{
	//
	//	this method assumes the following:
	//	glEnable (GL_TEXTURE_2D);
	//	glEnable (GL_BLEND);
	//	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	
	texture-> bind();
	renderNobind();
}


void TAC::bind() throw()
{
    texture-> bind();
}*/

void TAC::renderNobind ()
{
	//
	//	this method assumes the following:
	//	glEnable (GL_TEXTURE_2D);
	//	glEnable (GL_BLEND);
	//	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	
	const float hw = frames[currentFrame].width / 2;
	const float hh = frames[currentFrame].height / 2;
	float phw = hw;
	float phh = hh;
	/*
    if (static_cast<int>(frames[currentFrame].width)%2)
    {
        phw += 1.0f;
    }
    if (static_cast<int>(frames[currentFrame].height)%2)
    {
        phh += 1.0f;
    }*/
    
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

void TAC::updateTextureCoordinates(const AtlasFrame & frame)
{
	texCoord[(int)texCoordPos[0] ].set(frame.x1,frame.y1);
	texCoord[(int)texCoordPos[1] ].set(frame.x1,frame.y2);
	texCoord[(int)texCoordPos[2] ].set(frame.x2,frame.y2);
	texCoord[(int)texCoordPos[3] ].set(frame.x2,frame.y1);
}

float TAC::getFrameX(int frame) const
{
    #ifdef _DEBUG
    if (frame < 0 || static_cast<unsigned int>(frame) >= frames.size())
    {
        throw std::invalid_argument ("TextureAtlasClass::getFrameX(): frame size too large");
    }
    #endif
    return frames[frame].x1 * texture->getOutputWidth();
}

float TAC::getFrameY(int frame) const
{
    #ifdef _DEBUG
    if (frame < 0 || static_cast<unsigned int>(frame) >= frames.size())
    {
        throw std::invalid_argument ("TextureAtlasClass::getFrameY(): frame size too large");
    }
    #endif
    return frames[frame].y1 * texture->getOutputHeight();
}
	
int TAC::getFrameWidth (const unsigned int frame)const //_DEBUG std::invalid_argument
{
    #ifdef _DEBUG
    if (frame >= frames.size())
    {
        throw std::invalid_argument ("TextureAtlasClass::getFrameWidth(): frame size too large");
    }
    #endif
    return frames[frame].width;
}

int TAC::getFrameHeight (const unsigned int frame)const //_DEBUG std::invalid_argument
{
    #ifdef _DEBUG
    if (frame >= frames.size())
    {
        throw std::invalid_argument ("TextureAtlasClass::getFrameWidth(): frame size too large");
    }
    #endif
    return frames[frame].height;
}

void TAC::getTextureCoordinatesFor(unsigned int frame, float * first, unsigned int offset) const //_DEBUG std::invalid_argument
{
    #ifdef _DEBUG
    if (frame >= frames.size())
    {
        throw std::invalid_argument ("TextureAtlasClass::getTextureCoordinatesFor(): frame size too large");
    }
    #endif
	
	first[0] = frames[frame].x1; first[1] = frames[frame].y1;	
	first+=offset;
	first[0] = frames[frame].x1; first[1] = frames[frame].y2;
	first+=offset;
	first[0] = frames[frame].x2; first[1] = frames[frame].y1;
	first+=offset;	
	first[0] = frames[frame].x2; first[1] = frames[frame].y2;
}

void TAC::getStripTextureCoordinatesFor(unsigned int frame, Vertex * first) const //_DEBUG std::invalid_argument
{
    #ifdef _DEBUG
    if (frame >= frames.size())
    {
        throw std::invalid_argument ("TextureAtlasClass::getTextureCoordinatesFor(): frame size too large");
    }
    if (!first)
    {
        throw std::invalid_argument ("TextureAtlasClass::getTextureCoordinatesFor(): null pointer argument");
    }
    #else
    if (frame >= frames.size())
    {
        return;
    }
    #endif

	first[0].textCoord.x = frames[frame].x1; first[0].textCoord.y = frames[frame].y1;	
	first[1].textCoord.x = frames[frame].x1; first[1].textCoord.y = frames[frame].y2;	
	first[2].textCoord.x = frames[frame].x2; first[2].textCoord.y = frames[frame].y1;
	first[3].textCoord.x = frames[frame].x2; first[3].textCoord.y = frames[frame].y2;
}

void TAC::getCCWTextureCoordinatesFor(unsigned int frame, Vertex * first) const //_DEBUG std::invalid_argument
{
    #ifdef _DEBUG
    if (frame >= frames.size())
    {
        throw std::invalid_argument ("TextureAtlasClass::getTextureCoordinatesFor(): frame size too large");
    }
    if (!first)
    {
        throw std::invalid_argument ("TextureAtlasClass::getTextureCoordinatesFor(): null pointer argument");
    }
    #else
    if (frame >= frames.size())
    {
        return;
    }
    #endif

	first[0].textCoord.x = frames[frame].x1; first[0].textCoord.y = frames[frame].y1;	
	first[1].textCoord.x = frames[frame].x1; first[1].textCoord.y = frames[frame].y2;	
	first[2].textCoord.x = frames[frame].x2; first[2].textCoord.y = frames[frame].y2;
	first[3].textCoord.x = frames[frame].x2; first[3].textCoord.y = frames[frame].y1;
}

void TAC::getClippedTextureCoordinatesFor 
    (const unsigned int frame, Vertex * first, const float left,
     const float bottom, const float right, const float top) const  //_DEBUG std::invalid_argument
{
    #ifdef _DEBUG
    if (frame >= frames.size())
    {
        throw std::invalid_argument ("TextureAtlasClass::getClippedTextureCoordinatesFor(): frame size too large");
    }
    if (!first)
    {
        throw std::invalid_argument ("TextureAtlasClass::getClippedTextureCoordinatesFor(): null pointer argument");
    }
    #else
    if (frame >= frames.size())
    {
        return;
    }
    #endif
    
    const float full_w = frames[frame].x2 - frames[frame].x1;
    const float full_h = frames[frame].y2 - frames[frame].y1;
    const float full_x = 0.5f*(full_w) + frames[frame].x1;
    const float full_y = 0.5f*(full_h) + frames[frame].y1;
    
    const float x1 = full_x + full_w*left;
    const float y1 = full_y + full_h*bottom;
    const float x2 = full_x + full_w*right;
    const float y2 = full_y + full_h*top;

	first[0].textCoord.x = x1; first[0].textCoord.y = y1;	
	first[1].textCoord.x = x1; first[1].textCoord.y = y2;	
	first[2].textCoord.x = x2; first[2].textCoord.y = y1;
	first[3].textCoord.x = x2; first[3].textCoord.y = y2;
}

void TAC::getCCWClippedTextureCoordinatesFor 
    (const unsigned int frame, Vertex * first, const float left,
     const float bottom, const float right, const float top) const  //_DEBUG std::invalid_argument
{
    #ifdef _DEBUG
    if (frame >= frames.size())
    {
        throw std::invalid_argument ("TextureAtlasClass::getClippedTextureCoordinatesFor(): frame size too large");
    }
    if (!first)
    {
        throw std::invalid_argument ("TextureAtlasClass::getClippedTextureCoordinatesFor(): null pointer argument");
    }
    #else
    if (frame >= frames.size())
    {
        return;
    }
    #endif
    
    const float full_w = frames[frame].x2 - frames[frame].x1;
    const float full_h = frames[frame].y2 - frames[frame].y1;
    const float full_x = 0.5f*(full_w) + frames[frame].x1;
    const float full_y = 0.5f*(full_h) + frames[frame].y1;
    
    const float x1 = full_x + full_w*left;
    const float y1 = full_y + full_h*bottom;
    const float x2 = full_x + full_w*right;
    const float y2 = full_y + full_h*top;

	first[0].textCoord.x = x1; first[0].textCoord.y = y1;	
	first[1].textCoord.x = x1; first[1].textCoord.y = y2;	
	first[2].textCoord.x = x2; first[2].textCoord.y = y2;
	first[3].textCoord.x = x2; first[3].textCoord.y = y1;
}
  
  
  
    
}		//	visen
}		//	aab

