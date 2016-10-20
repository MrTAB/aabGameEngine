
/**
*
*	color.cpp
*
**/

#include"color.hpp"
#include<sdl.H>
#include"_include_opengl.hpp"
#include<algorithm>
#include<cmath>
namespace aab	{
namespace visen	{

/*
Colorub Colorub::black	(0, 0, 0, 255);
Colorub Colorub::white	(255, 255, 255, 255);
Colorub Colorub::gray	(128, 128, 128, 255);
Colorub Colorub::red	(255, 0, 0, 255);
Colorub Colorub::green	(0, 255, 0, 255);
Colorub Colorub::blue	(0, 0, 255, 255);
Colorub Colorub::yellow	(255, 255, 0, 255);
Colorub Colorub::magenta(255, 0, 255, 255);
Colorub Colorub::cyan	(0, 255, 255, 255);
*/


//todo - add methods to alter hue, to set from HSV, to alter brightness etc

Colorub Colorub::black	= {0, 0, 0, 255};
Colorub Colorub::white	= {255, 255, 255, 255};
Colorub Colorub::gray	= {128, 128, 128, 255};
Colorub Colorub::red	= {255, 0, 0, 255};
Colorub Colorub::green	= {0, 255, 0, 255};
Colorub Colorub::blue	= {0, 0, 255, 255};
Colorub Colorub::yellow	= {255, 255, 0, 255};
Colorub Colorub::magenta= {255, 0, 255, 255};
Colorub Colorub::cyan	= {0, 255, 255, 255};


Colorf Colorf::black	(0, 0, 0);
Colorf Colorf::white	(255, 255, 255);
Colorf Colorf::gray	(128, 128, 128);
Colorf Colorf::red	(255, 0, 0);
Colorf Colorf::green	(0, 255, 0);
Colorf Colorf::blue	(0, 0, 255);
Colorf Colorf::yellow	(255, 255, 0);
Colorf Colorf::magenta(255, 0, 255);
Colorf Colorf::cyan	(0, 255, 255);

/*
void Colorub::set (const Colorf f)
{
    colors[0] = f.getRedAsByte();
    colors[1] = f.getGreenAsByte();
    colors[2] = f.getBlueAsByte();
    colors[3] = f.getAlphaAsByte();
}*/

//todo - add conversion to YIQ:
//http://beesbuzz.biz/code/hsv_color_transforms.php
// http://en.wikipedia.org/wiki/YIQ


double Colorub::inverse_gamma(byte_t ic)const
{
    double c = ic/255.0;
    if ( c <= 0.04045 )
        return c/12.92;
    else 
        return std::pow(((c+0.055)/(1.055)),2.4);
}

int Colorub::gamma(double v)const
{
    if(v<=0.0031308)
        v *= 12.92;
    else 
        v = 1.055*std::pow(v,1.0/2.4)-0.055;
    return static_cast<int>(v*255+.5);
}

double Colorub::getLumaHSP()const
{
    return std::sqrt(0.299*colors[0]*colors[0] + 0.587*colors[1]*colors[1] + 0.114*colors[2]*colors[2])/255.0;
}

//todo - make a getPreucilHue() functrion:
//http://en.wikipedia.org/wiki/Hue#Computing_hue_from_RGB

float Colorub::getHue()const // returns a hure between 0.0f-1.0f
{
    //optimize
    
    const float max = std::max(colors[0],std::max(colors[1],colors[2]));
    const float min = std::min(colors[0],std::min(colors[1],colors[2]));
    float hue;
    
    if(max==colors[0])
    {
        hue = (colors[1]-colors[2])/(max-min);
    }
    else if (max==colors[1])
    {
        hue =  2.f + (colors[2]-colors[0])/(max-min);
    }
    else
    {
        hue =  4.f + (colors[0]-colors[1])/(max-min);
    }
    
    hue *= 60;
    if(hue < 0)
    {
        hue += 360;
    }
    
    return hue/360.0f;
}

void Colorub::blend (Colorub other)
{
	for (int t = 0; t < 4; ++t)
	{
	    colors[t] = (colors[t]+other.colors[t])/2;		
	}
}

void Colorub::blend (Colorub other, float weight)
{
	for (int t = 0; t < 4; ++t)
	{
		colors[t] = weight * colors[t] + (1.0f - weight) * other.colors[t];
	}
}

void Colorub::apply ()
{
    //todo - this is going to become depricated.
	glColor4ub (colors[0],colors[1],colors[2],colors[3]);
}

void Colorub::setFromAppliedColor ()
{
	Colorf cf;
	cf.setFromAppliedColor();
	colors[0] = cf.getRedAsByte();
	colors[1] = cf.getGreenAsByte();
	colors[2] = cf.getBlueAsByte();
	colors[3] = cf.getAlphaAsByte();
}





Colorf::Colorf ()
{
	std::fill (colors, colors + 4, 1.0f);
}

Colorf::Colorf (const int r, const int g, const int b, const int a)
{
	set (r, g, b, a);
}

Colorf::Colorf (const float r, const float g, const float b, const float a)
{
	set (r, g, b, a);
}


Colorf::Colorf (const Colorf &other)
{
	this-> operator = (other);
}

Colorf & Colorf::operator = (const Colorf &other)
{
	std::copy (other.colors, other.colors + 4, this-> colors);

	return *this;
}

void Colorf::set (const int r, const int g, const int b, const int a)
{
	colors [0] = static_cast<const float> (r) / 255.0f;
	colors [1] = static_cast<const float> (g) / 255.0f;
	colors [2] = static_cast<const float> (b) / 255.0f;
	colors [3] = static_cast<const float> (a) / 255.0f;
}

void Colorf::set (const float r, const float g, const float b, const float a)
{
	colors [0] = r;
	colors [1] = g;
	colors [2] = b;
	colors [3] = a;
}

void Colorf::setRed (const int r)
{
	colors [0] = static_cast<const float> (r) / 255.0f;
}

void Colorf::setGreen (const int g)
{
	colors [1] = static_cast<const float> (g) / 255.0f;
}

void Colorf::setBlue (const int b)
{
	colors [2] = static_cast<const float> (b) / 255.0f;
}

void Colorf::setAlpha (const int a)
{
	colors [3] = static_cast<const float> (a) / 255.0f;
}

void Colorf::setRed (const float r)
{
	colors [0] = r;
}

void Colorf::setGreen (const float g)
{
	colors [1] = g;
}

void Colorf::setBlue (const float b)
{
	colors [2] = b;
}

void Colorf::setAlpha (const float a)
{
	colors [3] = a;
}

void Colorf::setHexRGB(const unsigned int hex)
{
	setRed(static_cast<int>(hex&0xff0000)>>16);
	setGreen(static_cast<int>(hex&0x00ff00)>>8);
	setBlue(static_cast<int>(hex&0x0000ff));
}

float Colorf::getRedAsFloat () const
{
	return colors [0];
}

float Colorf::getGreenAsFloat () const
{
	return colors [1];
}

float Colorf::getBlueAsFloat () const
{
	return colors [2];
}

float Colorf::getAlphaAsFloat () const
{
	return colors [3];
}

Colorf::byte Colorf::getRedAsByte () const
{
	return static_cast<byte> (255 * colors[0]);
}

Colorf::byte Colorf::getGreenAsByte () const
{
	return static_cast<byte> (255 * colors[1]);
}

Colorf::byte Colorf::getBlueAsByte () const
{
	return static_cast<byte> (255 * colors[2]);
}

Colorf::byte Colorf::getAlphaAsByte () const
{
	return static_cast<byte> (255 * colors[3]);
}

Colorf::byte Colorf::getRed () const
{
	return static_cast<byte> (255 * colors[0]);
}

Colorf::byte Colorf::getGreen () const
{
	return static_cast<byte> (255 * colors[1]);
}

Colorf::byte Colorf::getBlue () const
{
	return static_cast<byte> (255 * colors[2]);
}

Colorf::byte Colorf::getAlpha () const
{
	return static_cast<byte> (255 * colors[3]);
}

void Colorf::blend (Colorf other)
{
	for (int t = 0; t < 4; ++t)
	{
		colors[t] += other.colors[t];
		colors[t] *= 0.5f;
	}
}

void Colorf::blend (Colorf other, float weight)
{
	for (int t = 0; t < 4; ++t)
	{
		colors[t] = weight * colors[t] + (1.0f - weight) * other.colors[t];
	}
}

void Colorf::apply ()
{
    //todo - this is going to become depricated.
	glColor4fv (colors);
}

void Colorf::setFromAppliedColor ()
{
	glGetFloatv (GL_CURRENT_COLOR, colors);
}





}	//	visen
}	//	aab


