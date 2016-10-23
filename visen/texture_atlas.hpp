/**
*
*	texture atlas.hpp
*
*   A texture atlas allows a collection of 'sub textures'to be mapped from one
   large source texture. These sub textures can have any size and position within
   the original texture atlas, and can even overlap if desired.
*
**/

#if !defined(AAB_VISEN_TEXTURE_ATLAS_CLASS)
#define AAB_VISEN_TEXTURE_ATLAS_CLASS
/*#include"texture.hpp"
#include"texture_base.hpp"
#include"../types/manager.hpp"
#include"../types/smart_ptr.hpp"
*/
#include"framed_texture.hpp"
#include"vertex.hpp"
#include<vector>
namespace aab	{
namespace visen	{

#ifdef _DEBUG
    #define AAB_VISEN_TEXTURE_ATLAS_MAX_FRAMES 65535
#endif


struct AtlasFrame
{
    float x1, y1, x2, y2; // texture coordinates to draw this frame
    int width, height; // size of frame in pixels
};

struct FrameDefinition
{
    int x, y, w, h;
};


class TextureAtlasClass: public FramedTextureClass//: public TextureBaseClass
{
    public:
    
    typedef aab::types::Smart <TextureAtlasClass>::Ptr Ptr;
    typedef aab::types::Smart <const TextureAtlasClass>::Ptr ConstPtr;
    
    protected:
    
        //TexturePtr texture;
        std::vector<AtlasFrame> frames;
        //int currentFrame;
    
    protected:
    
		friend Ptr makeTextureAtlas (TexturePtr);//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
					
		explicit TextureAtlasClass (TexturePtr);//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		virtual ~TextureAtlasClass () throw ();
		
		
		
    public:
    
        void addFrame (int x, int y, int width, int height);    //_DEBUG std::invalid_argument    
        void addFrames (FrameDefinition *, unsigned int frameCount); //_DEBUG std::invalid_argument
        
        ///TexturePtr getTexture ();
        
        virtual int getMaximumFrame () const;
        
        virtual bool isValidFrame (unsigned int frame) const;
            
        
        //void bind()throw();
        
        //void render ();
        virtual void renderNobind();

        /*
        float getFrameX(int frame) const;
        float getFrameY(int frame) const;
        float getTextureCoordinateWidth() const { return wfrac; }
        float getTextureCoordinateHeight() const { return hfrac; }
        float getEnvelopeWidth() const { return drawWidth; }
        float getEnvelopeHeight() const { return drawHeight; }
        */
        virtual float getFrameX(int frame) const;
        virtual float getFrameY(int frame) const;
	
        BlendMethod & accessBlendMethod () { return texture->accessBlendMethod(); }
        //virtual void updateBlendMethod() {texture->updateBlendMethod(); } ;  
        
        virtual bool isAnimatable () const { return true; }
        virtual void setFrame(int frame);
        //void setFrameHFlipped(int frame);
        //void setFrameHFlipped(int frame);
        ///int getFrame()const { return currentFrame; }
        
        virtual int getFrameWidth (const unsigned int frame)const; //_DEBUG std::invalid_argument
        virtual int getFrameHeight (const unsigned int frame)const; //_DEBUG std::invalid_argument
        
        //can be used explicitly to set a texture frame not specified in the internal frame list
        void updateTextureCoordinates(const AtlasFrame & frame);
        
        // returns coordinates for a traingle strip rendering - top left, bottom left, top right, bottom right
        //can be used when updating a vertex array for more efficient use of the texture atlas
        //Use bind(), update manyn objects in the array with this method, and then draw in one large pass.
        //This method expects a sequence of pairs of floats, each pairs start seperated by "offset" floats.
        //i.e. if they were contigious, it would be 2, if using Vertex, it would be sizeof(Vertex)/sizeof(float)
        //setFrame is not needed in these circumstances: simply set the texture coordinates in the array you are using
        //based on the data this returns to you
        void getTextureCoordinatesFor(unsigned int frame, float * first, unsigned int offset) const;  //_DEBUG std::invalid_argument//todo - add as vritual to framed_texture
        virtual void getStripTextureCoordinatesFor(unsigned int frame, Vertex * first) const;  //_DEBUG std::invalid_argument
        virtual void getCCWTextureCoordinatesFor(unsigned int frame, Vertex * first) const;  //_DEBUG std::invalid_argument
            //to use: left ratio is fraction of texture frame to clip from the centre etc.
            // e.g. something is centred annd half the width could have (-0.25f,-0.5f,0.25f,0.5f)
        virtual void getClippedTextureCoordinatesFor(const unsigned int frame, Vertex * first,
                    const float left_ratio, const float bottom_ratio, const float right_ratio, const float top_ratio) const;  //_DEBUG std::invalid_argument
        virtual void getCCWClippedTextureCoordinatesFor(const unsigned int frame, Vertex * first,
                    const float left_ratio, const float bottom_ratio, const float right_ratio, const float top_ratio) const; 
};


typedef TextureAtlasClass::Ptr TextureAtlasPtr;
typedef TextureAtlasClass::ConstPtr TextureAtlasConstPtr;

TextureAtlasPtr makeTextureAtlas (TexturePtr);//std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error

}		//	visen
}		//	aab
#endif //AAB_VISEN_TEXTURE_ATLAS_CLASS

