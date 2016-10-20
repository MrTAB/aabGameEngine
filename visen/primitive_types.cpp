/**
*
*	primitive_types.cpp
*
**/

#include"primitive_methods.hpp"
#include"primitive_types.hpp"
#include"render_state.hpp"
namespace aab	{
namespace visen	{
 
void Panel::internalRender()
{
    fill = true;
    if (fill)
    {
        if (usingColor)
        {
            fillColor.apply();
        }
        drawSolidPanel(left, bottom, right, top);
    }
    if(usingColor)
    {
        color.apply();
    }
    drawPanel(left, bottom, right, top);
}

void Panel::render()
{
    if (useTexturing)
    {        
        internalRender();
    }
    else
    {
        RenderState::disableTexturing();
        internalRender();
        RenderState::enableTexturing();
    }
    

}
    
}		//	visen
}		//	aab
