/**
*
*	primitive_methods.hpp
*
*   texturing is enabled by default by visen, so to use without a texture applied, call the appropriate methods from RenderState.
**/

/*
*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*   These methods are altered from Box2ds DebugDraw code examples.
*
*/


#if !defined(AAB_VISEN_PRIMITIVE_METHODS)
#define AAB_VISEN_PRIMITIVE_METHODS
#include"../geometry/point.hpp"
#include"../types/const.hpp"
#include<vector>
namespace aab	{
namespace visen	{
    
typedef aab::geometry::Point Point;
typedef const std::vector<Point> ConstPointVector;

void drawPolygon(ConstPointVector&);

void drawSolidPolygon(ConstPointVector&);

void drawCircle(const Point center, cfloat radius);

void drawSolidCircle(const Point center, cfloat radius, const Point axis = aab::geometry::makePoint(1,0));

void drawSegment(const Point, const Point);

void drawPoint(const Point);

void drawPoint(const Point, cfloat size);

void drawPoints(ConstPointVector&);

void drawPoints(ConstPointVector&, cfloat size);

void drawPanel(cfloat x1, cfloat y1, cfloat x2, cfloat y2);

void drawSolidPanel(cfloat x1, cfloat y1, cfloat x2, cfloat y2);


}		//	visen
}		//	aab
#endif //AAB_VISEN_PRIMITIVE_METHODS
