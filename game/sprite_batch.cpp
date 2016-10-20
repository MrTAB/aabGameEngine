
/**
*
*	sprite_batch.cpp"
*
**/

#include"sprite_batch.hpp"
//#include"../time/time_reporter.hpp"
//#include"../visen/animated_texture.hpp"
#include"../geometry/vector.hpp"
#include<stdexcept>
#include<algorithm>
#include<sstream>
namespace aab	{
namespace game	{
 
#ifdef _DEBUG
#define THROW_ERROR(EXCEPTION, MSG)         \
            std::stringstream message;      \
            if(id_for_errors)               \
                message<< MSG << ". Error in sprite batch No. " << id_for_errors;   \
            else    \
                message<< MSG << ". Error in un-named sprite batch.";   \
            throw EXCEPTION (message.str());
#endif

SpriteBatch::SpriteBatch (TextureAtlasPtr textureAtlasIn, unsigned int sizeIn):// _DEBUG std::invalid_argument
    textureAtlas (textureAtlasIn),
    id_for_errors(0)
{
    #ifdef _DEBUG
        if (0 == sizeIn) // TODO - implement to handle zero size cases gracefully
        {
            THROW_ERROR(std::invalid_argument, "SpriteBatch::SpriteBatch:: Invalid sprite batch size");
        }
    #else
        sizeIn = 12;
    #endif
    
    SpriteQuad blankQuad = {0,0, 0,0, aab::visen::Colorub::white};
    spriteQuads.assign(sizeIn,blankQuad);
    
    bufferObject = new aab::visen::VertexBufferObject ( &(spriteQuads[0].v00),sizeIn*4);
        //(static_cast<aab::visen::Vertex*>( static_cast<void*>(&(spriteQuads[0]) )),sizeIn*4);
    
    startOfFreeEndBlock = 0; //all currently "end block"
    lastStartOfFreeEndBlock = 0;
    resetMinMaxModified();
}



SpriteBatch::~SpriteBatch()//throw()
{
    delete bufferObject;
}


void SpriteBatch::render()
{
    textureAtlas->bind();
    renderNoBind();
}


void SpriteBatch::renderNoBind()
{
    //TODO - render only the revelant region (VBO needs updating first)
    //bufferObject->render();
    
    if (startOfFreeEndBlock)
        bufferObject->renderRegion(0,6*startOfFreeEndBlock); // 6 indices for every sprite quad
}


void SpriteBatch::renderRegionNoBind(unsigned int start, size_t size)
{
    // vertex offset, index count = 6 for every quad
    bufferObject->renderRegion(4*start, 6*size);
}

//todo - create a batch method for generating n sprites and returning a range of codes.
unsigned int SpriteBatch::generateSprite() //std::logic_error
{
    
    if (freeSpace.empty())
    {
        #ifdef _DEBUG
        //unsigned int _spriteQuadsSize = spriteQuads.size();
        #endif
        
        //before, it was ++ up here and return just start of block
        if (startOfFreeEndBlock == spriteQuads.size())
        {
            #if _DEBUG
                THROW_ERROR(std::logic_error, "SpriteBatch::generateSprite: limit of sprite batch reached: this is a _DEBUG build error and will not occur in release mode - consider resizing the sprite batch to improve runtime performance.");
            #else
                unsigned int increase = spriteQuads.size()/10;
                
                if (increase<10)
                {
                    increase = 10;
                }
                
                resize(spriteQuads.size() + increase);
            #endif
        }
        
        //return (startOfFreeEndBlock++); // very annoying compiler bug: when used in an assingment's right hand expression, the field startOfFreeEndBlock is never updated correctly, only the postfix value is returned.
        const unsigned int spriteCode = startOfFreeEndBlock;
        
        updateMinMaxModified(spriteCode);
        
        //++startOfFreeEndBlock;
        startOfFreeEndBlock = startOfFreeEndBlock + 1;
        
        
        return spriteCode;
        
    }
    else
    {
        // give freeSpace of item at top of set, and remove it from set
        const unsigned int spriteCode = *(freeSpace.cbegin());
        updateMinMaxModified(spriteCode);
        freeSpace.erase(freeSpace.begin());        
        return spriteCode;
    }
}

//todo - make release range of codes method.
void SpriteBatch::releaseSprite(unsigned int code) // throw()
{
    // WARNINING;
    // Do not allow any release to use the diagnostic exception throwing
    
    if (code >= getCapacity())
    {
        #if _DEBUG
            //throw std::logic_error("SpriteBatch::releaseSprite: sprite code out of range");
            return;
        #else
            return;
        #endif
    }

    if (code >= startOfFreeEndBlock)
    {
        #if _DEBUG
            //throw std::logic_error("SpriteBatch::releaseSprite: sprite code already free and in free end block");
            return;
        #else
            return;
        #endif
    }
    
    #if _DEBUG
        if (isInFreeSpace(code))
        {
             //throw std::logic_error("SpriteBatch::releaseSprite: sprite code already free");
             return;
        }
    #endif
    
    spriteQuads[code].makeZero();
    
    updateMinMaxModified(code);
    
    if (code == startOfFreeEndBlock - 1)
    {
        --startOfFreeEndBlock;
        
        // Remove contigious trailing group of freeblocks
        std::set<unsigned int>::iterator freeBlock;
        
        while(startOfFreeEndBlock != 0)
        {
            freeBlock = freeSpace.find(startOfFreeEndBlock-1);
            if (freeBlock != freeSpace.end())
            {
                freeSpace.erase(freeBlock);
                --startOfFreeEndBlock;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        freeSpace.insert(code);
    }
    
}

float SpriteBatch::guessSpriteWidth(unsigned int code)const //_DEBUG std::out_of_range
{
    if (code >= spriteQuads.size())
    {
        _DEBUG_RESPONSE(THROW_ERROR(std::out_of_range,"SpriteBatch::guessSpriteWidth: sprite code outside boundary."));
        _RELEASE_RESPONSE(return 0);
    }
    return spriteQuads[code].guessWidth();
}
float SpriteBatch::guessSpriteHeight(unsigned int code)const //_DEBUG std::out_of_range
{
    if (code >= spriteQuads.size())
    {
        _DEBUG_RESPONSE(THROW_ERROR(std::out_of_range,"SpriteBatch::guessSpriteHeight: sprite code outside boundary."));
        _RELEASE_RESPONSE(return 0);
    }
    return spriteQuads[code].guessHeight();
}
float SpriteBatch::guessSpriteX(unsigned int code)const //_DEBUG std::out_of_range
{
    if (code >= spriteQuads.size())
    {
        _DEBUG_RESPONSE(THROW_ERROR(std::out_of_range,"SpriteBatch::guessSpriteX: sprite code outside boundary."));
        _RELEASE_RESPONSE(return 0);
    }
    return spriteQuads[code].guessX();
}
float SpriteBatch::guessSpriteY(unsigned int code)const //_DEBUG std::out_of_range
{
    if (code >= spriteQuads.size())
    {
        _DEBUG_RESPONSE(THROW_ERROR(std::out_of_range,"SpriteBatch::guessSpriteY: sprite code outside boundary."));
        _RELEASE_RESPONSE(return 0);
    }
    return spriteQuads[code].guessY();
}
float SpriteBatch::guessSpriteAngle(unsigned int code)const //_DEBUG std::out_of_range
{
    if (code >= spriteQuads.size())
    {
        _DEBUG_RESPONSE(THROW_ERROR(std::out_of_range,"SpriteBatch::guessSpriteAngle: sprite code outside boundary."));
        _RELEASE_RESPONSE(return 0);
    }
    return spriteQuads[code].guessAngle();
}
		
SpriteQuad & SpriteBatch::accessSprite(const unsigned int code) //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::accessSprite: sprite code outside boundary.");
        #else
            updateMinMaxModified(0);
            return spriteQuads[0];
        #endif
    }
    #if _DEBUG
        //unsigned int teststartOfFreeEndBlock = startOfFreeEndBlock;
        if (code >= startOfFreeEndBlock )//|| isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::accessSprite: sprite code not been granted access.");
        }
    #endif
    
