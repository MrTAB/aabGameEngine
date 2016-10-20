/**
*
*	texture_base.cpp
*
**/

#include"texture_base.hpp"
#include"render_state.hpp"
namespace aab	{
namespace visen	{

TextureBaseClass::TextureBaseClass ()
{
    texCoord[0].set(0,0);
    texCoord[1].set(0,1);
    texCoord[2].set(1,1);
    texCoord[3].set(1,0);
    texCoordPos[0] = 0;
    texCoordPos[1] = 1;
    texCoordPos[2] = 2;
    texCoordPos[3] = 3;
};



void TextureBaseClass::setTextureCoordinates(const TextureCoordinateQuad quad)
{
    texCoord[0] = quad.coordinate[0];
    texCoord[1] = quad.coordinate[1];
    texCoord[2] = quad.coordinate[2];
    texCoord[3] = quad.coordinate[3];
}

void TextureBaseClass::getTextureCoordinates(TextureCoordinateQuad & quad)const
{
    quad.coordinate[0] = texCoord[0];
    quad.coordinate[1] = texCoord[1];
    quad.coordinate[2] = texCoord[2];
    quad.coordinate[3] = texCoord[3];
}

void TextureBaseClass::hFlip()
{
    std::swap(texCoord[0],texCoord[3]);
    std::swap(texCoord[1],texCoord[2]);
    std::swap(texCoordPos[0],texCoordPos[3]);
    std::swap(texCoordPos[1],texCoordPos[2]);
}
void TextureBaseClass::vFlip()
{
    std::swap(texCoord[0],texCoord[1]);
    std::swap(texCoord[2],texCoord[3]);
    std::swap(texCoordPos[0],texCoordPos[1]);
    std::swap(texCoordPos[2],texCoordPos[3]);
}



void TextureBaseClass::turnAnticlockwise()
{
    TextureCoordinate first = texCoord[0];
    texCoord[0] = texCoord[1];
    texCoord[1] = texCoord[2];
    texCoord[2] = texCoord[3];
    texCoord[3] = first;
    char firstc = texCoordPos[0];
    texCoordPos[0] = texCoordPos[1];
    texCoordPos[1] = texCoordPos[2];
    texCoordPos[2] = texCoordPos[3];
    texCoordPos[3] = firstc;
}

void TextureBaseClass::turnClockwise()
{
    TextureCoordinate last = texCoord[3];
    texCoord[3] = texCoord[2];
    texCoord[2] = texCoord[1];
    texCoord[1] = texCoord[0];
    texCoord[0] = last;
    char lastc = texCoordPos[3];
    texCoordPos[3] = texCoordPos[2];
    texCoordPos[2] = texCoordPos[1];
    texCoordPos[1] = texCoordPos[0];
    texCoordPos[0] = lastc;
}

void TextureBaseClass::resetTextureCoordinates()
{
    TextureCoordinate texCoordCopy[8] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::copy(texCoord,texCoord+4,texCoordCopy);
    for (int t = 0; t < 4; ++t)
    {
        texCoord[static_cast<int>(texCoordPos[t])] = texCoordCopy[t];
    }
}

/*
void TextureBaseClass::updateBlendMethod()
{
    RenderState::applyBlendMethod (blendMethod);
}*/


/*


todo - 

add:

void setTextureUnit(int);
void enableTextureUnit();
static int getMaxTextureUnits();

*/

}		//	visen
}		//	aab

