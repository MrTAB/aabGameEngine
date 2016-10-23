
/**
*
*	color.hpp
*
*   Below are two implementations of a single Color; one as unsigned byte, Colorub,
    and the other as floating point, Colourf
*
**/

#if !defined(AAB_VISEN_COLOR_CLASS)
#define AAB_VISEN_COLOR_CLASS
#include"../types/byte.hpp"
namespace aab	{
namespace visen	{

struct Colorf;

struct Colorub
{
    typedef aab::types::byte_t byte_t;
    
    private:
        byte_t colors[4];
       

        double inverse_gamma(byte_t ic)const;
        int gamma(double v)const;
        
    public:

    
    Colorub()
    {
        colors[0] = colors[1] = colors[2] = colors[3] = 255;
    }

    Colorub (byte_t r, byte_t g, byte_t b) 
    {
        colors[0] = r; colors[1] = g;
         colors[2] = b; colors[3] = 255;
    }
    
     // Use initialiser instead.
    Colorub (byte_t r, byte_t g, byte_t b, byte_t a) 
    {
        colors[0] = r; colors[1] = g;
         colors[2] = b; colors[3] = a;
    }
    
    // copy construction, comparison etc assumed.
    
    // access operators
    
    inline
    byte_t & operator[](const unsigned int index)
    {
        return colors[index];
    }
    inline
    byte_t operator[](const unsigned int index)const
    {
        return colors[index];
    }
    
    
    // setting methods
    inline
    void set(const byte_t r,const byte_t g,const byte_t b,const byte_t a = 255)
    {
        colors[0] = r; colors[1] = g;
        colors[2] = b; colors[3] = a;
    }
    inline void setRed(const byte_t sample) { colors[0] = sample; }
    inline void setGreen(const byte_t sample) { colors[1] = sample; }
    inline void setBlue(const byte_t sample) { colors[2] = sample; }
    inline void setAlpha(const byte_t sample) { colors[3] = sample; }
    inline
    void setRGB(const Colorub other)
    {
        colors[0] = other.colors[0];
        colors[1] = other.colors[1];
        colors[2] = other.colors[2];
    }
    
    
    inline
    void setHexRGB(const uint32_t hex)
    {
        colors[0] = static_cast<byte_t>(hex&0xff0000)>>16;
        colors[1] = static_cast<byte_t>(hex&0x00ff00)>>8;
        colors[2] = static_cast<byte_t>(hex&0x0000ff);
    }
    //void set (const Colorf);
    
    // get methods - get as float and get as byte methods not implemented for now
    
    inline byte_t getRed () const { return colors[0]; }
    inline byte_t getGreen () const { return colors[1]; }
    inline byte_t getBlue () const { return colors[2]; }
    inline byte_t getAlpha () const { return colors[3]; }
    
    inline float getRedf () const { return static_cast<float>(colors[0])/255.f; }
    inline float getGreenf () const { return static_cast<float>(colors[1])/255.f; }
    inline float getBluef () const { return static_cast<float>(colors[2])/255.f; }
    inline float getAlphaf () const { return static_cast<float>(colors[3])/255.f; }
    
	void blend (Colorub other); // weight = 0.5f
	void blend (Colorub other, float weight);
    
    	
    Colorub & scaled(const float scale, const float alphaScale = 1.0f)
    {
        if (scale < 0)
        {
            *this = black;
        }
        else
        {
            unsigned int r = colors[0] * scale;
            unsigned int g = colors[1] * scale;
            unsigned int b = colors[2] * scale;
            unsigned int a = colors[3] * alphaScale;
            colors[0] = (r > 255? 255: r);
            colors[1] = (g > 255? 255: g);
            colors[2] = (b > 255? 255: b);
            colors[3] = (a > 255? 255: a);
        }
        return *this;
    }
    
    void apply ();
    void setFromAppliedColor ();
    
	static Colorub black;
	static Colorub white;
	static Colorub gray;
	static Colorub red;
	static Colorub green;
	static Colorub blue;
	static Colorub yellow;
	static Colorub magenta;
	static Colorub cyan;
	
	bool operator == (const Colorub & other)const
	{
	    return *(uint32_t*)((void*)colors) == *(uint32_t*)((void*)other.colors);
	}
	
	bool operator != (const Colorub & other)const
	{
	    return *(uint32_t*)((void*)colors) != *(uint32_t*)((void*)other.colors);
	}
    
    byte_t * data()
    {
        return colors;
    }
    
    const byte_t * data() const
    {
        return colors;
    }
    
    byte_t * begin()
    {
        return colors;
    }
    
    byte_t const* begin()const
    {
        return colors;
    }
    
    byte_t * end()
    {
        return colors+4;
    }
    
    byte_t const* end()const
    {
        return colors+4;
    }
    
    byte_t getBrightness()const
    {
        return gamma(0.212655*inverse_gamma(colors[0])+
                     0.715158*inverse_gamma(colors[1])+
                     0.072187*inverse_gamma(colors[2]));
    };
    
    double getPhotometricLuma()const
    {
        return (0.2126*colors[0] + 0.7152*colors[1] + 0.0722*colors[2])/255.0;
    }
    
    double getCCIR601Luma()const
    {
        return (0.299*colors[0] + 0.587*colors[1] + 0.114*colors[2])/255.0;
    }
    
    double getLumaHSP()const;
    
    float fastLumaA()const
    {
        return (colors[0]+colors[0]+colors[1]+colors[2]+colors[2]+colors[2])/6.f/255.f;
    }
    
    float fastLumaB()const
    {
        return ((colors[0]+colors[0]+colors[0]+colors[1]+colors[2]+colors[2]+colors[2]+colors[2])>>3)/255.f;
    }
    
    float getHue()const; // returns a hure between 0.0f-1.0f
};

/*typedef aab::types::byte_t Colorub[4];*/


struct Colorf
{
	private:

		float colors[4];

	public:

	typedef aab::types::byte_t byte;


	explicit Colorf ();

	Colorf (const Colorf &);
	Colorf (const int r, const int g, const int b, const int a = 255);
	Colorf (const float r, const float g, const float b, const float a = 1.0f);
	Colorf& operator = (const Colorf &other);

	void set (const int r, const int g, const int b, const int a = 255);
	void set (const float r, const float g, const float b, const float a = 1.0f);
	void setRed (const int);
	void setGreen (const int);
	void setBlue (const int);
	void setAlpha (const int);
	void setRed (const float);
	void setGreen (const float);
	void setBlue (const float);
	void setAlpha (const float);
	void setHexRGB(const unsigned int hex);

	float getRedAsFloat () const;
	float getGreenAsFloat () const;
	float getBlueAsFloat () const;
	float getAlphaAsFloat () const;

	byte getRedAsByte () const;
	byte getGreenAsByte () const;
	byte getBlueAsByte () const;
	byte getAlphaAsByte () const;

	byte getRed () const;
	byte getGreen () const;
	byte getBlue () const;
	byte getAlpha () const;

	void blend (Colorf other); // weight = 0.5f
	void blend (Colorf other, float weight);

	void apply ();
	void setFromAppliedColor ();

	static Colorf black;
	static Colorf white;
	static Colorf gray;
	static Colorf red;
	static Colorf green;
	static Colorf blue;
	static Colorf yellow;
	static Colorf magenta;
	static Colorf cyan;
	
    
    float * data()
    {
        return colors;
    }
    
    const float * data() const
    {
        return colors;
    }

};


}		//	visen
}		//	aab
#endif	//	AAB_VISEN_COLOR_CLASS




