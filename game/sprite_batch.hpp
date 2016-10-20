
/**
* @file
* @author mentrox@gmail.com
* @version 1.0
* @date
*
* @section DESCRIPTION
*
* Sprite Batch
*
*
*   Uses a Vertex Buffer Object (VBO) set up with triangle strips:
*       Every four vertices represents a quad (degenerate strips seperate these "quads")
*       Each quad represents one sprite.
*       The one texture can be bound, and then the entire VBO rendered, to efficiently render each sprite.
*       A Texture Atlas is used, which means frames can be of different image size and can include non power of two shapes.
*   The VBO is of a fixed size on startup, with blank vertices at first.*
*   Entities that wish to use this texture and VBO pairing, can request a quad, and
*       be given access to four of the client local vertices which will be sent
*       to the Buffer Object in GPU memory via the VBO.
*       The Sprite Batch class maintains that quad.
*   
*
*       * Expanding the Buffer Object can be done under the hood, but it impacts performance to do so.
*       Initial implementation will exclude it.
*
*   todo - add method to draw a portion using VBO's extension of DrawElementsBaseVertex (when available)
*
*
*   If _DEBUG is defined, will throw exceptions on errors, otherwise will try best to behave without throwing exceptions. 
**/


#if !defined(AAB_GAME_SPRITE_BATCH_CLASS)
#define AAB_GAME_SPRITE_BATCH_CLASS
/*
#include"transformation_node.hpp"
#include"../types/smart_ptr.hpp"
#include"../visen/texture_base.hpp"
#include"../visen/texture.hpp"
#include"../visen/animated_texture.hpp"
//#include"../time/sub_animator.hpp"
*/
#include"prototype/sprite_batch.hh"
#include"../visen/texture_atlas.hpp"
#include"../visen/quad.hpp"
#include"../visen/vertex_buffer_object.hpp"
#include"../test/debug_assertions.hpp"
//#include<exception>
#include<vector>
#include<set>
#include<stdexcept>
namespace aab	{
namespace game	{
   
typedef aab::visen::StripQuad SpriteQuad;

//typedef unsigned int SpriteCode;

class SpriteBatch
{ 
    public:
    
        typedef aab::visen::Vertex Vertex;
        typedef aab::visen::TextureAtlasPtr TextureAtlasPtr;
        
    private:
    
        unsigned int startOfFreeEndBlock;
        unsigned int lastStartOfFreeEndBlock;
        int minModified;
        int maxModified;
        
        unsigned int id_for_errors;
        
        std::vector<SpriteQuad> spriteQuads;
        TextureAtlasPtr textureAtlas;
        aab::visen::VertexBufferObject* bufferObject;
        std::set<unsigned int> freeSpace;        
        
       
        bool isInFreeSpace(unsigned int code) const
        {
            return freeSpace.end() != freeSpace.find(code);
        }
        
        void updateMinMaxModified(const unsigned int code); 
        void resetMinMaxModified();       
    
    public:
    
        /*  size, i.e. number of sprites/quads represented.
            These will begin with blank data.
        */
        
        explicit SpriteBatch (TextureAtlasPtr, unsigned int size);// _DEBUG std::invalid_argument
        /*virtual*/ ~SpriteBatch();// throw();
        
        
        void render();
        void renderNoBind();
        void renderRegionNoBind(unsigned int start, size_t size);
        
        inline TextureAtlasPtr getTextureAtlas() { return textureAtlas; }
		//inline visen::BlendMethod & accessBlendMethod () { return textureAtlas->accessBlendMethod(); } // removed as it changes the underlying texture atlas. Use getTextureAtlas, which doesnt hide that a shared texture atlas is being modified.yy
		
		inline unsigned int getCapacity() const { return bufferObject->getSize()/4; }
		inline unsigned int countSprites() const { return startOfFreeEndBlock - freeSpace.size(); }
		
		inline unsigned int getStartOfFreeEndBlock() const { return startOfFreeEndBlock;}
		
		/*
		*   In debug build, generateSprite will throw a logic_error if there is no more room in the buffer
		*   In a release build, generateSprite will call resize() instead; this is costly, and so the debug
		*   behaviour of raising an exception hints to the programmer to make their sprite batch bigger.
		*   Keep in mind, resize can also throw.
		*   A generated sprite should have its quad shaped, either via direct access or with setSpriteShape
		*/
		unsigned int generateSprite() ;//std::logic_error
		
		/*
		* releaseSprite does not throw exceptions - safe to use in decionstructors
		*/
		void releaseSprite(unsigned int);// throw();
		
