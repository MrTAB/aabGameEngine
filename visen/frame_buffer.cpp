/**
*
*	frame_buffer.cpp
*
**/

#include"frame_buffer.hpp"
#include"_include_opengl.hpp"
#include<cassert>
namespace aab	{
namespace visen	{

namespace attachment_point
{
    const AttachmentPoint color_attachment_0 = GL_COLOR_ATTACHMENT0;
    const AttachmentPoint color_attachment_1 = GL_COLOR_ATTACHMENT1;
    const AttachmentPoint color_attachment_2 = GL_COLOR_ATTACHMENT2;
    const AttachmentPoint color_attachment_3 = GL_COLOR_ATTACHMENT3;
    const AttachmentPoint color_attachment_4 = GL_COLOR_ATTACHMENT4;
    const AttachmentPoint color_attachment_5 = GL_COLOR_ATTACHMENT5;
    const AttachmentPoint color_attachment_6 = GL_COLOR_ATTACHMENT6;
    const AttachmentPoint color_attachment_7 = GL_COLOR_ATTACHMENT7;
    const AttachmentPoint color_attachment_8 = GL_COLOR_ATTACHMENT8;
    const AttachmentPoint color_attachment_9 = GL_COLOR_ATTACHMENT9;
    const AttachmentPoint color_attachment(unsigned int value)
    {
        assert(value < static_cast<unsigned int>(FrameBuffer::getMaxColorAttachments()));
        return GL_COLOR_ATTACHMENT0 + value;
    }
    const AttachmentPoint depth = GL_DEPTH_ATTACHMENT;
    const AttachmentPoint stencil = GL_STENCIL_ATTACHMENT;
    const AttachmentPoint depth_stencil = GL_DEPTH_STENCIL_ATTACHMENT;
};

int FrameBuffer::getMaxColorAttachments()
{
    GLint data;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &data);
    return data;
}

FrameBuffer::FrameBuffer():width(0),height(0)
{
    glGenFramebuffers(1,&glId);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1,&glId);
}

void FrameBuffer::attachTexture2D(aab::visen::TextureBasePtr texture, AttachmentPoint attachmentPoint)
{
    width = texture->getImageWidth();
    height = texture->getImageHeight();
    viewportX = texture->getClearBorderX();
    viewportY = texture->getClearBorderY();
    glBindFramebuffer(GL_FRAMEBUFFER, glId);
    glFramebufferTexture2D(GL_FRAMEBUFFER,attachmentPoint,GL_TEXTURE_2D,texture->getId(), 0);
    //todo - throw if problem    
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



void FrameBuffer::switchToThisBuffer()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,glId);
        
    glViewport(viewportX,viewportY,width,height);      
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0,width,height,0);
}

void FrameBuffer::switchToThisBufferInverted()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,glId);
        
    glViewport(viewportX,viewportY,width,height);      
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0,width,0,height);
}

void FrameBuffer::switchBacktoScreen(Screen screen)
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
    screen->resetProjection();
}
    
    
    
}		//	visen
}		//	aab

