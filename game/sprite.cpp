
/**
*
*	sprite.cpp"
*
**/

#include"sprite.hpp"
//#include"../time/time_reporter.hpp"
#include"../visen/animated_texture.hpp"
#include<stdexcept>
namespace aab	{
namespace game	{
using aab::visen::makeAnimatedTexture;
using aab::visen::makeTexture;
using aab::visen::TextureBasePtr;
using aab::visen::TexturePtr;
using aab::visen::AnimatedTexturePtr;
//using aab::time::FrameTicker;



Sprite::Sprite (TextureBasePtr textureBase)
{
    useColor = false;
	texture = textureBase;
}


Sprite::Sprite (TexturePtr texture, //FrameTicker::Ptr ticker,
                int frameWidth, int frameHeight)
	//std::invalid_argument
{
	visen::AnimatedTexturePtr animation = makeAnimatedTexture (texture, //ticker,
                                                         frameWidth, frameHeight);
	//frames = animation->getMaximumFrame();
	this-> texture = animation;
	useColor = false;
}

Sprite::~Sprite()// throw ()
{
	// nothing to do here //
}


void Sprite::draw ()
{
	before ();
	after ();
}

void Sprite::render ()
{
    if (useColor)
    {
        color.apply();
        texture-> render ();
        aab::visen::Colorf::white.apply();
    }
    else
    {
        texture-> render ();
    }
}



void Sprite::before ()
{
	TransformationNode::before ();
	this-> render ();
}


void Sprite::after ()
{
	TransformationNode::after ();
}


TextureBasePtr Sprite::getTextureBase ()
{
	return texture;
}

/*
time::FrameTicker::Ptr Sprite::getFrameTickerPtr()
{
	return texture->getFrameTickerPtr();
}

void Sprite::updateAnimation()
{
	if (texture->hasFrameTickerPtr())
		texture->getFrameTickerPtr()->update();
}

int Sprite::getCurrentSubAnimatorIndex () const
{
	return currentSubAnimator;
}

void Sprite::setSubAnimator(int index);// throw (std::exception&)
{
	if (index == currentSubAnimator)
		return;

	if (index < 0 || index >= subAnimators.size())
		throw std::invalid_argument ("aab::game::Sprite::setSubAnimator: invalid index for a subAnimator");

	currentSubAnimator = index;
	subAnimators[index].applyTo (getFrameTickerPtr());
}

void Sprite::addSubAnimator(const time::SubAnimator subAnimator);// throw (std::exception&)
{
	if (subAnimator.getMax() >= frames)
		throw std::invalid_argument ("aab::game::Sprite::addSubAnimator: subAnimator's maximum frame is too large for this Sprite");

	subAnimators.push_back (subAnimator);
}

std::vector<time::SubAnimator> & Sprite::accessSubAnimators ()
{
	return subAnimators;
}*/

void Sprite::setFrame(int frame)
{
    texture->setFrame(frame);
}

int Sprite::getFrame()const
{
    return texture->getFrame();
}
int Sprite::getMaximumFrame()const
{
    return texture->getMaximumFrame();
}
bool Sprite::isAnimatable()const
{
    return texture->isAnimatable();
}

}		//	game
}		//	aab






