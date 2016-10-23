/**
*
*	quad.hpp
*
*   These quads represent quads composed of vertices for rendering and
*   transformtion.
*
*   They are particularly useful for sprites and sprite batches.
**/

#if !defined(AAB_VISEN_QUAD_CLASS)
#define AAB_VISEN_QUAD_CLASS
#include"vertex.hpp"
#include<utility>
namespace aab	{
namespace visen	{
 
/*
* a quad stuctured for use in Triangle Strips
*
*/

//template <typename VertexT>
struct StripQuad//X
{
    typedef Vertex VertexT;
    
    /*
    *   These should always be modified such that the angles of the corners are 90 degrees.
    *   They should also operate such that they can be drawn as a triaingle strip
    *   Other behaviour can be used but there is no guarantee that all the operations will work.
    */
    VertexT v00;
    VertexT v01;
    VertexT v10;
    VertexT v11;
    
    static int get00Position() { return 0; };
    static int get01Position() { return 1; };
    static int get10Position() { return 2; };
    static int get11Position() { return 3; };
    
    inline VertexT * begin() { return &v00; }
    inline VertexT * end() { return &v11 + 1; }
    
    inline const VertexT * begin() const { return &v00; }
    inline const VertexT * end() const { return &v11 + 1; }

    /*
    VertexT & first() { return v00; }
    VertexT & second() { return v01; }
    VertexT & third() { return v10; }
    VertexT & fourth() { return v11; }
    VertexT first() const { return v00; }
    VertexT second() const { return v01; }
    VertexT third() const { return v10; }
    VertexT fourth() const { return v11; }
    */
    
    inline void setPosition (const float x, const float y, const float hw, const float hh)
    {
        v00.position.set(x -hw,y -hh);
        v01.position.set(x -hw,y +hh);
        v10.position.set(x +hw,y -hh);
        v11.position.set(x +hw,y +hh);
    }
    
    inline void setCorners(float nwx, float nwy, float swx, float swy, float sex, float sey, float nex, float ney)
    {
        v00.position.set(nwx, nwy);
        v01.position.set(swx, swy);        
        v10.position.set(nex, ney);
        v11.position.set(sex, sey);
    }
    
    // Use this when dealing with something that has to be rasterised such as a 2d sprite
    //otherwise there might be clipping of a line of pixels during rasterisation (for odd width/height sprites)
    inline void setIntAlignedPosition (float x, float y, const float full_w, const float full_h)
    {
        const float hw = full_w/2;
        const float hh = full_h/2;
        float phw = hw;
        float phh = hh;

        /*
        if (static_cast<int>(full_w)%2)
        {
            //phw += 1.0f;
            //x += 0.5f;
        }
        if (static_cast<int>(full_h)%2)
        {
            //phh += 1.0f;
            //y += 0.5f;
        }
        */
    
        v00.position.set(x -hw,y -hh);
        v01.position.set(x -hw,y +phh);
        v10.position.set(x +phw,y -hh);
        v11.position.set(x +phw,y +hh);
    }
    
    void move (const float x, const float y)
    {
        moveX(x);moveY(y);
    }
    
    void moveX(const float dx)
    {
        v00.position.x += dx;
        v01.position.x += dx;
        v10.position.x += dx;
        v11.position.x += dx;
    }
    
    void moveY (const float dy)
    {
        v00.position.y += dy;
        v01.position.y += dy;
        v10.position.y += dy;
        v11.position.y += dy;
    }
    
    //relies on object having quad shape.
    void setX (const float x)
    {
        moveX(x - guessX());
    }
    
    //relies on object having quad shape.
    void setY (const float y)
    {
        moveY(y - guessY());
    }
    
    //relies on object having quad shape.
    void setPosition (const float x, const float y)
    {
        setX(x);setY(y);
    }
    

