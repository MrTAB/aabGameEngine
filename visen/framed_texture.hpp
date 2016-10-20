/**
*
*	framed_texture.hpp
**/

#if !defined(AAB_VISEN_FRAMED_TEXTURE_CLASS)
#define AAB_VISEN_FRAMED_TEXTURE_CLASS
#include"texture.hpp"
#include"texture_base.hpp"
#include"vertex.hpp"
#include"../types/manager.hpp"
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace visen	{


class FramedTextureClass : public TextureBaseClass
{
	public:

	typedef aab::types::Smart <FramedTextureClass>::Ptr Ptr;

	protected:
	
        TexturePtr texture;
        int currentFrame;
 

	protected:

		//friend Ptr makeAnimatedTexture (Texture, FrameTicker::Ptr,
					//int frameWidth, int frameHeight) throw (std::exception &);
		//friend Ptr makeFramedTexture (TexturePtr) ;//std::invalid_argument
		explicit FramedTextureClass (TexturePtr) ;//std::invalid_argument
		virtual ~FramedTextureClass ();// throw ();


	public:


	//FrameTicker::Ptr getFrameTickerPtr () throw (std::exception &);
	TexturePtr getTexture () { return texture; }
	
	virtual bool isValidFrame (unsigned int frame) const = 0;

	//virtual int getMaximumFrame () const; defined by Texture

	//void updateTicker ();
	void bind()throw();
	void render ();
	virtual void renderNobind() = 0;
	
	//void renderHFlipped(){renderFrameHFlipped(currentFrame);};
	//void renderVFlipped(){renderFrameVFlipped(currentFrame);};
	//void renderFrame (int frame);
	//void renderFrameHFlipped (int frame);
	//void renderFrameVFlipped (int frame);
	//void renderUnboundFrame (int frame);
	
	virtual float getFrameX(int frame) const = 0;
	virtual float getFrameY(int frame) const = 0;	
	
	virtual int getImageWidth () const { return texture->getImageWidth(); }
	virtual int getImageHeight () const { return texture->getImageHeight(); }
	virtual int getFrameWidth (const unsigned int frame = 0)const = 0;
    virtual int getFrameHeight (const unsigned int frame = 0)const = 0;
    virtual int getClearBorderX ()const { return texture->getClearBorderX(); }
    virtual int getClearBorderY ()const { return texture->getClearBorderY(); }
    
    virtual void getStripTextureCoordinatesFor(unsigned int frame, Vertex * first)const = 0;
    virtual void getCCWTextureCoordinatesFor(unsigned int frame, Vertex * first)const = 0;
    virtual void getClippedTextureCoordinatesFor(const unsigned int frame, Vertex * first,
                    const float left_ratio, const float bottom_ratio, const float right_ratio, const float top_ratio) const = 0;
    virtual void getCCWClippedTextureCoordinatesFor(const unsigned int frame, Vertex * first,
                    const float left_ratio, const float bottom_ratio, const float right_ratio, const float top_ratio) const = 0; 
                    
	//bool hasFrameTickerPtr () const; // returns true always for this subclass

	BlendMethod & accessBlendMethod () { return texture->accessBlendMethod(); }
	//void updateBlendMethod() { texture->updateBlendMethod(); }
	
	virtual bool isAnimatable () const { return true; }
	virtual void setFrame(int frame) = 0;
	int getFrame()const { return currentFrame; }
	
	virtual unsigned int getId()const
	{
	    return texture->getId();
	}
};

typedef FramedTextureClass::Ptr FramedTexturePtr;

//AnimatedTexturePtr makeAnimatedTexture (TexturePtr, aab::time::FrameTicker::Ptr,
//		int frameWidth, int frameHeight) throw (std::exception &);

//FramedTexturePtr makeFramedTextureClass (TexturePtr);//std::invalid_argument

}		//	visen
}		//	aab
#endif //AAB_VISEN_ANIMATED_TEXTURE_CLASS
