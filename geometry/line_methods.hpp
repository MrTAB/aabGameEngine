/**
*
*	line_methods.hpp
*
**/

#if !defined(AAB_GEOMETRY_LINE_METHODS)
#define AAB_GEOMETRY_LINE_METHODS
#include"../types/maybe.hpp"
#include"panel.hpp"
#include"vector.hpp"
#include"floats.hpp"
namespace aab	{
namespace geometry{

namespace LineMethods
{

	inline float getXCoefficient (const Point p1, const Point p2)
	{
		return p2.y - p1.y;
	}

	inline float getYCoefficient (const Point p1, const Point p2)
	{
		return p1.x - p2.x;
	}

	inline float getCCoefficient (const Point p1, const Point p2)
	{
		return p2.x * p1.y - p1.x * p2.y;
	}

	inline aab::types::Maybe<Point> findLineIntersectionPoint (const float xc1,
								const float yc1, const float cc1,
								const float xc2, const float yc2,
								const float cc2)
	{
		float denom = xc1 * yc2 - xc2 * yc1;

		if (floats::isZero (denom))
		{
			return false;
		}

		Point intersection;

		intersection.x =  ((yc1 * cc2 - yc2 * cc1) / denom);
		intersection.y =  ((xc2 * cc1 - xc1 * cc2) / denom);

		return intersection;
	}

	template <typename T_LineA, typename T_LineB>
		/* both require getXCoefficient() getYCoefficient() and getCCoefficient() */
	inline aab::types::Maybe<Point> findLineIntersectionPoint (const T_LineA & a, const T_LineB & b)
	{
		return findLineIntersectionPoint (a.getXCoefficient (), a.getYCoefficient (), a.getCCoefficient (),
						b.getXCoefficient (), b.getYCoefficient (), b.getCCoefficient ());
	}

	template <typename T_Line, typename T_LineSegment>
		/* T_Line requires getXCoefficient, getYCoefficient, getCCoefficient
		 * T_LineSegment requires getXCoefficient, getYCoefficient, getCCoefficient, getBoundingPanel */
	inline aab::types::Maybe<Point> findLineToLineSegmentIntersectionPoint (const T_Line & l, const T_LineSegment & ls)
	{
		aab::types::Maybe<Point> intersection = findLineIntersectionPoint (l, ls);

		if (! intersection.exists ())
		{
			return false;
		}

		if (ls.getBoundingPanel ().isPointInside (intersection))
		{
			return intersection;
		}

		return false;
	}

	template <typename T_LineSegment, typename T_Line>
		/* T_LineSegment requires getXCoefficient, getYCoefficient, getCCoefficient, getBoundingPanel
		 * T_Line requires getXCoefficient, getYCoefficient, getCCoefficient */
	inline aab::types::Maybe<Point> findLineSegmentToLineIntersectionPoint (const T_LineSegment & ls, const T_Line & l)
	{
		return findLineToLineSegmentIntersectionPoint (l, ls);
	}

	template <typename T_LineSegmentA, typename T_LineSegmentB>
		/* both require getXCoefficient, getYCoefficient, getCCoefficient, getBoundingPanel */
	inline aab::types::Maybe<Point> findLineSegmentIntersectionPoint (const T_LineSegmentA & a, const T_LineSegmentB & b)
	{
		aab::types::Maybe<Point> intersection = findLineIntersectionPoint (a, b);

		if (! intersection.exists ())
		{
			return false;
		}

		if (! a.getBoundingPanel().isPointInside (intersection))
		{
			return false;
		}

		if (! b.getBoundingPanel().isPointInside (intersection))
		{
			return false;
		}

		return intersection ;
	}

	template <typename T_LineSegmentA, typename T_LineSegmentB>
		/* both require getXCoefficient, getYCoefficient, getCCoefficient, getBoundingPanel */
	inline aab::types::Maybe<Point> findLineSegmentToLineSegmentIntersectionPoint (const T_LineSegmentA & a, const T_LineSegmentB & b)
	{
		return findLineSegmentIntersectionPoint (a, b);
	}

	template <typename T_LineA, typename T_LineB>
		/* both require getXCoefficient() getYCoefficient() and getCCoefficient() */
	inline aab::types::Maybe<Point> findLineToLineIntersectionPoint (const T_LineA & a, const T_LineB & b)
	{
		return findLineIntersectionPoint (a, b);
	}


	template <typename T_Line>
		/* requires getDx() and getCCoefficient () */
	inline aab::types::Maybe<float> calculateYIntercept (const T_Line & line)
	{
		float dx = line.getDx ();

		if (floats::isZero(dx))
		{
			return false;
		}

		return line.getCCoefficient () / dx;
	}

	template <typename T_Line>
		/* requires getDx() and getDy () */
	inline aab::types::Maybe<float> calculateGradient (const T_Line & line)
	{
		float dx = line.getDx ();

		if (floats::isZero (dx))
		{
			return false;
		}

		return line.getDy () / dx;
	}

	template <typename T_LineA, typename T_LineB>
		/* both require getXCoefficient() and getXCoefficient() */
	inline bool areParallel (const T_LineA & a, const T_LineB & b)
	{
		return areClose (a.getXCoefficient () * b.getYCoefficient (),
							b.getXCoefficient () * a.getYCoefficient ());
	}