		bool isSpriteInUse (unsigned int code)const;
		
		typedef float dimension_t;
		
		SpriteQuad & accessSprite(const unsigned int code) ;//_DEBUG std::out_of_range, std::logic_error
		const SpriteQuad & accessSprite(const unsigned int code) const;//_DEBUG std::out_of_range, std::logic_error
		void setSpriteFrame(unsigned int code, unsigned int frame);
		void setSpriteShape(unsigned int code, float x, float y, unsigned int frame) ;//_DEBUG std::out_of_range, std::logic_error
		void setSpriteShape(unsigned int code, float x, float y, dimension_t width, dimension_t height);//_DEBUG std::out_of_range, std::logic_error
		void setSpriteShapeAndFrame(unsigned int code, float x, float y, unsigned int frame);//_DEBUG std::out_of_range, std::logic_error
		void setSpriteShapeAtAngle(unsigned int code, float x, float y, unsigned int frame, float radians);//_DEBUG std::out_of_range, std::logic_error
		void setSpriteShapeAtAngle(unsigned int code, float x, float y, dimension_t width, dimension_t height, float radians);//_DEBUG std::out_of_range, std::logic_error
		void resizeSprite(unsigned int code, unsigned int oldFrame, unsigned int newFrame);//_DEBUG std::out_of_range, std::logic_error // A sprite that has been scaled may need resized from one frame to the next: use this
            // left, bottom, right and top are positions of the clipped frame relative tot he CENTRE of the sprite.
		void setSpriteShapeAndFrameClipped(unsigned int code, float x, float y, const unsigned int frame, float left, float bottom, float right, float top);//_DEBUG std::out_of_range, std::logic_error
		void setSpriteShapeAndFrameAtAngleClipped(unsigned int code, float x, float y, const unsigned int frame, float left, float bottom, float right, float top, float radians);//_DEBUG std::out_of_range, std::logic_error
		void setSpriteShapeAndFrameScaledClipped(unsigned int code, float x, float y, const unsigned int frame, float left, float bottom, float right, float top, float sx, float sy);//_DEBUG std::out_of_range, std::logic_error
		
		float guessSpriteWidth(unsigned int code)const ;//_DEBUG std::out_of_range
		float guessSpriteHeight(unsigned int code)const;//_DEBUG std::out_of_range
		float guessSpriteX(unsigned int code)const;//_DEBUG std::out_of_range
		float guessSpriteY(unsigned int code)const;//_DEBUG std::out_of_range
		float guessSpriteAngle(unsigned int code)const;//_DEBUG std::out_of_range
		
        int getFrameWidth (const unsigned int frame)const
        {
            return textureAtlas->getFrameWidth(frame);
        }
        int getFrameHeight (const unsigned int frame)const
        {
            return textureAtlas->getFrameHeight(frame);
        }
		
		
		//call "en masse" after updating sprites this frame
		void updateSprites();
		//updates entire buffer: cheaper than using updateSprites() if the full size is currently in use.
		void updateEntireBuffer();
		
		
		// costly operation
		// In debug build, will throw if the resize operation would invalidate currently released sprite codes
		// In release build, it chooses not to resize enough to invalidate sprite codes.
		void resize(unsigned int newSize);//_DEBUG std::out_of_range
		
		// will release all sprites without asking questions...
		void releaseAllSprites();//throw();
		
		void set_id_for_errors(const unsigned int id_in) // set to something non-zero: will be reported when an exception is thrown.
		{
		    id_for_errors = id_in;
		}
		
};

/*
    Implementation note: to keep track of freed sections, use a stack, and a note of the first of the contiguous end blocks beginning.
    Note: as vertices are a vector, cannot link to data itself, or store iterator
        If the stack has anything in it, pop off the top of the stack, and give it as the newly requested sprite.
        problem with this implementation:
            A future impl will render only the elements of the VBO which are required.
                Thus they should be continuous. Unfortunately, defragmentation is not possible,
                The best solution is to sort this stack such that the element at the top will be within the largest chunk of data
                Is this the one with elements in either direction but with elements such that the distance to the surrounding elements is greatest?
                Alternatively, they could be sorted in ascending order, to try and keep the ordering near the start!
            These ideas are only important in situations where many sprites are to be created and destroyed at runtime.
    Very simple, as all data requests will be for quads of the same size.

*/

}		//	game
}		//	aab
#endif	//	AAB_GAME_SPRITE_BATCH_CLASS




