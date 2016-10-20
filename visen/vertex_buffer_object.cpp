
/**
*
*	vertex_buffer_object.cpp
*
**/

#include"vertex_buffer_object.hpp"
#include"error_trap.hpp"
#include"_include_opengl.hpp"
#include<cstddef>
#include<stdexcept>
#include<cassert>
#include"../test/debug_assertions.hpp"
namespace aab	{
namespace visen	{
    
// todo - expand to allow use of glPrimitiveRestartIndex

/*
VertexBufferObject::VertexBufferObject( const Vertex * vertices, const unsigned int sizeIn, VertexBufferObjectUsage usageIn, const VertexIndex * indices, const unsigned int indicesCountIn) throw (std::exception&)
{
    //todo - use error trap to catch any mistakes
    
    aab::visen::ErrorTrap error_trap;
    bool generateIndices = false;
    
    switch(usageIn)
    {
    case vbo_usage_stream: usage = GL_STREAM_DRAW; break;
    case vbo_usage_static: usage = GL_STATIC_DRAW;  break;
    case vbo_usage_dynamic: default: usage = GL_DYNAMIC_DRAW; break;
    }
    
    vertexCount = sizeIn;
    indicesCount = indicesCountIn;
    
    if (indicesCount == 0)
    {
        indicesCount = indicesNeededForVertices(vertexCount);
    }
    
    if (vertexCount < 1 || indicesCount < 1)
    {
        throw std::logic_error ("VertexBufferObject::VertexBufferObject:: sizes cannot be less than 1");
    }
    
    if (indices == staticIndexList && indicesCount >= VISEN_MAX_STATIC_INDEX)
    {
        generateIndices = true;
    }
    
    glGenBuffers( 1, &vertexBuffer );
    glGenBuffers( 1, &indexBuffer );

    // Copy the vertex data to the VBO
    glBindBufferARB( GL_ARRAY_BUFFER, vertexBuffer );
    glBufferDataARB( GL_ARRAY_BUFFER, sizeof(Vertex)*vertexCount, vertices, usage ); // buff_format, size(bytes), data, usage
    glBindBufferARB( GL_ARRAY_BUFFER, 0 );
     
    // Copy the index data to the VBO
    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
    if (generateIndices)
    {
        std::vector<VertexIndex> generatedIndices;
        generateStripQuadIndices(generatedIndices, sizeIn/4);
        indicesCount = generatedIndices.size();
        glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indicesCount, &generatedIndices[0], GL_STATIC_DRAW );
    }
    else
    {
        glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indicesCount, indices, GL_STATIC_DRAW );
    }
    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, 0 );
     
    //glEnableClientState(GL_VERTEX_ARRAY); // todo - should these be left enabled rather than re-enabled each time?    
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    
    error_trap.tryRaise(); 
}
*/

VertexBufferObject::VertexBufferObject( const Vertex * vertices,
                                       const unsigned int sizeIn,
                                       VertexBufferObjectUsage usageIn,
                                       IndexGenerator * indexGeneratorIn):
                                       // std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
    indexGenerator(indexGeneratorIn)
{
    assert(indexGenerator);
    //todo - use error trap to catch any mistakes
    
    aab::visen::ErrorTrap error_trap ("VertexBufferObject::VertexBufferObject::\t");
    
    switch(usageIn)
    {
    case vbo_usage_stream: usage = GL_STREAM_DRAW; break;
    case vbo_usage_static: usage = GL_STATIC_DRAW;  break;
    case vbo_usage_dynamic: default: usage = GL_DYNAMIC_DRAW; break;
    }
    
    renderType = GL_TRIANGLE_STRIP;
    std::vector<VertexIndex> generatedIndices;
    indexGenerator->generateIndices(generatedIndices, sizeIn/4, renderType);
    indicesCount = generatedIndices.size();
    
    vertexCount = sizeIn;
    
    if (vertexCount < 1 || indicesCount < 1)
    {
        throw std::invalid_argument ("VertexBufferObject::VertexBufferObject:: sizes cannot be less than 1");
    }
    
    glGenBuffersARB( 1, &vertexBuffer );
    glGenBuffersARB( 1, &indexBuffer );

    // Copy the vertex data to the VBO
    glBindBufferARB( GL_ARRAY_BUFFER, vertexBuffer );
    glBufferDataARB( GL_ARRAY_BUFFER, sizeof(Vertex)*vertexCount, vertices, usage ); // buff_format, size(bytes), data, usage
    glBindBufferARB( GL_ARRAY_BUFFER, 0 );
     
    // Copy the index data to the VBO
    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
    glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indicesCount, &generatedIndices[0], GL_STATIC_DRAW );

    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, 0 );
     