    updateMinMaxModified(code);
    return spriteQuads[code];
}

const SpriteQuad & SpriteBatch::accessSprite(const unsigned int code) const //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::accessSprite: sprite code outside boundary.");
        #else
            return spriteQuads[0];
        #endif
    }
    #if _DEBUG
        //unsigned int teststartOfFreeEndBlock = startOfFreeEndBlock;
        if (code >= startOfFreeEndBlock )//|| isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::accessSprite: sprite code not been granted access.");
        }
    #endif
    
    return spriteQuads[code];
}

bool SpriteBatch::isSpriteInUse (unsigned int code) const
{
    if (code >=startOfFreeEndBlock)
    {
        return false;
    }
    
    if (isInFreeSpace(code))
    {
        return false;
    }
    
    return true;
}


void SpriteBatch::setSpriteFrame(unsigned int code, unsigned int frame)
{
    textureAtlas->getStripTextureCoordinatesFor(frame,&accessSprite(code).v00);    
}

void SpriteBatch::resizeSprite(unsigned int code, unsigned int oldFrame, unsigned int newFrame) //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::resizeSprite: sprite code outside boundary");
        #else
            return;
        #endif
    }
    #if _DEBUG
        if (code >= startOfFreeEndBlock || isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::resizeSprite: sprite code not been granted access.");
        }
    #endif

    const float oldWidth = textureAtlas->getFrameWidth(oldFrame);
    const float oldHeight = textureAtlas->getFrameHeight(oldFrame);
    const float newWidth = textureAtlas->getFrameWidth(newFrame);
    const float newHeight = textureAtlas->getFrameHeight(newFrame);
    
    spriteQuads[code].scale(newWidth/oldWidth,newHeight/oldHeight);
    updateMinMaxModified(code);
}