    /*
    * good method for updating rotated sprite quad data
    */
    inline void setRotated (const float x, const float y, const float hw, const float hh, const float sinr, const float cosr)
    {
        v00.position.set(x +(-cosr*hw+sinr*hh),y +(-sinr*hw-cosr*hh));
        v01.position.set(x +(-cosr*hw-sinr*hh),y +(-sinr*hw+cosr*hh));
        v10.position.set(x +(cosr*hw+sinr*hh),y +(sinr*hw-cosr*hh));
        v11.position.set(x +(cosr*hw-sinr*hh),y +(sinr*hw+cosr*hh));
    }
    inline void setRotated (const float x, const float y, const float hw, const float hh, const float radians)
    {
        const float sinr = std::sin(radians);
        const float cosr = std::cos(radians);
        
        v00.position.set(x +(-cosr*hw+sinr*hh),y +(-sinr*hw-cosr*hh));
        v01.position.set(x +(-cosr*hw-sinr*hh),y +(-sinr*hw+cosr*hh));
        v10.position.set(x +(cosr*hw+sinr*hh),y +(sinr*hw-cosr*hh));
        v11.position.set(x +(cosr*hw-sinr*hh),y +(sinr*hw+cosr*hh));
    }
    
    inline void setIntAlignedRotated (const float x, const float y, const float full_w, const float full_h, const float radians)
    {
        const float hw = full_w/2;
        const float hh = full_h/2;
        const float sinr = std::sin(radians);
        const float cosr = std::cos(radians);
        float phw = hw;
        float phh = hh;
        /*
        if (static_cast<int>(full_w)%2)
        {
            //phw += 1.0f;
        }
        if (static_cast<int>(full_h)%2)
        {
           // phh += 1.0f;
        }
        */
    
        v00.position.set(x +(-cosr*hw+sinr*phh),y +(-sinr*hw-cosr*hh));
        v01.position.set(x +(-cosr*hw-sinr*hh),y +(-sinr*hw+cosr*phh));
        v10.position.set(x +(cosr*phw+sinr*phh),y +(sinr*phw-cosr*hh));
        v11.position.set(x +(cosr*phw-sinr*hh),y +(sinr*phw+cosr*phh));
    }
    
    inline void setColor (const Colorub color)
    {
        v00.color = v01.color = v10.color = v11.color = color;
    }
    
    inline void setColorNotAlpha(const Colorub color)
    {
        v00.color.setRGB(color);
        v01.color = v10.color = v11.color = v00.color;
    }
    
    inline void setAlpha (const Colorub::byte_t alpha)
    {
        v00.color.setAlpha(alpha);
        v10.color.setAlpha(alpha);
        v01.color.setAlpha(alpha);
        v11.color.setAlpha(alpha);
    }
    
    inline void setDefaultTextureCoordinates ()
    {
        v00.textCoord.set(0,0);
        v01.textCoord.set(0,1);
        v10.textCoord.set(1,0);
        v11.textCoord.set(1,1);
    }
    
    inline void spanTextureCoordinates (const float x, const float y, const float width, const float height)
    {
        v00.textCoord.set(x,y);
        v01.textCoord.set(x,y + height);
        v10.textCoord.set(x + width,y);
        v11.textCoord.set(x + width,y + height);
    }
    
    inline void setTextureCoordinates (const float tx, const float ty, const float wfrac, const float hfrac)
    {
        v00.textCoord.set(tx ,ty -hfrac);
        v01.textCoord.set(tx ,ty);
        v11.textCoord.set(tx +wfrac,ty);
        v10.textCoord.set(tx +wfrac,ty -hfrac);
        
    }
    
    inline void setTexturePanel(const float x1, const float y1, const float x2, const float y2)
    {
        v00.textCoord.x = v01.textCoord.x = x1; 
        v00.textCoord.y = v10.textCoord.y = y1;
        v10.textCoord.x = v11.textCoord.x = x2; 
        v01.textCoord.y = v11.textCoord.y = y2;
    }

    void hFlipTexture()
    {
        std::swap(v00.textCoord,v10.textCoord);
        std::swap(v01.textCoord,v11.textCoord);        
    }
    
    void vFlipTexture()
    {
        std::swap(v00.textCoord,v01.textCoord);
        std::swap(v10.textCoord,v11.textCoord);
    }
    
    void rightTurnTexture()
    {
        aab::visen::TextCoordf v00Tex = v00.textCoord;
        v00.textCoord = v01.textCoord;
        v01.textCoord = v11.textCoord;
        v11.textCoord = v10.textCoord;
        v10.textCoord = v00Tex;
    }
    