    //glEnableClientState(GL_VERTEX_ARRAY); // todo - should these be left enabled rather than re-enabled each time?    
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    
    error_trap.tryRaise(); 
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffersARB (1, &vertexBuffer);
    glDeleteBuffersARB (1, &indexBuffer);
    //delete indexGenerator;
}


void VertexBufferObject::render() const
{
    if (0 == vertexCount)
    {
        _DEBUG_RESPONSE(throw std::logic_error("VertexBufferObject::render::\tcannot render a VBO with no vertices."));
        _RELEASE_RESPONSE(return);
    }
    
    glEnableClientState(GL_VERTEX_ARRAY); // todo - should these be left enabled rather than re-enabled each time?    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glBindBufferARB( GL_ARRAY_BUFFER, vertexBuffer );
    glVertexPointer( 2, GL_FLOAT, sizeof(Vertex), (void*)(offsetof(Vertex,position)));    //&Vertex::position ? 
    glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex,textCoord) );
    glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex,color) );

    //glBindBufferARB( GL_ARRAY_BUFFER, vertexBuffer ); // should this be called each time?
    // Bind the indices's VBO
    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
    glDrawElements( renderType, indicesCount, GL_UNSIGNED_INT,  (void*)0 );
    
    // Unbind buffers so client-side vertex arrays still work.
    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindBufferARB( GL_ARRAY_BUFFER, 0 );
     
    glDisableClientState(GL_VERTEX_ARRAY);    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

//vertex offset becomes the first vertex.
//lastIndex becomes the count of indices
void VertexBufferObject::renderRegion(unsigned int vertexOffset, size_t indicesToRender) const // _DEBUG std::out_of_range
{
    if (vertexOffset >= vertexCount)
    {
        #ifdef _DEBUG
            throw std::out_of_range("VertexBufferObject::renderRegion: invalid region start.");
        #else
            return;
        #endif
    }
    /*
    if (start + count > indicesCount)
    {
        #ifdef _DEBUG
            throw std::out_of_range("VertexBufferObject::renderRegion: region goes past end of buffer");
        #else
            count = indicesCount - start;
        #endif
    }
    */
    if (indicesToRender > indicesCount)
    {
        #ifdef _DEBUG
            throw std::out_of_range("VertexBufferObject::renderRegion: region goes past end of buffer.");
        #else
            indicesToRender = indicesCount;
        #endif
    }
    
    glEnableClientState(GL_VERTEX_ARRAY); // todo - should these be left enabled rather than re-enabled each time?    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glBindBufferARB( GL_ARRAY_BUFFER, vertexBuffer );
    glVertexPointer( 2, GL_FLOAT, sizeof(Vertex), (void*)(offsetof(Vertex,position)) );    
    glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), (void*)(offsetof(Vertex,textCoord)) );
    glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)(offsetof(Vertex,color)) );

    //glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer ); // should this be called each time?
    // Bind the indices's VBO
    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
    
    //#define USE_BASE_VERTEX
    
    #ifdef USE_BASE_VERTEX
    
        
        glDrawElementsBaseVertex( renderType, indicesToRender, GL_UNSIGNED_INT,  (void*)0 , vertexOffset); //todo - use this if available?
        
    #else
    
        // better version of function may ask for region in terms of quads
            
        const unsigned int vertexOffsetIndex = indexGenerator->getObjectIndexFromStartingValue(vertexOffset);

        if (vertexOffsetIndex + indicesToRender - indexGenerator->trailingDegenerates() > indicesCount)
        {
            #ifdef _DEBUG
                throw std::out_of_range("VertexBufferObject::renderRegion: vertexOffsetIndex + indicesToRender goes past end of buffer.");
            #else
                indicesToRender = indicesCount - vertexOffsetIndex;
            #endif
        }
        
        const GLuint start = vertexOffset;
        const GLuint end = indexGenerator->getIndexValue(vertexOffsetIndex+indicesToRender);//index_value for index indicesToRender above first index with value vertexOffset;
        const GLsizei count = indicesToRender - indexGenerator->trailingDegenerates(); // no need to draw the last two indices
        const GLenum type = GL_UNSIGNED_INT;
        const void *indices = (void*)(vertexOffsetIndex*sizeof(VertexIndex));
        
        //glDrawElements(mode, count, type, indices); // changed for potential performance benefit.
        glDrawRangeElements(renderType, start, end, count, type, indices); 
        
    
    
    #endif
    
    
    // Unbind buffers so client-side vertex arrays still work.
    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindBufferARB( GL_ARRAY_BUFFER, 0 );
     
    glDisableClientState(GL_VERTEX_ARRAY);    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}


