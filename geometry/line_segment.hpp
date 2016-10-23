/**
*
*	line_segment.hpp
*
*   Represents a segment of a line as a pair of points, and provides operations
*   for comparing/colliding/interacting with other geometric objects
**/

#if !defined(AAB_GEOMETRY_LINE_SEGMENT_CLASS)
#define AAB_GEOMETRY_LINE_SEGMENT_CLASS
#include"../types/maybe.hpp"
#include"panel.hpp"
#include"vector.hpp"
#include"floats.hpp"
#include"line_methods.hpp"
namespace aab	{
namespace geometry{



class LineSegment
{
	private:

		Point p1, p2;

	public:

	typedef aab::types::Maybe<float> MaybeFloat;
	typedef aab::types::Maybe<Point> MaybePoint;
	typedef aab::types::Maybe<Panel> MaybePanel;

	explicit LineSegment ()
	{
		// nothing //
	}

	explicit LineSegment (const Point p1, const Point p2) : p1 (p1), p2 (p2)
	{
		// nothing //
	}

	//implicit LineSegment::LineSegment (const LineSegment&);
	//implicit LineSegment::LineSegment& operator = (const LineSegment&);

	template <typename T_LineSegment>
	bool operator == (const T_LineSegment & other) const
	{
		return	getFirstPoint () == other.getFirstPoint () &&
				getSecondPoint () == other.getSecondPoint ();
	}

	template <typename T_LineSegment>
	bool operator != (const T_LineSegment & other) const
	{
		return ! operator == (other);
	}

	void set (const Point p1, const Point p2)
	{
		this-> p1 = p1;
		this-> p2 = p2;
	}


	float getDx () const
	{
		return - getYCoefficient ();
	}

	float getDy () const
	{
		return getXCoefficient ();
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
		return p2.getY() - p1.getY();
	}

	float getYCoefficient () const
	{
		return p1.getX() - p2.getX();
	}

	float getCCoefficient () const
	{
		return p2.getX() * p1.getY() - p1.getX() * p2.getY();
	}

	bool isHorizontal () const
	{
		return floats::compare (p1.getY (), p2.getY ());
	}

	bool isVertical () const
	{
		return floats::compare (p1.getX (), p2.getX ());
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


	// transformations (segment dependant):

	void rotateAroundFirst (const float radians)
	{
		Vector v = {p2.x-p1.x, p2.y-p1.y};
		v.rotate (radians);
		p2.set(p1.x+v.x, p1.y+v.y);
	}

	void rotateAroundSecond (const float radians)
	{
		Vector v  = {p1.x-p2.x, p1.y-p2.y};
		v.rotate (radians);
		p1.set(p2.x+v.x, p2.y+v.y);	
	}


	//	queries (segment dependant):

	float getLength () const
	{
		return makeVector (p2.getX() - p1.getX(), p2.getY() - p1.getY()).getLength ();
	}

	Point getFirstPoint () const
	{
		return p1;
	}

	Point getSecondPoint () const
	{
		return p2;
	}

	Panel getEnvelope () const
	{
		return makePanel (p1.getX(), p1.getY(), p2.getX(), p2.getY());
	}

	template <typename T_LineSegment>
	MaybePanel findIntersectionPanel (const T_LineSegment & other) const
	{
		return LineMethods::findLineSegmentIntersectionPanel (*this, other);
	}

	template <typename T_Line>
	MaybePoint findLineIntersectionPoint (const T_Line & other) const
	{
		return LineMethods::findLineSegmentToLineIntersectionPoint (*this, other);
	}

	template <typename T_Line>
	bool intersectsLine (const T_Line & other) const
	{
		return LineMethods::doLineSegmentToLineIntersect (*this, other);
	}

	template <typename T_LineSegment>
	MaybePoint findLineSegmentIntersectionPoint (const T_LineSegment & other) const
	{
		return LineMethods::findLineSegmentToLineSegmentIntersectionPoint (*this, other);
	}

	template <typename T_LineSegment>
	bool intersectsLineSegment (const LineSegment & other) const
	{
		return LineMethods::doLineSegmentsIntersect (*this, other);
	}

	template <typename T_Line>
	MaybePoint findIntersectionPointAsLines (const T_Line & other) const
	{
		return LineMethods::findLineIntersectionPoint (*this, other);
	}

	template <typename T_Line>
	bool intersectsAsLines (const T_Line & other) const
	{
		return LineMethods::doLinesIntersect (*this, other);
	}
};



/*
class LineSegment
{
	private:

		float x, y, c;

	public:

	typedef aab::types::Maybe<float> MaybeFloat;
	typedef aab::types::Maybe<Point> MaybePoint;

	explicit LineSegment ()

	explicit LineSegment (const float xc, const float yc, const float cc)

	explicit LineSegment (const Point p1, const Point p2)

	//implicit LineSegment::LineSegment (const LineSegment&);
	//implicit LineSegment::LineSegment& operator = (const LineSegment&);

	bool operator == (const LineSegment&) const

	bool operator != (const LineSegment&) const

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

	bool isParallelTo (const LineSegment & other) const

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


	// transformations (segment dependant):

	void rotateAroundFirst (const float radians)

	void rotateAroundSecond (const float radians)


	//	queries (segment dependant):

	float getLength () const

	Point getFirstPoint () const

	Point getSecondPoint () const

	Panel getBoundingPanel () const

	MaybePanel findIntersectionPanel (const T_LineSegment & other) const

	MaybePoint findLineIntersectionPoint (const T_Line & other) const

	bool intersectsLine (const T_Line & other) const

	MaybePoint findLineSegmentIntersectionPoint (const T_LineSegment & other) const

	MaybePoint intersectsLineSegment (const T_LineSegment & other) const
};

*/


}	// geometry
}	// aab
#endif // AAB_GEOMETRY_LINE_SEGMENT_CLASS













