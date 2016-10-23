
/**
*
*	texture.hpp
*
*   A Texture represents a single texture loaded from an image, which can then
*   be bound or rendered directly onto a quad.
*
*	todo - either bind has to enable gltexture2d, so that lines etc can be drawn
*   or objects which draw lines have to enable gltexture2d when done.
**/

#if !defined(AAB_VISEN_TEXTURE_CLASS)
#define AAB_VISEN_TEXTURE_CLASS
#include"screen.hpp"
#include"image.hpp"
#include"color.hpp"
#include"texture_base.hpp"
#include"../types/byte.hpp"
#include"../types/smart_ptr.hpp"
#include"../types/manager.hpp"
#include<string>
#include<memory>
namespace aab	{
namespace visen	{

/*

	The three constructors correspond to the 3 available transparency options:

	1)	full opacity
	2)	mask the specified Color
	3)	set alpha using the luminosity of each pixel in the specified image loaded from that filename.

*/

namespace texture
{
	unsigned int getMaxTextureUnits();
	
    void setActiveTextureUnit(unsigned int unit);

    void establishTextureUnit(unsigned int unit);
};

class TextureClass : public TextureBaseClass
{
	public:

	typedef aab::types::byte_t byte_t;
	typedef aab::types::Smart <TextureClass>::Ptr Ptr;

	private:

		struct Data;
		const std::auto_ptr <Data> data;

		TextureClass (TextureClass &);

		void fillData (Image);
		bool correctedStoredSizes();
		void correctImageSize (Image);// std::runtime_error, std::invalid_argument
		void createTexture (Image);//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		void createTexture (unsigned int width, unsigned int height, bool useAlpha);
        void createTexture (unsigned int width, unsigned int height, bool useAlpha, aab::visen::Colorub color);

	protected:

		friend Ptr makeTexture (Screen, Image);
			//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		friend Ptr makeTexture (Screen, const std::string &);
			//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
		friend Ptr makeTexture (Screen, const std::string &, byte_t, byte_t, byte_t);
			//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
		friend Ptr makeTexture (Screen, const std::string &, const Colorf);
			//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
		friend Ptr makeTexture (Screen, const std::string &, const std::string &);
			//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
		//friend Ptr makeNullTexture ()
		//	//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		friend Ptr makeTexture (Screen, unsigned int width, unsigned int height, bool useAlpha);
		friend Ptr makeTexture (Screen, unsigned int width, unsigned int height, bool useAlpha, aab::visen::Colorub color);

		explicit TextureClass (Screen, Image);
			//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		explicit TextureClass (Screen, const std::string &filename);
			//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
		explicit TextureClass (Screen, const std::string &filename, byte_t red, byte_t green, byte_t blue);
			//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
		explicit TextureClass (Screen, const std::string &filename, const std::string &maskFilename);
			//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error, aab::test::file_not_found_error
		explicit TextureClass (Screen, unsigned int width, unsigned int height, bool useAlpha);
		explicit TextureClass (Screen, unsigned int width, unsigned int height, bool useAlpha, aab::visen::Colorub color);
		virtual ~TextureClass ();// throw ();

	public:

	void bind (); //throw (); 

	virtual int getImageWidth () const;
	virtual int getImageHeight () const;

	int getOutputWidth () const;
	int getOutputHeight () const;
	
	
	
	virtual inline int getFrameWidth (const unsigned int ignore = 0)const { return getOutputWidth(); }
    virtual inline int getFrameHeight (const unsigned int ignore = 0)const { return getOutputWidth(); }
    
	virtual int getClearBorderX()const;
	virtual int getClearBorderY()const;


	//bool hasFrameTickerPtr () const; // always returns false for this subclass
	//FrameTicker::Ptr getFrameTickerPtr ();// throw (std::exception &); // always throws for this subclass
	void render ();
	void renderNobind ();

	virtual bool isAnimatable() const { return false; }
	virtual void setFrame(int)  {/* do nothing */ }
	virtual int getFrame()const { return 0; }
	virtual int getMaximumFrame()const { return 0; }
	
	virtual unsigned int getId()const;
	
};

typedef TextureClass::Ptr TexturePtr;

TexturePtr makeTexture (Screen, Image);
	//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
TexturePtr makeTexture (Screen, const std::string &filename);
	//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
TexturePtr makeTexture (Screen, const std::string &filename,
			TextureClass::byte_t red, TextureClass::byte_t green, TextureClass::byte_t blue);
	//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
TexturePtr makeTexture (Screen, const std::string &filename, const Colorf mask);
	//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
TexturePtr makeTexture (Screen, const std::string &filename, const std::string &maskFilename);
	//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
TexturePtr makeTexture (Screen, unsigned int width, unsigned int height, bool useAlpha);
TexturePtr makeTexture (Screen, unsigned int width, unsigned int height, bool useAlpha, aab::visen::Colorub color);

//TexturePtr makeNullTexture () throw (std::exception &);


}		//	visen
}		//	aab
#endif	//	AAB_VISEN_TEXTURE_CLASS