void SpriteBatch::setSpriteShape(unsigned int code, float x, float y, unsigned int frame) //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::setSpriteShape: sprite code outside boundary");
        #else
            return;
        #endif
    }
    #if _DEBUG
        if (code >= startOfFreeEndBlock || isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::setSpriteShape: sprite code not been granted access.");
        }
    #endif
    
    const float width = textureAtlas->getFrameWidth(frame);
    const float height = textureAtlas->getFrameHeight(frame);    
    spriteQuads[code].setIntAlignedPosition(x,y,width,height);
    updateMinMaxModified(code);
}

void SpriteBatch::setSpriteShape(unsigned int code, float x, float y, dimension_t width, dimension_t height) //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::setSpriteShape: sprite code outside boundary");
        #else
            return;
        #endif
    }
    #if _DEBUG
        if (code >= startOfFreeEndBlock || isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::setSpriteShape: sprite code not been granted access.");
        }
    #endif    
    
    spriteQuads[code].setIntAlignedPosition(x,y, width, height);
    updateMinMaxModified(code);
}

void SpriteBatch::setSpriteShapeAndFrame(unsigned int code, float x, float y, unsigned int frame) //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::setSpriteShape: sprite code outside boundary");
        #else
            return;
        #endif
    }
    #if _DEBUG
        if (code >= startOfFreeEndBlock || isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::setSpriteShape: sprite code not been granted access.");
        }
    #endif
    
    spriteQuads[code].setIntAlignedPosition(x,y,textureAtlas->getFrameWidth(frame),textureAtlas->getFrameHeight(frame));
    textureAtlas->getStripTextureCoordinatesFor(frame,&accessSprite(code).v00);
    updateMinMaxModified(code);
}


void SpriteBatch::setSpriteShapeAtAngle(unsigned int code, float x, float y, unsigned int frame, float radians) //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::setSpriteShapeAtAngle: sprite code outside boundary");
        #else
            return;
        #endif
    }
    #if _DEBUG
        if (code >= startOfFreeEndBlock || isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::setSpriteShapeAtAngle: sprite code not been granted access.");
        }
    #endif 
    
    spriteQuads[code].setIntAlignedRotated(x,y,textureAtlas->getFrameWidth(frame),textureAtlas->getFrameHeight(frame), radians);
    updateMinMaxModified(code);
}

void SpriteBatch::setSpriteShapeAtAngle(unsigned int code, float x, float y, dimension_t width, dimension_t height, float radians) //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::setSpriteShapeAtAngle: sprite code outside boundary");
        #else
            return;
        #endif
    }
    #if _DEBUG
        if (code >= startOfFreeEndBlock || isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::setSpriteShapeAtAngle: sprite code not been granted access.");
        }
    #endif 
    
    spriteQuads[code].setIntAlignedRotated(x,y, width, height, radians);
    updateMinMaxModified(code);
}
	
