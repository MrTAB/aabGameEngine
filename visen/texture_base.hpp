/**
*
*	texture_base.hpp
*
*	Defines a base class for textures of different properties, e.g. animated, non-animated.
*   This can be used in various contexts where different kinds of textures are
*   allowed.
*
    Developer notes:

    todo: consider option of using this for textures:
 	http://www.gamedev.net/page/resources/_/technical/opengl/rendering-efficient-2d-sprites-in-opengl-using-r2429
	Use GL_NV_texture_rectangle or GL_EXT_texture_rectangle if they are available.
		(there is also ARB_non_power_of_two, however this is not commonly available - the above are a step towards it with limitations)
		This extension means you do not have to convert the file or have it power of two in size.
		You also texture coordinate describe it in terms of it's actual size, which means texture coordinates work in terms of pixels.
	This requires:
		extensions to be loaded at initialisation.
		GL_TEXTURE_RECTANGLE_NV  or GL_TEXTURE_RECTANGLE_EXT to be used instead of GL_TEXTURE_2D at the appropriate locations
			This includes enabling it before generating, binding, parameterising, and writing the textures from RAM to video memory.
		When plotting texture coordinates, you describe the actual width and height of the image.
*
**/

#if !defined(AAB_VISEN_TEXTURE_BASE_CLASS)
#define AAB_VISEN_TEXTURE_BASE_CLASS
//#include"../time/frame_ticker.hpp"
#include"../types/manager.hpp"
#include"../types/smart_ptr.hpp"
#include"blend_method.hpp"
#include<algorithm>
namespace aab	{
namespace visen	{
    
struct TextureCoordinate
{
    float x, y;
    
    void set(const float xIn, const float yIn)
    {
        x = xIn; y = yIn;
    }
};

struct TextureCoordinateQuad
{
    TextureCoordinate coordinate[4];
};


// abstract //
class TextureBaseClass : public aab::types::Manager <TextureBaseClass>
{
	public:

	typedef aab::types::Smart <TextureBaseClass>::Ptr Ptr;
	//typedef aab::time::FrameTicker FrameTicker;

	protected:

		friend class aab::types::Manager<TextureBaseClass>::Deleter;
		explicit TextureBaseClass ();

		virtual ~TextureBaseClass () //throw ()
		{
			// nothing //
		}

		BlendMethod blendMethod;
		
		TextureCoordinate texCoord[4];
		char texCoordPos[4]; // remmembers the relative position of the texture coordinates

	public:

	//virtual bool hasFrameTickerPtr () const = 0;
	//virtual FrameTicker::Ptr getFrameTickerPtr () throw (std::exception &) = 0; // throws if hasFrameTickerPtr is false.
	virtual bool isAnimatable() const = 0;
	virtual void setFrame(int)  = 0;
	virtual int getFrame()const = 0;
	virtual int getMaximumFrame()const = 0;
	
    virtual void bind () = 0;//throw () = 0;
	virtual void render () = 0;
    virtual void renderNobind () = 0; //renders without binding.    

	virtual BlendMethod & accessBlendMethod () { return blendMethod; }
	//virtual void updateBlendMethod();  
	
	//  Calling getFrameWidth() and getFrameHeight() is okay for non animated textures: simply returns the output width (full size, inc clear border)
	virtual int getFrameWidth (const unsigned int frame = 0)const = 0;
    virtual int getFrameHeight (const unsigned int frame = 0)const = 0;
	virtual int getImageWidth ()const = 0;
	virtual int getImageHeight ()const = 0;
	virtual int getClearBorderX()const = 0; //will be zero if original image had compatible power of two size. Useful if running a viewport into the texture
	virtual int getClearBorderY()const = 0; // will be zero if original image had compatible power of two size.
	
    void setTextureCoordinates(const TextureCoordinateQuad quad);
    void getTextureCoordinates(TextureCoordinateQuad & quad)const;
    void hFlip();
    void vFlip();
    void turnAnticlockwise();
    void turnClockwise();
    
    // this only works based upon internal changes to the relative shape of the texture coordinate quad
    // calling setTextureCoordinates will invalidate this.
    void resetTextureCoordinates();
    
    virtual unsigned int getId()const = 0;
  

};

typedef TextureBaseClass::Ptr TextureBasePtr;


}		//	visen
}		//	aab
#endif //AAB_VISEN_TEXTURE_BASE_CLASS
