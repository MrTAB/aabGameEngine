
/**
*
*	index_generator.hpp
*
*   Used to generate indices for a vertex buffer object for example.
*
**/

#if !defined(AAB_VISEN_INDEX_GENERATOR_CLASS)
#define AAB_VISEN_INDEX_GENERATOR_CLASS
#include<vector>
#include<cstdint>
namespace aab	{
namespace visen	{

typedef uint32_t VertexIndex;

// using degenerate triangle strips,
// n vertices means for every 4 vertices there are an extra 2 vertices
// number of indices = n + 2*(n/4) = 6n/4

// for indices i, where vertices come in a groups of 4
// number of vertices = 4/6 * i


// static list of indices for degenerate triangle strips
#define VISEN_MAX_STATIC_INDEX 384
extern VertexIndex staticIndexList[VISEN_MAX_STATIC_INDEX];

/*
namespace triangle_strip_quads
{
    
    inline unsigned int indicesNeededForVertices (const unsigned int n)
    {
        return 6*n/4;
    }

    inline unsigned int verticesNeededForIndices (const unsigned int i)
    {
        return 4*i/6;
    }

}
*/

class IndexGenerator
{
    public:
    
    virtual ~IndexGenerator()
    {
        // do nothing //
    };
    
    virtual void generateIndices(std::vector<VertexIndex>&indexVector,const unsigned int quadCount,unsigned int&renderType) = 0;
    
    virtual unsigned int getIndexValue(unsigned int index) = 0;
    virtual unsigned int getValuesFirstIndex(unsigned int value) = 0;
    virtual unsigned int getObjectIndexFromStartingValue(unsigned int value) = 0;    
    
    virtual unsigned int verticesPerObject() = 0;
    virtual unsigned int indicesPerObject() = 0;
    
    virtual unsigned int trailingDegenerates() = 0;
};

//Strip Quads are quads built using two triangles each, as a TRIANGLE_STRIP: This generates the appropriate indices while also
//producing indices to separate each quads, producing degenerate triangles between each quad.
class StripQuadIndexGenerator: public IndexGenerator
{
    public:
    
    void generateIndices(std::vector<VertexIndex>&indexVector,const unsigned int quadCount,unsigned int&renderType);
    
    unsigned int getIndexValue(unsigned int index);
    unsigned int getValuesFirstIndex(unsigned int value);
    unsigned int getObjectIndexFromStartingValue(unsigned int value);
    unsigned int verticesPerObject(){ return 4; }
    unsigned int indicesPerObject(){ return 6; }
    unsigned int trailingDegenerates(){ return 2; }
};
extern StripQuadIndexGenerator stripQuadIndexGenerator;

// Generates indices for quads as a QUADS, but using Strip Quads.
// They have a different ordering, and so the indices need to be re-ordered
/* to be tested:
class StripQuadAsQuadIndexGenerator: public IndexGenerator
{
    public:
    
    void generateIndices(std::vector<VertexIndex>&indexVector,const unsigned int quadCount,unsigned int&renderType);
    
    unsigned int getIndexValue(unsigned int index);
    unsigned int getValuesFirstIndex(unsigned int value);
};*/

// Generates indices for quad strip as a QUAD_STRIP, using standard counter clockwise Quads,, e.g. CCWQuads
class QuadsIndexGenerator: public IndexGenerator
{
    public:
    
    void generateIndices(std::vector<VertexIndex>&indexVector,const unsigned int quadCount,unsigned int&renderType);
    
    unsigned int getIndexValue(unsigned int index);
    unsigned int getValuesFirstIndex(unsigned int value);
    unsigned int getObjectIndexFromStartingValue(unsigned int value);
    unsigned int verticesPerObject(){ return 4; }
    unsigned int indicesPerObject(){ return 4; }
    unsigned int trailingDegenerates(){ return 0; }
};
extern QuadsIndexGenerator quadsIndexGenerator;

/*
void generateStripQuadIndices(std::vector<VertexIndex>&indexVector,const unsigned int quadCount,unsigned int&renderType);


void generateStripQuadAsQuadIndices(std::vector<VertexIndex>&indexVector,const unsigned int quadCount,unsigned int&renderType);


void generateQuadsIndices(std::vector<VertexIndex>&indexVector,const unsigned int quadCount,unsigned int&renderType);
//Define an Index Generator? Must build a vector of indices to match quadCount quads, and return the render type to be used by element drawing procedure.
//typedef void (*IndexGenerator)(std::vector<VertexIndex>&indexVector,const unsigned int quadCount, unsigned int&renderType);


unsigned int getStripQuadIndexValue(unsigned int index);
unsigned int getStripQuadValuesFirstIndex(unsigned int value);
unsigned int getQuadsIndexValue(unsigned int index);
unsigned int getQuadsValuesFirstIndex(unsigned int value);
*/


}		//	visen
}		//	aab
#endif	//	AAB_VISEN_INDEX_GENERATOR_CLASS




