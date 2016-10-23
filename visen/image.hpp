
/**
*
*   image.hpp
*
*   Represents an image either loaded from file or constructed in memory.
*   Textures can be created from images, which can be modified using Pixel
*   Operations before being used for Texture generation.
*
*
**/

#if !defined(AAB_VISEN_IMAGE_CLASS)
#define AAB_VISEN_IMAGE_CLASS
#include"screen.hpp"
#include"color.hpp"
#include"../types/byte.hpp"
#include"../types/smart_ptr.hpp"
#include"../types/manager.hpp"
#include<string>
#include<memory>
#include<cstdint>
namespace aab	{
namespace visen	{


struct Pixel
{
    uint8_t red, green, blue, alpha;
    
    bool operator == (const Pixel p)
    {
        return red == p.red && green == p.green && blue == p.blue;
    }
    bool operator != (const Pixel p)
    {
        return red != p.red || green != p.green || blue != p.blue;
    }
};

struct PixelReadOperation
{   typedef aab::visen::Pixel Pixel;
    virtual void operator()(const Pixel *)
    {
        // do nothing //
    }
};

struct PixelWriteOperation
{    typedef aab::visen::Pixel Pixel;
    virtual void operator()(Pixel *)
    {
        // do nothing //
    }
};

struct PixelReadXYOperation
{   typedef aab::visen::Pixel Pixel;
    virtual void operator()(const Pixel *, const int x, const int y)
    {
        //x;y;
        // do nothing //
    }
};


struct PixelWriteXYOperation
{    typedef aab::visen::Pixel Pixel;
    virtual void operator()(Pixel*, const int x, const int y)
    {
        //x;y;
        // do nothing //
    }
};

/*

	Image loaded is converted into a 32bpp image.

	The three constructors correspond to the 3 available transparency options:

	1)	full opacity
	2)	mask the specified Color
	3)	set alpha using the value of the first byte of each pixel in the specified image
		loaded from that filename. Behaviour is undefined if the two images are not the
		same dimension. The mask image can be a different byte per pixel though, however
		must have 8 bit sample sizes.


	expandClearEdgesTo () redimensions the image such that any pixels not originaly
	in the image are clear (given 0 alpha).

	Constructors may throw std::exceptions.
	expandClearEdgesTo may throw a std::exception.
*/


class ImageClass : public aab::types::Manager <ImageClass>
{
	public:

	typedef aab::types::byte_t byte_t;
	typedef aab::types::Smart <ImageClass>::Ptr Ptr;

	private:

		struct Data;
		const std::auto_ptr <Data> data;

		ImageClass (ImageClass &);

		void convertTo24bpp () ;// std::runtime_error
		void convertTo32bpp ();// std::runtime_error
		bool isTextureShaped () const;
		
		void assert_file_path(std::string filename) const;

	protected:

		friend class aab::types::Manager <ImageClass>::Deleter;

		friend Ptr makeImage (const Screen, const std::string &filename) ;//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
		friend Ptr makeImage (const Screen, const std::string &filename, byte_t red,
									byte_t green, byte_t blue) ;//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
		friend Ptr makeImage (const Screen, const std::string &filename, const Colorf mask);
									//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
		friend Ptr makeImage (const Screen, const std::string &filename,
									const std::string &maskFilename);//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
        friend Ptr makeImage (const Screen screen, const int width, const int height, const bool useAlpha);
        
		explicit ImageClass (const Screen, const std::string &filename);//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
		explicit ImageClass (const Screen, const std::string &filename, byte_t red,
									byte_t green, byte_t blue);//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
		explicit ImageClass (const Screen, const std::string &filename,
									const std::string &maskFilename);//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
        explicit ImageClass (const Screen screen, const int width, const int height, const bool alpha);
		virtual ~ImageClass ();// throw ();

	public:

	int getWidth () const;
	int getHeight () const;
	int getBitsPerPixel () const;

    enum ExpandDirection
    {
        EXPAND_CENTRE,
        EXPAND_TOP_LEFT,
        EXPAND_TOP_RIGHT,
        EXPAND_BOTTOM_LEFT,
        EXPAND_BOTTOM_RIGHT    
    };

	void expandClearEdgesTo (int newWidth, int newHeight, ExpandDirection expand = EXPAND_CENTRE);//std::runtime_error, std::invalid_argument
	
	
	// these traverse the pixels top to right and down, like a book
	void readPixels (PixelReadOperation&operation);
	void readPixels (PixelReadXYOperation&operation);
	void transformPixels (PixelWriteOperation&operation);
	void transformPixels (PixelWriteXYOperation&operation);
	
	
	// In addition to the transformation methods above, you can traverse pixels using these methods.
	// Lock must be called before calling these methods, followed by unlock after these methdos have been done.
	// The "ImageLocker" can be used to lock and auto-unlock
	
	void lockPixels();
	
	Pixel readPixel (const int x, const int y)const;
	Pixel * accessPixel (const int x, const int y); // no check is made
	
	const void *accessPixels () const;
	
	void unlockPixels();
	
	bool saveBmp(const std::string &filename)const;
	//bool savePng(const std::string &filename)const;
	
    bool copyInto(ImageClass&other, const int x, const int y);
    bool copyCroppedInto(const int left, const int top, const int right, const int bottom, ImageClass&other, const int x, const int y);

    void fill(aab::visen::Colorub color);
    void fill(aab::visen::Colorub color, const int left, const int top, const int right, const int bottom);
    
    void setClipRect(const int left, const int top, const int right, const int bottom);
    void removeClipRect();

};


typedef ImageClass::Ptr Image;

Image makeImage (const Screen, const std::string &filename);//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
Image makeImage (const Screen, const std::string &filename, ImageClass::byte_t red,
							ImageClass::byte_t green, ImageClass::byte_t blue);//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
Image makeImage (const Screen, const std::string &filename, const Colorf mask);
							//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
Image makeImage (const Screen, const std::string &filename,
							const std::string &maskFilename) ;//	std::runtime_error, std::invalid_argument, aab::test::file_not_found_error
Image makeImage (const Screen screen, const int width, const int height, const bool useAlpha=true);

struct ImageLocker
{
    Image image;
    
    explicit ImageLocker(Image imageIn):image(imageIn)
    {
        image->lockPixels();
    }
    
    ~ImageLocker()
    {
        image->unlockPixels();
    }
};




}		//	visen
}		//	aab
#endif	//	AAB_VISEN_IMAGE_CLASS




