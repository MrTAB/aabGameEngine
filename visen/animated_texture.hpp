/**
*
*	animated_texture.hpp
**/

#if !defined(AAB_VISEN_ANIMATED_TEXTURE_CLASS)
#define AAB_VISEN_ANIMATED_TEXTURE_CLASS
//#include"texture.hpp"
//#include"texture_base.hpp"
//#include"../types/manager.hpp"
//#include"../types/smart_ptr.hpp"
#include"framed_texture.hpp"
namespace aab	{
namespace visen	{


class AnimatedTextureClass : public FramedTextureClass//: public TextureBaseClass
{
	public:

	typedef aab::types::Smart <AnimatedTextureClass>::Ptr Ptr;

	protected:

		//static FrameTicker::Ptr stillTicker;

		//FrameTicker::Ptr ticker;
		///TexturePtr texture;

		float wfrac;
		float hfrac;
		float drawWidth;
		float drawHeight;
		int horizontalFrames;
		int maxFrame;
		///int currentFrame;
		
		void updateTextureCoordinates();

	protected:

		//friend Ptr makeAnimatedTexture (Texture, FrameTicker::Ptr,
					//int frameWidth, int frameHeight) throw (std::exception &);
		friend Ptr makeAnimatedTexture (TexturePtr,
					int frameWidth, int frameHeight) ;//std::invalid_argument
		explicit AnimatedTextureClass (TexturePtr,// FrameTicker::Ptr,
					int frameWidth, int frameHeight) ;//std::invalid_argument
		virtual ~AnimatedTextureClass ();// throw ();


	public:


	//FrameTicker::Ptr getFrameTickerPtr () throw (std::exception &);
	///TexturePtr getTexture ();

	virtual int getMaximumFrame () const;

    virtual bool isValidFrame (unsigned int frame) const;
    
	//void updateTicker ();
	///void bind()throw();
	///void render ();
	virtual void renderNobind();
	//void renderHFlipped(){renderFrameHFlipped(currentFrame);};
	//void renderVFlipped(){renderFrameVFlipped(currentFrame);};
	//void renderFrame (int frame);
	//void renderFrameHFlipped (int frame);
	//void renderFrameVFlipped (int frame);
	//void renderUnboundFrame (int frame);
	virtual float getFrameX(int frame) const;
	virtual float getFrameY(int frame) const;
	float getTextureCoordinateWidth() const { return wfrac; }
	float getTextureCoordinateHeight() const { return hfrac; }
	int getEnvelopeWidth() const { return drawWidth; }
	int getEnvelopeHeight() const { return drawHeight; }
	
	virtual int getFrameWidth (const unsigned int ignore = 0)const { return getEnvelopeWidth(); }
    virtual int getFrameHeight (const unsigned int ignore = 0)const { return getEnvelopeHeight(); }
    
    virtual void getCCWTextureCoordinatesFor(unsigned int frame, Vertex * first)const;
    virtual void getStripTextureCoordinatesFor(unsigned int frame, Vertex * first)const;
    virtual void getClippedTextureCoordinatesFor(const unsigned int frame, Vertex * first,
                    const float left_ratio, const float bottom_ratio, const float right_ratio, const float top_ratio) const;
    virtual void getCCWClippedTextureCoordinatesFor(const unsigned int frame, Vertex * first,
                    const float left_ratio, const float bottom_ratio, const float right_ratio, const float top_ratio) const; 
                    
	//bool hasFrameTickerPtr () const; // returns true always for this subclass

	BlendMethod & accessBlendMethod () { return texture->accessBlendMethod(); }
	//void updateBlendMethod() { texture->updateBlendMethod(); }
	
	virtual bool isAnimatable () const { return true; }
	virtual void setFrame(int frame);  //_DEBUG std::invalid_argument
	///int getFrame()const { return currentFrame; }
    
};

typedef AnimatedTextureClass::Ptr AnimatedTexturePtr;

//AnimatedTexturePtr makeAnimatedTexture (TexturePtr, aab::time::FrameTicker::Ptr,
//		int frameWidth, int frameHeight) throw (std::exception &);

AnimatedTexturePtr makeAnimatedTexture (TexturePtr,
		int frameWidth, int frameHeight);//std::invalid_argument

}		//	visen
}		//	aab
#endif //AAB_VISEN_ANIMATED_TEXTURE_CLASS
