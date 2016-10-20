

#include"../../auden/auden.hpp"
#include"../../events/events.hpp"
#include"../../game/game.hpp"
#include"../../geometry/geometry.hpp"
#include"../../input/input.hpp"
#include"../../maths/maths.hpp"
#include"../../test/test.hpp"
#include"../../time/time.hpp"
#include"../../types/types.hpp"
#include"../../visen/visen.hpp"
#include<iostream>
#include<list>
#include<gl/gl.h>

using namespace aab::auden;
using namespace aab::events;
using namespace aab::game;
using namespace aab::geometry;
using namespace aab::input;
using namespace aab::maths;
using namespace aab::test;
using namespace aab::time;
using namespace aab::types;
using namespace aab::visen;
using namespace std;

class SelectableNode
{
};

class CheckingPolygon : public Polygon
{
	Mouse::Ptr mouse;

	Color colliding;
	Color notColliding;
	Color panel;

	static list <CheckingPolygon*> allPolygons;

	bool isColliding ()
	{
		list <CheckingPolygon*>::iterator itr = allPolygons.begin ();

		for (;itr != allPolygons.end();++itr)
		{
			if (*itr != this)
			{
				if ((*itr) -> isIntersecting (*this))
				{
					return true;
				}
			}
		}

		return false;
	}

	public:

	explicit CheckingPolygon (Mouse::Ptr mouse) : mouse (mouse)
	{
		colliding.set (255, 0, 0);
		notColliding.set (0, 128, 255);
		panel.set (50,50,50);

		allPolygons.push_back (this);
	}

	~CheckingPolygon ()
	{
		allPolygons.remove (this);
	}

	void draw ()
	{

		panel.apply ();

		/*
		glBegin (GL_LINES);
		{
			glVertex2f (getFirst().getX(), getFirst().getY());
			glVertex2f (getFirst().getX(), getSecond().getY());
			glVertex2f (getFirst().getX(), getSecond().getY());
			glVertex2f (getSecond().getX(), getSecond().getY());
			glVertex2f (getSecond().getX(), getSecond().getY());
			glVertex2f (getSecond().getX(), getFirst().getY());
			glVertex2f (getSecond().getX(), getFirst().getY());
			glVertex2f (getFirst().getX(), getFirst().getY());
		}
		glEnd ();
		*/

		if (isColliding ())
		{
			colliding.apply ();
		}
		else
		{
			notColliding.apply ();
		}

		/*
		glBegin (GL_LINES);
		{
			glVertex2f (getFirst().getX(), getFirst().getY());
			glVertex2f (getSecond().getX(), getSecond().getY());
		}
		glEnd ();
		*/
	}

	static void drawAll ()
	{
		list <CheckingPolygon*>::iterator itr = allPolygons.begin ();

		for (;itr != allPolygons.end();++itr)
		{
			(*itr)-> draw ();
		}
	}

	static void randomizeAll ()
	{
		list <CheckingPolygon*>::iterator itr = allPolygons.begin ();

		for (;itr != allPolygons.end();++itr)
		{
			if (random1in (4))
			{
				int x = random (10, 630);
				int y = random (10, 470);
				int length = random (10, 460);

				if (random1in (2))
				{
					(*itr)-> set (Point (x,y), Point (x + length,y));
				}
				else
				{
					(*itr)-> set (Point (x,y), Point (x,y + length));
				}
			}
			else
			{
				(*itr)-> set (Point (random (10, 630),random (10, 470)), Point (random (10, 630),random (10, 470)));
			}

			cout << "\nline:\t" << (*itr)->toString() << "\n";
		}
	}
};
list <CheckingPolygon*> CheckingPolygon::allPolygons;



int main ()
{



	try
	{
		Screen screen = makeScreen (640, 480, windowed_mode);
		screen-> showCursor ();
		screen-> setClearColor (0, 0, 0);

		EventQueue eventQueue = makeEventQueue (screen);
		Dispatcher dispatcher = makeDispatcher ();

		Mouse::Ptr mouse (new Mouse (screen));
		mouse-> disableEventPumping ();
		CloseHandler::Ptr closer (new CloseHandler ());
		KeyInfo::Ptr keys (new KeyInfo ());
		EventHandler::Ptr keyboardHandler (new KeyboardAutoHandler (keys));

		dispatcher-> addHandler (closer);
		dispatcher-> addHandler (keyboardHandler);

		eventQueue-> addDispatcher (dispatcher);

		Cap cap (5);
		cap.setMaximumFPS (60);
		cap.setSleepInterval (10);

		CheckingLine line1 (mouse);
		CheckingLine line2 (mouse);
		CheckingLine line3 (mouse);
		CheckingLine line4 (mouse);
		CheckingLine line5 (mouse);
		CheckingLine line6 (mouse);
		CheckingLine line7 (mouse);

		seed_random (getMilliseconds ());

		screen-> clear ();
		CheckingLine::randomizeAll ();
		CheckingLine::drawAll();
		screen-> update ();


		while (! closer-> hasClosed ())
		{


			eventQueue-> poll ();


			cap.wait ();


			if (keys-> isHit (key_r))
			{
				screen-> clear ();
				CheckingLine::randomizeAll ();
				CheckingLine::drawAll();
				screen-> update ();
			}

			if (mouse-> isButtonDown (1))
			{
				cout << "mouse pos: (" << mouse-> getX() << ", " << mouse-> getY() << ")\n";
			}

			keys-> update ();
			mouse-> update ();


		}

	}
	catch (std::exception &)
	{
		cout << "oh crap" << endl;
	}

	return 0;
}