void SpriteBatch::setSpriteShapeAndFrameClipped
    (unsigned int code, float x, float y, const unsigned int frame,
     float left, float bottom, float right, float top)
     //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::setSpriteShape: sprite code outside boundary");
        #else
            return;
        #endif
    }
    #if _DEBUG
        if (code >= startOfFreeEndBlock || isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::setSpriteShape: sprite code not been granted access.");
        }
    #endif
    
    const float full_width = textureAtlas->getFrameWidth(frame);
    const float full_height = textureAtlas->getFrameHeight(frame);
    const float clipped_x = 0.5f*(left+right) + x;
    const float clipped_y = 0.5f*(bottom+top) + y;
    const float clipped_width = right-left;
    const float clipped_height = top-bottom;
    
    spriteQuads[code].setIntAlignedPosition(clipped_x,clipped_y,clipped_width,clipped_height);
    textureAtlas->getClippedTextureCoordinatesFor(frame,&accessSprite(code).v00,
                                                  (left)/full_width,
                                                  (bottom)/full_height,
                                                  (right)/full_width,
                                                  (top)/full_height);
    //textureAtlas->getTextureCoordinatesFor(frame,&accessSprite(code).v00);
    updateMinMaxModified(code);
}

void SpriteBatch::setSpriteShapeAndFrameAtAngleClipped
    (unsigned int code, float x, float y, const unsigned int frame,
     float left, float bottom, float right, float top, float radians)
     //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::setSpriteShape: sprite code outside boundary");
        #else
            return;
        #endif
    }
    #if _DEBUG
        if (code >= startOfFreeEndBlock || isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::setSpriteShape: sprite code not been granted access.");
        }
    #endif
    
    const float full_width = textureAtlas->getFrameWidth(frame);
    const float full_height = textureAtlas->getFrameHeight(frame);
    const float clipped_x = 0.5f*(left+right) + x;
    const float clipped_y = 0.5f*(bottom+top) + y;
    const float clipped_width = right-left;
    const float clipped_height = top-bottom;
        
    //spriteQuads[code].setIntAlignedRotated(clipped_x,clipped_y,clipped_width,clipped_height, radians); // problem; will rotate around the centre of the clipped portion rather than rotating around the original centre.

    const float hw = clipped_width/2;
    const float hh = clipped_height/2;
    const float sinr = std::sin(radians);
    const float cosr = std::cos(radians);
    const float phw = hw;
    const float phh = hh;

    aab::geometry::Vector vector = {left,bottom};
    vector.rotate(radians);
    vector.x += x;
    vector.y += y;        
    spriteQuads[code].v00.position.set(vector.x,vector.y);
    vector.set(left,top);
    vector.rotate(radians);
    vector.x += x;
    vector.y += y;        
    spriteQuads[code].v01.position.set(vector.x,vector.y);
    vector.set(right,bottom);
    vector.rotate(radians);
    vector.x += x;
    vector.y += y;        
    spriteQuads[code].v10.position.set(vector.x,vector.y);
    vector.set(right,top);
    vector.rotate(radians);
    vector.x += x;
    vector.y += y;        
    spriteQuads[code].v11.position.set(vector.x,vector.y);
    //todo - move into a setIntAlignedRotatedAround method, which sets rotated around a position.
        
    textureAtlas->getClippedTextureCoordinatesFor(frame,&accessSprite(code).v00,
                                                  (left)/full_width,
                                                  (bottom)/full_height,
                                                  (right)/full_width,
                                                  (top)/full_height);
    //textureAtlas->getTextureCoordinatesFor(frame,&accessSprite(code).v00);
    updateMinMaxModified(code);
}