    void halfTurnTexture()
    {
        std::swap(v00.textCoord,v11.textCoord);
        std::swap(v01.textCoord,v10.textCoord);
    }
    
    void threeQuarterTurnTexture()
    {
        aab::visen::TextCoordf v00Tex = v00.textCoord;
        v00.textCoord = v10.textCoord;
        v10.textCoord = v11.textCoord;
        v11.textCoord = v01.textCoord;
        v01.textCoord = v00Tex;
    }
    
    inline float guessX()const
    {
        return (v00.position.x + v11.position.x)/2.0;
    }

    inline float guessY()const
    {
        return (v00.position.y + v11.position.y)/2.0;
    }
    
    inline float guessWidth() const
    {
        return v00.position.distance(v10.position);
    }
    
    inline float guessHeight() const
    {
        return v00.position.distance(v01.position);
    }
    
    inline float guessAngle() const
    {
        return std::atan2(v10.position.y-v00.position.y, v10.position.x-v00.position.x);
    }
    
    /*
    inline float calculateX()const
    {
        return (v00.x + v01.x + v10.x + v11.x)/4.0;
    }
    inline float calculateY()const
    {
        return (v00.y + v01.y + v10.y + v11.y)/4.0;
    }
    */
    
    inline void translate (const float x, const float y)
    {
        v00.position.move(x,y);
        v01.position.move(x,y);
        v10.position.move(x,y);
        v11.position.move(x,y);
    }
    
    // matrix must have 4 elements
    //|a b| |x| = |ax+by|
    //|c d| |y|   |cd+dy|
    inline void transform (const float * matrix2D)
    {
        v00.position.transform(matrix2D);
        v01.position.transform(matrix2D);
        v10.position.transform(matrix2D);
        v11.position.transform(matrix2D);
    }
        
    inline void scale (const float sx, const float sy)
    {
        const float x = guessX();
        const float y = guessY();
        
        /*translate(-x,-y);
        float matrix[4] = {sx,0,0,sy};
        transform(matrix); 
        translate(x,y);*/
   
        v00.position.set(sx*(v00.position.x-x)+x,sy*(v00.position.y-y)+y);
        v01.position.set(sx*(v01.position.x-x)+x,sy*(v01.position.y-y)+y);
        v10.position.set(sx*(v10.position.x-x)+x,sy*(v10.position.y-y)+y);
        v11.position.set(sx*(v11.position.x-x)+x,sy*(v11.position.y-y)+y);
    }
    
    inline void rotate (const float radians)
    {
        const float sinr = std::sin(radians);
        const float cosr = std::cos(radians);
        float x = guessX();
        float y = guessY();
        
        v00.position.set( x+cosr*(v00.position.x-x)-sinr*(v00.position.y-y), y+sinr*(v00.position.x-x)+cosr*(v00.position.y-y));
        v01.position.set( x+cosr*(v01.position.x-x)-sinr*(v01.position.y-y), y+sinr*(v01.position.x-x)+cosr*(v01.position.y-y));
        v10.position.set( x+cosr*(v10.position.x-x)-sinr*(v10.position.y-y), y+sinr*(v10.position.x-x)+cosr*(v10.position.y-y));
        v11.position.set( x+cosr*(v11.position.x-x)-sinr*(v11.position.y-y), y+sinr*(v11.position.x-x)+cosr*(v11.position.y-y));

        /*
        translate(-x,-y);
        float matrix[4] = {cosr,-sinr,sinr,cosr};
        transform(matrix); 
        translate(x,y);
        */
    }
    
    inline void quarterTurn ()
    {
        float x = guessX();
        float y = guessY();
        
        v00.position.set(-(v00.position.y-y)+x,(v00.position.x-x)+y);
        v01.position.set(-(v01.position.y-y)+x,(v01.position.x-x)+y);
        v10.position.set(-(v10.position.y-y)+x,(v10.position.x-x)+y);
        v11.position.set(-(v11.position.y-y)+x,(v11.position.x-x)+y);
    }
    
