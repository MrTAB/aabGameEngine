/**
*
*	panel.hpp
*
*	Panel: an AxisAlignedBoundingBox (or rather Window aligned bounding box)
*
**/

#if !defined(AAB_GEOMETRY_PANEL_CLASS)
#define AAB_GEOMETRY_PANEL_CLASS
#include"../types/maybe.hpp"
#include"point.hpp"
#include<cmath>
//#include<exception>
#include<algorithm>
namespace aab	{
namespace geometry{



struct Panel
{

	float left, bottom, right, top;

    /*
	explicit Panel () : left (0), bottom (0), right (0), top (0)
	{
		// nothing //
	}

	explicit Panel (float left, float bottom, float right, float top)
	{
		set (left, bottom, right, top);
	}*/

    inline bool operator == (const Panel other)
    {
        using floats::compare;
        return compare(left,other.left) && compare(bottom,other.bottom) && compare(right,other.right) && compare(top,other.top);
    }
    
	void set (float left, float bottom, float right, float top)
	{
		this-> left		= left;
		this-> bottom	= bottom;
		this-> right	= right;
		this-> top		= top;

        validate();
	}
	
	void validate ()
	{
		if (left > right)
		{
			std::swap (this-> left, this-> right);
		}

		if (bottom > top)
		{
			std::swap (this-> bottom, this-> top);
		}
	}
	

	float getLeft () const
	{
		return left;
	}

	float getBottom () const
	{
		return bottom;
	}

	float getRight () const
	{
		return right;
	}

	float getTop () const
	{
		return top;
	}
	
	float getWidth () const
	{
	    return right-left;
	}
	
	float getHeight () const
	{
	    return top - bottom;
	}
	
	float getArea () const
	{
        return (right - left) * (top - bottom);
	}
	
	float getX() const
	{
	    return (right + left)/2;
	}
	
	float getY() const
	{
	    return (top + bottom)/2;
	}
	
	void moveTo(const float xIn, const float yIn)
	{
	    const float dx = xIn - getX();
	    const float dy = yIn - getY();
	    left += dx;
	    right += dx;
	    top += dy;
	    bottom += dy;
	}
	
	void move(const float dx, const float dy)
	{
	    left += dx;
	    right += dx;
	    top += dy;
	    bottom += dy;
	}
	
	void setWidth(const float widthIn)
	{
	    //if (widthIn >= 0)
	    {
	        //left = (right + left)/2.0f - widthIn/2.0f;
	        //right = left + widthIn;
            const float x = getX();
	        left = x - widthIn/2.0f;
	        right = x + widthIn/2.0f;
	    }
	    //else
	    {
	        //left = (right + left)/2.0f + widthIn/2.0f;
	       // right = left - widthIn;
	    }
	}
	
	void setHeight(const float heightIn)
	{
	    //if (heightIn >= 0)
	    {
	        //bottom = (top + bottom)/2.0f - heightIn/2.0f;
	        //top = bottom + heightIn;
	        const float y = getY();
	        bottom = y - heightIn/2.0f;
	        top = y + heightIn/2.0f;
	    }
	    //else
	    {
	        //bottom = (top + bottom)/2.0f + heightIn/2.0f;
	        //top = bottom - heightIn;
	    }
	}


	Point getCorner (const int index) const
	{
		// usefull for cycling through corners.
		switch (index)
		{

			case 1 :
			{
				return makePoint (right, bottom);
				break;
			}
			case 2 :
			{
				return makePoint (right, top);
				break;
			}
			case 3 :
			{
				return makePoint (left, top);
				break;
			}
			case 0 : default :
			{
				return makePoint (left, bottom);
				break;
			}
		}
	}

	bool isPointInside (const Point p) const
	{
		if (p.getX () < getLeft () || p.getX () > getRight ())
		{
			return false;
		}

		if (p.getY () < getBottom () || p.getY () > getTop ())
		{
			return false;
		}

		return true;
	}

	bool intersects (const Panel p) const
	{
		if (p.getLeft () > getRight () || getLeft () > p.getRight ())
		{
			return false;
		}

		if (p.getBottom () > getTop () || getBottom () > p.getTop ())
		{
			return false;
		}

		return true;
	}

	aab::types::Maybe<Panel> getIntersection (const Panel p) const
	{
		Panel intersection;

		if (! intersects (p))
		{
			return false;
		}

		intersection.set (	std::max (getLeft	(), p.getLeft	()),
							std::max (getBottom	(), p.getBottom	()),
							std::min (getRight	(), p.getRight	()),
							std::min (getTop	(), p.getTop	()));

		return intersection;
	}


};



inline Panel makePanel (const float left, const float bottom, const float right, const float top)
{
    Panel p = {left, bottom, right, top};
    return p;
}


}	// geometry
}	// aab
#endif // AAB_GEOMETRY_PANEL_CLASS