void SpriteBatch::setSpriteShapeAndFrameScaledClipped
    (unsigned int code, float x, float y, const unsigned int frame,
     float left, float bottom, float right, float top, float sx, float sy)
     //_DEBUG std::out_of_range, std::logic_error
{
    if (code >= spriteQuads.size())
    {
        #if _DEBUG
            THROW_ERROR(std::out_of_range,"SpriteBatch::setSpriteShape: sprite code outside boundary");
        #else
            return;
        #endif
    }
    #if _DEBUG
        if (code >= startOfFreeEndBlock || isInFreeSpace(code))
        {
            THROW_ERROR(std::logic_error,"SpriteBatch::setSpriteShape: sprite code not been granted access.");
        }
    #endif
    
    const float full_width = textureAtlas->getFrameWidth(frame);
    const float full_height = textureAtlas->getFrameHeight(frame);
    const float clipped_x = 0.5f*(left+right) + x;
    const float clipped_y = 0.5f*(bottom+top) + y;
    const float clipped_width = right-left;
    const float clipped_height = top-bottom;
    
    spriteQuads[code].setIntAlignedPosition(clipped_x,clipped_y,sx*clipped_width,sy*clipped_height);
    textureAtlas->getClippedTextureCoordinatesFor(frame,&accessSprite(code).v00,
                                                  (left)/full_width,
                                                  (bottom)/full_height,
                                                  (right)/full_width,
                                                  (top)/full_height);
    //textureAtlas->getTextureCoordinatesFor(frame,&accessSprite(code).v00);
    updateMinMaxModified(code);
}
	
void SpriteBatch::updateSprites()
{
    // no need to update the entire VBO
    // but do need to update regions that might have recently been updatedated.

    
    /*
    unsigned int startOfFreeEndBlockL = startOfFreeEndBlock;
    unsigned int lastStartOfFreeEndBlockL = lastStartOfFreeEndBlock;
    unsigned int updateSize = (startOfFreeEndBlock < lastStartOfFreeEndBlock?lastStartOfFreeEndBlock : startOfFreeEndBlock);
   
    //bufferObject->updateRegion(0,&(spriteQuads[0].v00),4*startOfFreeEndBlock);
    if (updateSize)
        bufferObject->updateRegion(0,&(spriteQuads[0].v00),4*updateSize);
        
    lastStartOfFreeEndBlock = startOfFreeEndBlock;
    */
    
    //If the buffer has shrunk, update the larger old size to correctly zero remaining components.
    
    //unsigned int updateSize = (startOfFreeEndBlock < lastStartOfFreeEndBlock? lastStartOfFreeEndBlock : startOfFreeEndBlock);
    
    //if(updateSize)
    //    bufferObject->updateRegion(0,&(spriteQuads[0].v00),4*updateSize);
        
    lastStartOfFreeEndBlock = startOfFreeEndBlock;
    
    
    if (maxModified - minModified > -1)
    {
        bufferObject->updateRegion(4*minModified,&(spriteQuads[minModified].v00),4*(maxModified-minModified + 1));
    }
    
    resetMinMaxModified();
}

void SpriteBatch::updateMinMaxModified(const unsigned int code)
{
    minModified = std::min(minModified,static_cast<int>(code));
    maxModified = std::max(maxModified,static_cast<int>(code));
}

void SpriteBatch::resetMinMaxModified()
{
    minModified = 65535;//std::numeric_limits<int>::max()/2;
    maxModified = 0;
}


void SpriteBatch::updateEntireBuffer()
{
    bufferObject->update(&(spriteQuads[0].v00)); // updates entire VBO
    resetMinMaxModified();
}

void SpriteBatch::resize(unsigned int newSize)//_DEBUG std::out_of_range
{
    SpriteQuad blankQuad = {0,0, 0,0, aab::visen::Colorub::white};
    
    if (spriteQuads.size() == newSize)
    {
        return;
    }
    
    if (newSize < spriteQuads.size())
    {
        // smaller  -make sure released sprite codes will not be invalidated
        
        if (startOfFreeEndBlock < newSize)
        {
            #if _DEBUG
                THROW_ERROR(std::out_of_range,"SpriteBatch::accessSprite: sprite code outside boundary");
            #else
                newSize = startOfFreeEndBlock;
            #endif
        }
    }
    
    spriteQuads.resize(newSize,blankQuad);
    bufferObject->setBuffer(&(spriteQuads[0].v00), 4*spriteQuads.size());
    
    if(lastStartOfFreeEndBlock > spriteQuads.size())
    {
        lastStartOfFreeEndBlock = spriteQuads.size();
    }
    
}

void SpriteBatch::releaseAllSprites() //throw()
{
    SpriteQuad blankQuad = {0,0, 0,0, aab::visen::Colorub::white};
    std::fill(spriteQuads.begin(),spriteQuads.begin()+startOfFreeEndBlock, blankQuad);
    freeSpace.clear();
    startOfFreeEndBlock = 0;
    resetMinMaxModified();
}

        

}		//	game
}		//	aab






