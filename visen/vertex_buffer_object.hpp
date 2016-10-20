
/**
*
*	vertex_buffer_object.hpp
*
*
*   Client supplies vertex data. Data supplied to updateBuffer must match the existing size of the buffer.
*
*   Currently, only the default Vertex is supported. The internals must be changed if the default vertex is changed.
*
*   Assumes static indices; although they can be changed with SetBuffer, they are not optimised for change by the GPU.
*
*   If _DEBUG is defined, will throw exceptions on errors, otherwise will try best to behave without throwing exceptions. 
*
*
*   todo : add method to draw a portion using DrawElementsBaseVertex
**/

#if !defined(AAB_VISEN_VERTEX_BUFFER_OBJECT_CLASS)
#define AAB_VISEN_VERTEX_BUFFER_OBJECT_CLASS
//#include"../types/manager.hpp"
#include"prototype/vertex_buffer_object.hh"
#include"vertex.hpp"
#include"index_generator.hpp"
#include<cstdint>
namespace aab	{
namespace visen	{
    
enum VertexBufferObjectUsage
{
    vbo_usage_stream, // changes constantly - default
    vbo_usage_static, // doesn't change much
    vbo_usage_dynamic // changes occassionally
};


//typedef std::vector<Vertex> VertexArray;



class VertexBufferObject
{
    uint32_t vertexBuffer;
    uint32_t indexBuffer;
    uint32_t usage;
    unsigned int vertexCount;
    unsigned int indicesCount;
    unsigned int renderType;
    IndexGenerator * indexGenerator;
    
    VertexBufferObject(const VertexBufferObject&);
        
    public:
    
        // if index count is zero, it is assumed to be 6/4 * the size of vertices to account for degenerate strips between quads
        //VertexBufferObject(const Vertex * vertices, const unsigned int count, VertexBufferObjectUsage usageIn = vbo_usage_stream, const VertexIndex * indices = staticIndexList, const unsigned int indicesCount = 0) throw (std::exception&);
        VertexBufferObject(const Vertex * vertices,
                           const unsigned int count,
                           VertexBufferObjectUsage usageIn = vbo_usage_stream,
                           IndexGenerator * = &stripQuadIndexGenerator); // Does not take ownership of indexGenerator: make sure it is in scope!
                           // std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
        ~VertexBufferObject();
        
        int getSize()const { return vertexCount; }
        int getIndexCount()const { return indicesCount; }
        void render()const;
        void renderRegion(unsigned int vertexOffset, size_t indicesToRender)const; // _DEBUG std::out_of_range
                   
        void update(const Vertex * vertices); // MUST be same size as returned by getSize(), i.e. as set up with constructor or setBuffer
        
        // if index count is zero, it is assumed to be 6/4 * the size of vertices to account for degenerate strips between quads
        void setBuffer(const Vertex * vertices, const unsigned int count, IndexGenerator * = new StripQuadIndexGenerator()); //_DEBUG std::invalid_argument
        void updateRegion(const unsigned int regionStart, const Vertex * vertices, unsigned int verticesSize);//_DEBUG std::out_of_range, _DEBUG std::invalid_argument

        bool isUsingTriangleStrips()const;
        bool isUsingQuads()const;
   
};


}		//	visen
}		//	aab
#endif	//	AAB_VISEN_VERTEX_BUFFER_OBJECT_CLASS




