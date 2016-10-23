/**
*
*	frame_buffer.hpp
*
*	Use for rendering to a texture; supply the texture when creating the frame
*   buffer, then call switchToThisBuffer() to set render operations to occur
*   on this buffer. Call switchBacktoScreen(Screen) when done.
*
*   todo - some sort of push/pop mechanism for guaranteed temporary rendering to
*   buffer.
**/

#if !defined(AAB_VISEN_FRAME_BUFFER_CLASS)
#define AAB_VISEN_FRAME_BUFFER_CLASS
#include"screen.hpp"
#include"texture_base.hpp"
namespace aab	{
namespace visen	{


typedef unsigned int AttachmentPoint;

namespace attachment_point
{
    extern const AttachmentPoint color_attachment_0;
    extern const AttachmentPoint color_attachment_1;
    extern const AttachmentPoint color_attachment_2;
    extern const AttachmentPoint color_attachment_3;
    extern const AttachmentPoint color_attachment_4;
    extern const AttachmentPoint color_attachment_5;
    extern const AttachmentPoint color_attachment_6;
    extern const AttachmentPoint color_attachment_7;
    extern const AttachmentPoint color_attachment_8;
    extern const AttachmentPoint color_attachment_9;
    AttachmentPoint color_attachment(unsigned int);
    extern const AttachmentPoint depth;
    extern const AttachmentPoint stencil;
    extern const AttachmentPoint depth_stencil;
};

class FrameBuffer
{
	private:

        unsigned int glId;
        float width;
        float height;
        float viewportX;
        float viewportY;
        
        FrameBuffer(const FrameBuffer&);

	public:

    unsigned int getId()const
    {
        return glId;
    }

    FrameBuffer();

    ~FrameBuffer();

    void attachTexture2D(aab::visen::TextureBasePtr texture, AttachmentPoint attachmentPoint);

    void switchToThisBuffer(); // enables rendering on this framebuffer. Uses bottom left coordinate system
    void switchToThisBufferInverted(); // enables rendering on this framebuffer, uses top left coordinate system - remmember to render clockwise
    
    void switchBacktoScreen(Screen screen);
    
    static int getMaxColorAttachments();
};




}		//	visen
}		//	aab
#endif //AAB_VISEN_FRAME_BUFFER_CLASS
