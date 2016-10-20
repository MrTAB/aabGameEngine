/**
*
*	primitive_types.hpp
*
**/


#if !defined(AAB_VISEN_PRIMITIVE_TYPES)
#define AAB_VISEN_PRIMITIVE_TYPES
#include"color.hpp"
#include"../geometry/panel.hpp"
namespace aab	{
namespace visen	{
  

// Note: colour may be set by these objects - it will not be reset afterwards.
//Do so manually using color objects.

class Primitive
{
    protected:
    
        bool useTexturing;
        bool fill;
        aab::visen::Colorub color;
        aab::visen::Colorub fillColor;
        bool usingColor;
        
    public:
    
    Primitive():
        useTexturing(false),
        fill(true),
        usingColor(false)
    {
        // do nothing //
    }
    
    virtual void render() = 0;
    
    void setTexturing(bool useTexturingIn)
    {
        useTexturing = useTexturingIn;
    }
    
    void setFill(bool fillIn)
    {
        fill = fillIn;
    }
    
    void setLineColor(aab::visen::Colorub lineColorIn)
    {
        usingColor = true;
        color = lineColorIn;
    }
    
    void setFillColor(aab::visen::Colorub fillColorIn)
    {
        usingColor = true;
        fillColor = fillColorIn;
        fill = true;
    }
    
    aab::visen::Colorub getLineColor()const
    {
        return color;
    }
    
    aab::visen::Colorub getFillColor()const
    {
        return fillColor;
    }
    
    aab::visen::Colorub& accessLineColor()
    {
        return color;
    }
    
    aab::visen::Colorub& accessFillColor()
    {
        return fillColor;
    }
};


class Panel : public Primitive, public aab::geometry::Panel
{
    protected:
    
        void internalRender();
        
    public:
    
    Panel()
    {  
        //do nothing //      
    }
    

    Panel & operator = (const aab::geometry::Panel other)
    {
        left = other.left;
        bottom = other.bottom;
        right = other.right;
        top = other.top;
        return *this;
    }
    
    virtual void render();
};



}		//	visen
}		//	aab
#endif //AAB_VISEN_PRIMITIVE_METHODS
