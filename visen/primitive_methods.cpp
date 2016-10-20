/**
*
*	primitive_methods.cpp
*
**/

#include"primitive_methods.hpp"
#include"_include_opengl.hpp"
#include"../maths/constants.hpp"
#include<cmath>
namespace aab	{
namespace visen	{
    
void drawPolygon(ConstPointVector& points)
{
	glBegin(GL_LINE_LOOP);
	for (auto i = points.begin(); i != points.end(); ++i)
	{
		glVertex2f(i->x, i->y);
	}
	glEnd();
}

void drawSolidPolygon(ConstPointVector& points)
{
	glBegin(GL_TRIANGLE_FAN);
	for (auto i = points.begin(); i != points.end(); ++i)
	{
		glVertex2f(i->x, i->y);
	}
	glEnd();
}

void drawCircle(const Point center, cfloat radius)
{
	cfloat k_segments = 16.0f;
	cfloat k_increment = 2.0f * aab::maths::pi / k_segments;
	float theta = 0.0f;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < k_segments; ++i)
	{
		Point v = center + radius*aab::geometry::makePoint(std::cos(theta), std::sin(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
};

void drawSolidCircle(const Point center, cfloat radius, const Point axis)
{
	cfloat k_segments = 16.0f;
	cfloat k_increment = 2.0f * aab::maths::pi / k_segments;
	float theta = 0.0f;

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < k_segments; ++i)
	{
		Point v = center + radius*aab::geometry::makePoint(std::cos(theta), std::sin(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();

	Point p = center + radius * axis;
	glBegin(GL_LINES);
	glVertex2f(center.x, center.y);
	glVertex2f(p.x, p.y);
	glEnd();
}

void drawSegment(const Point p1, const Point p2)
{
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
}

void drawPoint(const Point p)
{
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
}

void drawPoint(const Point p, cfloat size)
{
	glPointSize(size);
	drawPoint(p);
	glPointSize(1.0f);
}

void drawPoints(ConstPointVector& points)
{
	glBegin(GL_POINTS);
	for (auto i = points.begin(); i!=points.end();++i)
	{
        glVertex2f(i->x, i->y);
	}
	glEnd();
}

void drawPoints(ConstPointVector& points, cfloat size)
{
	glPointSize(size);
	drawPoints(points);
	glPointSize(1.0f);
}

void drawPanel(cfloat x1, cfloat y1, cfloat x2, cfloat y2)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}

void drawSolidPanel(cfloat x1, cfloat y1, cfloat x2, cfloat y2)
{
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}

}		//	visen
}		//	aab