    inline void halfTurn ()
    {
        float x = guessX();
        float y = guessY();
        
        v00.position.set(-(v00.position.x-x)+x,-(v00.position.y-y)+y);
        v01.position.set(-(v01.position.x-x)+x,-(v01.position.y-y)+y);
        v10.position.set(-(v10.position.x-x)+x,-(v10.position.y-y)+y);
        v11.position.set(-(v11.position.x-x)+x,-(v11.position.y-y)+y);
    }
    
    inline void threeQuarterTurn ()
    {
        float x = guessX();
        float y = guessY();
        
        v00.position.set((v00.position.y-y)+x,-(v00.position.x-x)+y);
        v01.position.set((v01.position.y-y)+x,-(v01.position.x-x)+y);
        v10.position.set((v10.position.y-y)+x,-(v10.position.x-x)+y);
        v11.position.set((v11.position.y-y)+x,-(v11.position.x-x)+y);
    }
    
    inline void makeZero()
    {
        v00 = v01 = v10 = v11 = Vertex::zero();
    }
    
    
};



    
/*
typedef StripQuadX <Vertex> StripQuad;

struct StripQuadXTemplateCompiler
{
    void useTheTemplates();
};
*/


struct CCWQuad//X
{
    typedef Vertex VertexT;
    
    /*
    *   These should always be modified such that the angles of the corners are 90 degrees.
    *   They should also operate such that they can be drawn as a triaingle strip
    *   Other behaviour can be used but there is no guarantee that all the operations will work.
    */
    VertexT v00;
    VertexT v01;    
    VertexT v11;
    VertexT v10;
    
    static int get00Position() { return 0; };
    static int get01Position() { return 1; };
    static int get11Position() { return 2; };
    static int get10Position() { return 3; };
    
    inline VertexT * begin() { return &v00; }
    inline VertexT * end() { return &v10 + 1; }
    
    inline const VertexT * begin() const { return &v00; }
    inline const VertexT * end() const { return &v10 + 1; }

    /*
    VertexT & first() { return v00; }
    VertexT & second() { return v01; }
    VertexT & third() { return v10; }
    VertexT & fourth() { return v11; }
    VertexT first() const { return v00; }
    VertexT second() const { return v01; }
    VertexT third() const { return v10; }
    VertexT fourth() const { return v11; }
    */
    
    inline void setPosition (const float x, const float y, const float hw, const float hh)
    {
        v00.position.set(x -hw,y -hh);
        v01.position.set(x -hw,y +hh);
        v10.position.set(x +hw,y -hh);
        v11.position.set(x +hw,y +hh);
    }
    

    
    inline void setCorners(float nwx, float nwy, float swx, float swy, float sex, float sey, float nex, float ney)
    {
        v00.position.set(nwx, nwy);
        v01.position.set(swx, swy);        
        v10.position.set(nex, ney);
        v11.position.set(sex, sey);
    }
    
    
    void move (const float x, const float y)
    {
        moveX(x);moveY(y);
    }
    
    void moveX(const float dx)
    {
        v00.position.x += dx;
        v01.position.x += dx;
        v10.position.x += dx;
        v11.position.x += dx;
    }
    
    void moveY (const float dy)
    {
        v00.position.y += dy;
        v01.position.y += dy;
        v10.position.y += dy;
        v11.position.y += dy;
    }
    
    //relies on object having quad shape.
    void setX (const float x)
    {
        moveX(x - guessX());
    }
    
    //relies on object having quad shape.
    void setY (const float y)
    {
        moveY(y - guessY());
    }
    
    //relies on object having quad shape.
    void setPosition (const float x, const float y)
    {
        setX(x);setY(y);
    }
 
