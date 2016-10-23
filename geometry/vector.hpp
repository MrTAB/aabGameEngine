/**
*
*	vector.hpp
*
*   Simple two dimensional float vector
**/

#if !defined(AAB_GEOMETRY_VECTOR_CLASS)
#define AAB_GEOMETRY_VECTOR_CLASS
#include"floats.hpp"
#include"../maths/constants.hpp"
//#include<cmath>
namespace aab	{
namespace geometry{



struct Vector
{
    float x, y;

    /*
    Forgoed for implicit {} - use makeVector(x,y)
	explicit Vector () : x (0), y (0)
	{
		// nothing //
	}

	explicit Vector (float x, float y) : x (x), y (y)
	{
		// nothing //
	}
	*/

	//implicit Vector (const Vector &) { etc;
	//implicit Vector & operator == (const Vector& other);

    float operator[](const int index) const
    {
        return (index?y:x);
    }
    
    float & operator[](const int index)
    {
        return (index?y:x);
    }   
    
	bool operator == (const Vector & other) const
	{
		return floats::compare (x, other.x) && floats::compare (y, other.y);
	}

	bool operator != (const Vector & other) const
	{
		return ! operator == (other);
	}

	void set (float x_in, float y_in)
	{
		this-> x = x_in;
		this-> y = y_in;
	}
	
	void setPolar (float length, float radians)
	{
	    this-> x = length * std::cos(radians);
	    this-> y = length * std::sin(radians);
	}
	
	void setAngle(float radians)
	{
	    setPolar (getLength(),radians);
	}

	void normalize ()
	{
		float length = getLength ();

		x /= length;
		y /= length;
	}

	void setLength (float length)
	{
		float modifier = length / getLength ();

		x *= modifier;
		y *= modifier;
	}

	float getLength () const
	{
		return std::sqrt (getLengthSquared ());
	}
	
	void scale(const float s)
	{
	    x *= s;
	    y *= s;
	}
	
	void scale(const float sx, const float sy)
	{
	    x *= sx;
	    y *= sy;
	}

	float getLengthSquared () const
	{
		return x * x + y * y;
	}

	float getX () const
	{
		return x;
	}

	float getY () const
	{
		return y;
	}