	template <typename T_LineA, typename T_LineB>
		/* both require getXCoefficient, getYCoefficient and getCCoefficient */
	inline bool doLinesIntersect (const T_LineA & a, const T_LineB & b)
	{
		return ! areParallel (a, b);
	}

	template <typename T_LineSegmentA, typename T_LineSegmentB>
		/* both require getXCoefficient, getYCoefficient, getCCoefficient and getBoundingPanel */
	inline bool doLineSegmentsIntersect (const T_LineSegmentA & a, const T_LineSegmentB & b)
	{
		return findLineSegmentIntersectionPoint (a, b).exists ();
	}

	template <typename T_Line, typename T_LineSegment>
		/* T_Line requires getXCoefficient, getYCoefficient and getCCoefficient
		 * T_LineSegment requires getXCoefficient, getYCoefficient, getCCoefficient and getBoundingPanel */
	inline bool doLineToLineSegmentIntersect (const T_Line & a, const T_LineSegment & b)
	{
		return findLineToLineSegmentIntersectionPoint (a, b).exists ();
	}

	template <typename T_LineSegment, typename T_Line>
		/* T_LineSegment requires getXCoefficient, getYCoefficient, getCCoefficient and getBoundingPanel
		 *  T_Line requires getXCoefficient, getYCoefficient and getCCoefficient */
	inline bool doLineSegmentToLineIntersect (const T_LineSegment & b, const T_Line & a)
	{
		return doLineToLineSegmentIntersect (a, b);
	}

	template <typename T_LineSegmentA, typename T_LineSegmentB>
		/* both require getBoundingPanel */
	inline aab::types::Maybe<Panel> findLineSegmentIntersectionPanel (const T_LineSegmentA & a, const T_LineSegmentB & b)
	{
		return a.getBoundingPanel().getIntersection (b.getBoundingPanel ());
	}

	template <typename T_Line>
		/* requires getYCoefficient, getCCoefficient and getXCoefficient */
	inline float calculateXRawFromY (const T_Line & line, const float y)
	{
		return - (line.getYCoefficient () * y + line.getCCoefficient ()) / line.getXCoefficient ();
	}

	template <typename T_Line>
		/* requires getXCoefficient, getCCoefficient, getYCoefficient */
	inline float calculateYRawFromX (const T_Line & line, const float x)
	{
		return - (line.getXCoefficient () * x + line.getCCoefficient ()) / line.getYCoefficient ();
	}

	template <typename T_Line>
		/* requires isHorizontal, getYCoefficient, getCCoefficient and getXCoefficient */
	inline float calculateXFromY (const T_Line & line, const float y)
	{
		if (line.isHorizontal ())
		{
			return false;
		}

		return calculateXRawFromY (line, y);
	}

	template <typename T_Line>
		/* requires isVertical, getYCoefficient, getCCoefficient and getXCoefficient */
	inline float calculateYFromX (const T_Line & line, const float y)
	{
		if (line.isVertical ())
		{
			return false;
		}

		return calculateYRawFromX (line, y);
	}


	template <typename T_Line, typename T_Point>
		/* T_Line needs isVertical, getXCoefficient, getCCoefficient, getYCoefficient.
		 * T_Point needs getX and getY */
	inline bool isPointAboveLine (const T_Line & l, const T_Point & p)
	{
		if (l.isVertical ())
		{
			return false;
		}

		return calculateYRawFromX (l, p.getX ()) < p.getY ();
	}

	template <typename T_Line, typename T_Point>
		/* T_Line needs isVertical, getXCoefficient, getCCoefficient, getYCoefficient.
		 * T_Point needs getX and getY */
	inline bool isPointBelowLine (const T_Line & l, const T_Point & p)
	{
		if (l.isVertical ())
		{
			return false;
		}

		return calculateYRawFromX (l, p.getX ()) > p.getY ();
	}

	template <typename T_Line, typename T_Point>
		/* T_Line needs isHorizontal, getXCoefficient, getCCoefficient, getYCoefficient.
		 * T_Point needs getX and getY */
	inline bool isPointRightOfLine (const T_Line & l, const T_Point & p)
	{
		if (l.isHorizontal ())
		{
			return false;
		}

		return calculateXRawFromY (l, p.getY ()) < p.getX ();
	}

	template <typename T_Line, typename T_Point>
		/* T_Line needs isHorizontal, getXCoefficient, getCCoefficient, getYCoefficient.
		 * T_Point needs getX and getY */
	inline bool isPointLeftOfLine (const T_Line & l, const T_Point & p)
	{
		if (l.isHorizontal ())
		{
			return false;
		}

		return calculateXRawFromY (l, p.getY ()) > p.getX ();
	}

	template <typename T_Line, typename T_Point>
		/* T_Line requires getXCoefficient, getYCoefficient and getCCoefficient
		 * T_Point requires getX and getY */
	inline float evaluateLinesEquationFor (const T_Line & l, const T_Point & p)
	{
		return	l.getXCoefficient () * p.getX () +
				l.getYCoefficient () * p.getY () +
				l.getCCoefficient ();
	}

	template <typename T_Line, typename T_Point>
		/* T_Line requires getXCoefficient, getYCoefficient and getCCoefficient
		 * T_Point requires getX and getY */
	inline bool isPointOnLine (const T_Line & l, const T_Point & p)
	{
		return floats::isZero (evaluateLinesEquationFor (l, p));
	}


}	// LineMethods

}	// geometry
}	// aab
#endif // AAB_GEOMETRY_LINE_METHODS