    /*
    * good method for updating rotated sprite quad data
    */
    inline void setRotated (const float x, const float y, const float hw, const float hh, const float sinr, const float cosr)
    {
        v00.position.set(x +(-cosr*hw+sinr*hh),y +(-sinr*hw-cosr*hh));
        v01.position.set(x +(-cosr*hw-sinr*hh),y +(-sinr*hw+cosr*hh));
        v10.position.set(x +(cosr*hw+sinr*hh),y +(sinr*hw-cosr*hh));
        v11.position.set(x +(cosr*hw-sinr*hh),y +(sinr*hw+cosr*hh));
    }
    inline void setRotated (const float x, const float y, const float hw, const float hh, const float radians)
    {
        const float sinr = std::sin(radians);
        const float cosr = std::cos(radians);
        
        v00.position.set(x +(-cosr*hw+sinr*hh),y +(-sinr*hw-cosr*hh));
        v01.position.set(x +(-cosr*hw-sinr*hh),y +(-sinr*hw+cosr*hh));
        v10.position.set(x +(cosr*hw+sinr*hh),y +(sinr*hw-cosr*hh));
        v11.position.set(x +(cosr*hw-sinr*hh),y +(sinr*hw+cosr*hh));
    }
    
    inline void setColor (const Colorub color)
    {
        v00.color = v01.color = v10.color = v11.color = color;
    }
    
    inline void setColorNotAlpha(const Colorub color)
    {
        v00.color.setRGB(color);
        v01.color = v10.color = v11.color = v00.color;
    }
    
    inline void setAlpha (const Colorub::byte_t alpha)
    {
        v00.color.setAlpha(alpha);
        v10.color.setAlpha(alpha);
        v01.color.setAlpha(alpha);
        v11.color.setAlpha(alpha);
    }
    
    inline void setDefaultTextureCoordinates ()
    {
        v00.textCoord.set(0,0);
        v01.textCoord.set(0,1);
        v10.textCoord.set(1,0);
        v11.textCoord.set(1,1);
    }
    
    inline void spanTextureCoordinates (const float x, const float y, const float width, const float height)
    {
        v00.textCoord.set(x,y);
        v01.textCoord.set(x,y + height);
        v10.textCoord.set(x + width,y);
        v11.textCoord.set(x + width,y + height);
    }
    
    inline void setTextureCoordinates (const float tx, const float ty, const float wfrac, const float hfrac)
    {
        v00.textCoord.set(tx ,ty -hfrac);
        v01.textCoord.set(tx ,ty);
        v11.textCoord.set(tx +wfrac,ty);
        v10.textCoord.set(tx +wfrac,ty -hfrac);
        
    }
    
    inline void setTexturePanel(const float x1, const float y1, const float x2, const float y2)
    {
        v00.textCoord.x = v01.textCoord.x = x1; 
        v00.textCoord.y = v10.textCoord.y = y1;
        v10.textCoord.x = v11.textCoord.x = x2; 
        v01.textCoord.y = v11.textCoord.y = y2;
    }

    void hFlipTexture()
    {
        std::swap(v00.textCoord,v10.textCoord);
        std::swap(v01.textCoord,v11.textCoord);        
    }
    
    void vFlipTexture()
    {
        std::swap(v00.textCoord,v01.textCoord);
        std::swap(v10.textCoord,v11.textCoord);
    }
    
    void rightTurnTexture()
    {
        aab::visen::TextCoordf v00Tex = v00.textCoord;
        v00.textCoord = v01.textCoord;
        v01.textCoord = v11.textCoord;
        v11.textCoord = v10.textCoord;
        v10.textCoord = v00Tex;
    }
    
    void halfTurnTexture()
    {
        std::swap(v00.textCoord,v11.textCoord);
        std::swap(v01.textCoord,v10.textCoord);
    }
    
    void threeQuarterTurnTexture()
    {
        aab::visen::TextCoordf v00Tex = v00.textCoord;
        v00.textCoord = v10.textCoord;
        v10.textCoord = v11.textCoord;
        v11.textCoord = v01.textCoord;
        v01.textCoord = v00Tex;
    }
    
    inline float guessX()const
    {
        return (v00.position.x + v11.position.x)/2.0;
    }

    inline float guessY()const
    {
        return (v00.position.y + v11.position.y)/2.0;
    }
    
    inline float guessWidth() const
    {
        return v00.position.distance(v10.position);
    }
    
    inline float guessHeight() const
    {
        return v00.position.distance(v01.position);
    }
    
    inline float guessAngle() const
    {
        return std::atan2(v10.position.y-v00.position.y, v10.position.x-v00.position.x);
    }
    
