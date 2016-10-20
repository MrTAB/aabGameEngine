/**
*
*	point.hpp
*
**/

#if !defined(AAB_GEOMETRY_POINT_CLASS)
#define AAB_GEOMETRY_POINT_CLASS
#include"floats.hpp"
namespace aab	{
namespace geometry{


struct Point
{
	float x, y;

    //implicit - use of {}
	//implicit Point (const Point&);
	//implicit Point& operator = (const Point&);

    inline
	bool operator == (const Point & other) const
	{
		return floats::compare(x, other.x) && floats::compare(y, other.y);
	}

    inline
	bool operator != (const Point & other) const
	{
		return ! operator == (other);
	}

    inline
	void move (const float dx, const float dy)
	{
		x += dx;
		y += dy;
	}
	
	inline
	void set (const float ix, const float iy)
	{
        x = ix; y = iy;
	}
	
	inline
	float distance(const Point other)const
	{
	    return std::sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y));
	}

	inline
	float distanceSquared(const Point other)const
	{
	    return (x-other.x)*(x-other.x)+(y-other.y)*(y-other.y);
	}	
	
	// const versions of the fields, although you're better of just passing a const Point
	
	inline
	float getX()const { return x; }
	
	inline
	float getY()const { return y; }
	
	
    // matrix must have 4 elements
    //|a b| |x| = |ax+by|
    //|c d| |y|   |cd+dy|
    inline void transform (const float * matrix2D)
    {
        float ox = x;
        x = matrix2D[0]*ox+matrix2D[1]*y;
        y = matrix2D[2]*ox+matrix2D[3]*y;
    }
    
    Point operator+(const Point & other)const
    {
        Point result = {x + other.x, y + other.y};
        return result;
    }
    
    /*
    Point operator*(const float k)const
    {
        Point result = {k*x, k*y};
        return result;
    }
    */
    
    /* such methods should be grouped into one unit that can be included or excluded whole.

	*/
};

// using this instead of constructors allows initialiser lists (edit: old fashioned way)
inline Point makePoint(const float x, const float y)
{
    Point p = {x,y};
    return p;
}

inline Point operator*(const float k, const Point & point)
{
    Point result = {k*point.x, k*point.y};
    return result;
}


}	// geometry
}	// aab
#endif // AAB_GEOMETRY_POINT_CLASS