void VertexBufferObject::update(const Vertex * vertices)
{
    glBindBufferARB(GL_ARRAY_BUFFER, vertexBuffer );
    glBufferDataARB(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexCount, NULL, usage); // don't care about existing data patch
    glBufferSubDataARB(GL_ARRAY_BUFFER, 0, sizeof(Vertex)*vertexCount, vertices); // replace data
    glBindBufferARB(GL_ARRAY_BUFFER, 0 );
}

void VertexBufferObject::setBuffer(const Vertex * vertices,
                                   const unsigned int sizeIn,
                                   IndexGenerator * indexGeneratorIn)
                                   //_DEBUG std::invalid_argument
{   
  
    unsigned int oldVertexCount = vertexCount;
    unsigned int oldIndicesCount = indicesCount;
     
    assert(indexGeneratorIn);
    //delete indexGenerator;
    indexGenerator = indexGeneratorIn;
    vertexCount = sizeIn;
    std::vector<VertexIndex> generatedIndices;
    indexGenerator->generateIndices(generatedIndices, sizeIn/4, renderType);
    indicesCount = generatedIndices.size();
    
    if (vertexCount < 1 || indicesCount < 1)
    {
        throw std::invalid_argument ("VertexBufferObject::setBuffer:: sizes cannot be less than 1");
    }
    

    glBindBufferARB( GL_ARRAY_BUFFER, vertexBuffer );
    glBufferDataARB( GL_ARRAY_BUFFER, sizeof(Vertex)*oldVertexCount, NULL,usage); // don't care about existing data patch
    glBufferDataARB( GL_ARRAY_BUFFER, sizeof(Vertex)*vertexCount, vertices, usage );
    glBindBufferARB( GL_ARRAY_BUFFER, 0 );
    
    //glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
    //glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*oldIndicesCount, NULL,GL_STATIC_DRAW);
    //glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indicesCount, indices, GL_STATIC_DRAW );
    //glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, 0 );

    // Copy the index data to the VBO
    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
    glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*oldIndicesCount, NULL,GL_STATIC_DRAW);
    glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indicesCount, &generatedIndices[0], GL_STATIC_DRAW );

    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, 0 );
    
    
    
}

void VertexBufferObject::updateRegion(const unsigned int regionStart,
                                      const Vertex * vertices,
                                      unsigned int regionSize)
//_DEBUG std::out_of_range, _DEBUG std::invalid_argument
{
  
    if (regionSize < 1)
    {
        #ifdef _DEBUG
            throw std::invalid_argument("VertexBufferObject::updateRegion: must be 1 or more vertices");
        #else
            return;
        #endif
    }
    
    if (regionStart >= vertexCount)
    {
        #ifdef _DEBUG
            throw std::out_of_range("VertexBufferObject::updateRegion: regionStart is past end of buffer data");
        #else
            return;
        #endif
    }
 
    if (regionSize + regionStart > vertexCount)
    {
        #ifdef _DEBUG
            throw std::out_of_range("VertexBufferObject::updateRegion: vertices given exceed range of buffer");
        #else
            regionSize = vertexCount - regionStart;
        #endif
    }
    
    glBindBufferARB( GL_ARRAY_BUFFER, vertexBuffer ); //todo - change from ARB
    glBufferSubDataARB (GL_ARRAY_BUFFER, regionStart*sizeof(Vertex), regionSize*sizeof(Vertex), vertices );
    glBindBufferARB( GL_ARRAY_BUFFER, 0 );
}

bool VertexBufferObject::isUsingTriangleStrips()const
{
    return renderType == GL_TRIANGLE_STRIP;
}
bool VertexBufferObject::isUsingQuads()const
{
    return renderType == GL_QUADS;
}

}	//	visen
}	//	aab


