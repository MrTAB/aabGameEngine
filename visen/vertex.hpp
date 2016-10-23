/**
*
*	vertex.hpp
*
*   Provides formats for vertices and a definition for the default vertex format
*   used by the library
*
**/

#if !defined(AAB_VISEN_VERTEX_CLASS)
#define AAB_VISEN_VERTEX_CLASS
#include"color.hpp"
#include<geometry/point.hpp>
namespace aab	{
namespace visen	{
    
typedef aab::geometry::Point Position;
typedef aab::geometry::Point TextCoordf;

// Order of descriptions is always position, texture, colour

struct Vertex2f2f4ub   // {float,float, float,float, byte,byte,byte,byte}
{
    Position position;
    TextCoordf textCoord;
    Colorub color;
    
    
    
    /*void set(float x, float y, float tx, float ty, Colorub colorIn = aab::visen::Colorub::white )
    {
        position.x = x;position.y = y;        
        textCoord.x = tx;textCoord.y = ty; 
        color = colorIn;
    }*/
    
    inline static Vertex2f2f4ub zero()
    {
        Vertex2f2f4ub vzero = {0,0,0,0,aab::visen::Colorub::white};
        return vzero;
    }
    
    
    
};

inline void setVertex(Vertex2f2f4ub&v,float x, float y, float tx, float ty, Colorub colorIn = aab::visen::Colorub::white )
{
    v.position.x = x;
    v.position.y = y;        
    v.textCoord.x = tx;
    v.textCoord.y = ty; 
    v.color = colorIn;
}
    
struct Vertex2f2f4f
{
    Position position;
    TextCoordf textCoord;
    Colorf color;
};

struct Vertex2f2f
{
    Position position;
    TextCoordf textCoord;
};

struct Vertex2f_4ub
{
    Position position;
    Colorub color;
};

struct Vertex2f_4f
{
    Position position;
    Colorf color;
};


// nominal vertex includes everything with a balance between efficiency and speed.

typedef Vertex2f2f4ub Vertex;


}		//	visen
}		//	aab
#endif //AAB_VISEN_VERTEX_CLASS