    /*
    inline float calculateX()const
    {
        return (v00.x + v01.x + v10.x + v11.x)/4.0;
    }
    inline float calculateY()const
    {
        return (v00.y + v01.y + v10.y + v11.y)/4.0;
    }
    */
    
    inline void translate (const float x, const float y)
    {
        v00.position.move(x,y);
        v01.position.move(x,y);
        v10.position.move(x,y);
        v11.position.move(x,y);
    }
    
    // matrix must have 4 elements
    //|a b| |x| = |ax+by|
    //|c d| |y|   |cd+dy|
    inline void transform (const float * matrix2D)
    {
        v00.position.transform(matrix2D);
        v01.position.transform(matrix2D);
        v10.position.transform(matrix2D);
        v11.position.transform(matrix2D);
    }
        
    inline void scale (const float sx, const float sy)
    {
        const float x = guessX();
        const float y = guessY();
        
        /*translate(-x,-y);
        float matrix[4] = {sx,0,0,sy};
        transform(matrix); 
        translate(x,y);*/
   
        v00.position.set(sx*(v00.position.x-x)+x,sy*(v00.position.y-y)+y);
        v01.position.set(sx*(v01.position.x-x)+x,sy*(v01.position.y-y)+y);
        v10.position.set(sx*(v10.position.x-x)+x,sy*(v10.position.y-y)+y);
        v11.position.set(sx*(v11.position.x-x)+x,sy*(v11.position.y-y)+y);
    }
    
    inline void rotate (const float radians)
    {
        const float sinr = std::sin(radians);
        const float cosr = std::cos(radians);
        float x = guessX();
        float y = guessY();
        
        v00.position.set( x+cosr*(v00.position.x-x)-sinr*(v00.position.y-y), y+sinr*(v00.position.x-x)+cosr*(v00.position.y-y));
        v01.position.set( x+cosr*(v01.position.x-x)-sinr*(v01.position.y-y), y+sinr*(v01.position.x-x)+cosr*(v01.position.y-y));
        v10.position.set( x+cosr*(v10.position.x-x)-sinr*(v10.position.y-y), y+sinr*(v10.position.x-x)+cosr*(v10.position.y-y));
        v11.position.set( x+cosr*(v11.position.x-x)-sinr*(v11.position.y-y), y+sinr*(v11.position.x-x)+cosr*(v11.position.y-y));

        /*
        translate(-x,-y);
        float matrix[4] = {cosr,-sinr,sinr,cosr};
        transform(matrix); 
        translate(x,y);
        */
    }
    
    inline void quarterTurn ()
    {
        float x = guessX();
        float y = guessY();
        
        v00.position.set(-(v00.position.y-y)+x,(v00.position.x-x)+y);
        v01.position.set(-(v01.position.y-y)+x,(v01.position.x-x)+y);
        v10.position.set(-(v10.position.y-y)+x,(v10.position.x-x)+y);
        v11.position.set(-(v11.position.y-y)+x,(v11.position.x-x)+y);
    }
    
    inline void halfTurn ()
    {
        float x = guessX();
        float y = guessY();
        
        v00.position.set(-(v00.position.x-x)+x,-(v00.position.y-y)+y);
        v01.position.set(-(v01.position.x-x)+x,-(v01.position.y-y)+y);
        v10.position.set(-(v10.position.x-x)+x,-(v10.position.y-y)+y);
        v11.position.set(-(v11.position.x-x)+x,-(v11.position.y-y)+y);
    }
    
    inline void threeQuarterTurn ()
    {
        float x = guessX();
        float y = guessY();
        
        v00.position.set((v00.position.y-y)+x,-(v00.position.x-x)+y);
        v01.position.set((v01.position.y-y)+x,-(v01.position.x-x)+y);
        v10.position.set((v10.position.y-y)+x,-(v10.position.x-x)+y);
        v11.position.set((v11.position.y-y)+x,-(v11.position.x-x)+y);
    }
    
    inline void makeZero()
    {
        v00 = v01 = v10 = v11 = Vertex::zero();
    }
    
    
};




}		//	visen
}		//	aab
#endif //AAB_VISEN_QUAD_CLASS
