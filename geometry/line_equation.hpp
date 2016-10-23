/**
*
*	line_equation.hpp
*
*   LineEquation represents a line which is infinite in length, and provides
*   methods for comparing that line to other geometric objects for collision etc
*
**/

#if !defined(AAB_GEOMETRY_LINE_EQUATION_CLASS)
#define AAB_GEOMETRY_LINE_EQUATION_CLASS
#include"../types/maybe.hpp"
#include"panel.hpp"
#include"vector.hpp"
#include"floats.hpp"
#include"line_methods.hpp"
namespace aab	{
namespace geometry{


class LineEquation
{
	private:

		float x, y, c;

	public:

	typedef aab::types::Maybe<float> MaybeFloat;
	typedef aab::types::Maybe<Point> MaybePoint;

	explicit LineEquation ():
		x (0), y (0), c (0)
	{
		// nothing //
	}

	explicit LineEquation (const float xc, const float yc, const float cc):
		x (xc), y (yc), c (cc)
	{
		// nothing //
	}

	explicit LineEquation (const Point p1, const Point p2)
	{
		set (p1, p2);
	}

	//implicit LineEquation::LineEquation (const LineEquation&);
	//implicit LineEquation::LineEquation& operator = (const LineEquation&);

	bool operator == (const LineEquation & other) const
	{
		return floats::compare (x, other.x) && floats::compare (y, other.y) && floats::compare (c, other.c);
	}

	bool operator != (const LineEquation & other) const
	{
		return ! (operator == (other));
	}

	void set (const float xc, const float yc, const float cc)
	{
		x = xc;
		y = yc;
		c = cc;
	}

	void set (const Point p1, const Point p2)
	{
		x = LineMethods::getXCoefficient (p1, p2);
		y = LineMethods::getYCoefficient (p1, p2);
		c = LineMethods::getCCoefficient (p1, p2);
	}


	float getDx () const
	{
		return - y;
	}

	float getDy () const
	{
		return x;
	}

	MaybeFloat getYIntercept () const
	{
		return LineMethods::calculateYIntercept (*this);
	}

	MaybeFloat getGradient () const
	{
		return LineMethods::calculateGradient (*this);
	}


	float getXCoefficient () const
	{
		return x;
	}

	float getYCoefficient () const
	{
		return y;
	}

	float getCCoefficient () const
	{
		return c;
	}

	bool isHorizontal () const
	{
		return floats::isZero (y);
	}

	bool isVertical () const
	{
		return floats::isZero (x);
	}

	template <typename T_Line>
	bool isParallelTo (const T_Line & other) const
	{
		return LineMethods::areParallel (*this, other);
	}


	float calculateXRaw (float y) const
	{
		return LineMethods::calculateXRawFromY (*this, y);
	}

	float calculateYRaw (float x) const
	{
		return LineMethods::calculateYRawFromX (*this, x);
	}

	MaybeFloat calculateX (float y) const
	{
		return LineMethods::calculateXFromY (*this, y);
	}

	MaybeFloat calculateY (float x) const
	{
		return LineMethods::calculateYFromX (*this, x);
	}

	bool isAboveLine (const Point & p) const
	{
		return LineMethods::isPointAboveLine (*this, p);
	}

	bool isBelowLine (const Point & p) const
	{
		return LineMethods::isPointBelowLine (*this, p);
	}

	bool isRightOfLine (const Point & p) const
	{
		return LineMethods::isPointRightOfLine (*this, p);
	}

	bool isLeftOfLine (const Point & p) const
	{
		return LineMethods::isPointLeftOfLine (*this, p);
	}

	bool isOnLine (const Point & p) const
	{
		return LineMethods::isPointOnLine (*this, p);
	}

	float evaluate (const Point & p) const
	{
		return LineMethods::evaluateLinesEquationFor (*this, p);
	}

	template <typename T_Line>
	MaybePoint findLineIntersectionPoint (const T_Line & other) const
	{
		return LineMethods::findLineIntersectionPoint (*this, other);
	}

	template <typename T_Line>
	bool intersectsLine (const T_Line & other) const
	{
		return LineMethods::doLinesIntersect (*this, other);
	}

	template <typename T_LineSegment>
	MaybePoint findLineSegmentIntersectionPoint (const T_LineSegment & other) const
	{
		return LineMethods::findLineToLineSegmentIntersectionPoint (*this, other);
	}

	template <typename T_LineSegment>
	MaybePoint intersectsLineSegment (const T_LineSegment & other) const
	{
		return LineMethods::doLineToLineSegmentIntersect (*this, other);
	}

};


/*
class LineEquation
{
	private:

		float x, y, c;

	public:

	typedef aab::types::Maybe<float> MaybeFloat;

	explicit LineEquation ()

	explicit LineEquation (const float xc, const float yc, const float cc)

	explicit LineEquation (const Point p1, const Point p2)

	//implicit LineEquation::LineEquation (const LineEquation&);
	//implicit LineEquation::LineEquation& operator = (const LineEquation&);

	bool operator == (const LineEquation&) const

	bool operator != (const LineEquation&) const

	void set (const float xc, const float yc, const float cc)

	void set (const Point p1, const Point p2)

	std::string toString () const;

	float getDx () const

	float getDy () const

	MaybeFloat getYIntercept () const

	float getGradient () const

	float getXCoefficient () const

	float getYCoefficient () const

	float getCCoefficient () const

	bool isHorizontal () const

	bool isVertical () const

	bool isParallelTo (const LineEquation & other) const

	float calculateXRaw (float y) const

	float calculateYRaw (float x) const

	MaybeFloat calculateX (float y) const

	MaybeFloat calculate Y (float x) const

	bool isAboveLine (const Point & p) const

	bool isBelowLine (const Point & p) const

	bool isRightOfLine (const Point & p) const

	bool isLeftOfLine (const Point & p) const

	bool isOnLine (const Point & p) const

	float evaluate (const Point & p) const

	MaybePoint findLineIntersectionPoint (const T_Line & other) const

	bool intersectsLine (const T_Line & other) const

	MaybePoint findLineSegmentIntersectionPoint (const T_LineSegment & other) const

	MaybePoint intersectsLineSegment (const T_LineSegment & other) const
};



*/


}	// geometry
}	// aab
#endif // AAB_GEOMETRY_LINE_EQUATION_CLASS