	Vector & operator += (const Vector& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector & operator -= (const Vector& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector operator + (const Vector& other) const
	{
		return Vector (*this) += other;
	}

	Vector operator - (const Vector& other) const
	{
		return Vector (*this) -= other;
	}
	
	bool operator > (const Vector& other) const
	{
	    return getLengthSquared() > other.getLengthSquared();
	}
	
	bool operator < (const Vector& other) const
	{
	    return getLengthSquared() < other.getLengthSquared();
	}
	
	bool equalLengths(const Vector& other) const
	{
	    return floats::compare(getLengthSquared(),other.getLengthSquared());
	}

    Vector & getLargest(Vector& other)
    {   
        if(getLengthSquared() > other.getLengthSquared())
        {
            return *this;
        }
        else
        {
            return other;
        }
    }
    
    Vector & getSmallest(Vector& other)
    {   
        if(getLengthSquared() < other.getLengthSquared())
        {
            return *this;
        }
        else
        {
            return other;
        }
    }
    
	void rotate (float radians)
	{
		float ox = x, oy = y;
		float cosA = std::cos (radians);
		float sinA = std::sin (radians);

		x = ox * cosA + oy * sinA;
		y = - ox * sinA + oy * cosA;
	}
	
	Vector operator - ()const
	{
	    Vector v = {-x,-y};
	    return v;
	}
	
	void blendTowards(const Vector& other, float blend)
	{
	    x = blend*other.x + (1.0f-blend)* x;
	    y = blend*other.y + (1.0f-blend)* y;
	}
	
	Vector blendedTowards(const Vector& other, float blend)
	{
	    Vector v = {blend*other.x + (1.0f-blend)* x, blend*other.y + (1.0f-blend)* y};
	    return v;
	}
	
	void flip()
	{
	    x = -x;
	    y = -y;
	}
	
	float getAngle()const
	{
	    return std::atan2(y, x);
	}
	
	float dot(const Vector& other)const
	{
	    return x*other.x + y*other.y;
	}
	
	bool isZero()const
	{
	    return zero() == *this;
	}
	
	bool isNormalized()const
	{
	    return floats::compare(getLengthSquared(),1.0f);
	}
	
	bool arePerpendicular(const Vector& other)const
	{
	    return floats::isZero(dot(other));
	}
	
	static Vector zero()
	{
	    Vector v = {0,0};
	    return v;
	}
	
	void turnYX()// efficiently turns vector pi/2 radians in the direction of the y axis to x axis
	{
	    set(y,-x);
	}
	void turnXY()// efficiently turns vector pi/2 radians in the direction of the x axis to y axis
	{
	    set(-y,x);
	}
	
	void flipAboutX()
	{
	    y = -y;
	}
	
    void flipAboutY()
	{
	    x = -x;
	}
	


    //
    //  Methods for determining the "half" that a normal is within
    //

    bool inRightHalf ()const 
    {
        return x > 0;
    }

    bool inLeftHalf ()const 
    {
        return x < 0;
    }

    bool inTopHalf ()const 
    {
        return y < 0;
    }

    bool inBottomHalf ()const 
    {
        return y > 0;
    }

    //
    //  Methods for determining the quadrant that a normal is within (axis aligned)
    //

    bool inToprightQuadrant ()const 
    {
        return y <= 0 && x > 0;//y < 0 && x >= 0;
    }

    bool inBottomrightQuadrant ()const 
    {
        return y >= 0 && x > 0;
    }

    bool inBottomleftQuadrant ()const 
    {
        return y > 0 && x <= 0;
    }

    bool inTopleftQuadrant ()const 
    {
        return y <= 0 && x < 0;
    }

    //
    //  Methods for determining the quadrant that a normal is within (offset by pi/4)
    //

    bool inRightQuadrant ()const 
    {
        //return y >= -aab::maths::invsqrt_2 && y < aab::maths::invsqrt_2 && x > aab::maths::invsqrt_2;
        return x > aab::maths::invsqrt_2;
    }

    bool inBottomQuadrant ()const 
    {
        //return y > aab::maths::invsqrt_2 && x > -aab::maths::invsqrt_2 && x <= aab::maths::invsqrt_2;
        return y > aab::maths::invsqrt_2;
    }

    bool inLeftQuadrant ()const 
    {
        //return y > -aab::maths::invsqrt_2 && y <= aab::maths::invsqrt_2 && x < -aab::maths::invsqrt_2;
        return x < -aab::maths::invsqrt_2;
    }

    bool inTopQuadrant ()const 
    {
        //return y < -aab::maths::invsqrt_2 && x >= -aab::maths::invsqrt_2 && x < aab::maths::invsqrt_2;
        return y < -aab::maths::invsqrt_2;
    }

    // "on" methods : checks edge with certainty
    bool onTopQuadrant ()const 
    {
        //return y < -aab::maths::invsqrt_2 && x >= -aab::maths::invsqrt_2 && x < aab::maths::invsqrt_2;
        return y < -aab::maths::invsqrt_2 || floats::compare (y,-aab::maths::invsqrt_2);
    }



    //
    //  Methods for determining the Octant that a normal is within
    //
    //  Octants are labelled 0 to 7 as the angle of normals within that octant increase
    //  i.e.
    /*
            5   6
            
        4           7
        
        3           0
        
            2   1
    */


    bool inOctant0 ()const 
    {
        return y >= 0 && x > aab::maths::invsqrt_2;
    }

    bool inOctant1 ()const 
    {
        return y >= aab::maths::invsqrt_2 && x > 0;
    }

    bool inOctant2 ()const 
    {
        return y > aab::maths::invsqrt_2 && x <= 0;
    }

    bool inOctant3 ()const 
    {
        return y > 0 && x <= -aab::maths::invsqrt_2;
    }
    bool inOctant4 ()const 
    {
        return y <= 0 && x < -aab::maths::invsqrt_2;
    }

    bool inOctant5 ()const 
    {
        return y <= -aab::maths::invsqrt_2 && x < 0;
    }

    bool inOctant6 ()const 
    {
        return y < -aab::maths::invsqrt_2 && x >= 0;
    }

    bool inOctant7 ()const
    {
        return y < 0 && x >= aab::maths::invsqrt_2;
    }
    
    bool inOctant(int number)
    {
        switch(number)
        {
            case 0: return inOctant0();
            case 1: return inOctant1();
            case 2: return inOctant2();
            case 3: return inOctant3();
            case 4: return inOctant4();
            case 5: return inOctant5();
            case 6: return inOctant6();
            case 7: return inOctant7();
            default: return false;
        }
    }

};

inline Vector makeVector (const float x = 0, const float y = 0)
{
    Vector v = {x,y};
    return v;
}


}	// geometry
}	// aab
#endif // AAB_GEOMETRY_VECTOR_CLASS

