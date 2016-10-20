
#include<iostream>
#include"line.hpp"
#include"maybe.hpp"

using std::cout;
using aab::types::Maybe;
using namespace aab::geometry;

void test ();
void test_Line ();
void test_Point ();
void test_Floats ();
void test_Panel ();
void test_Vector ();

bool global_fail = false;

void fail ()
{
	global_fail = true;
	cout << ". F A I L .\n";
}

int main ()
{

	cout << "hello\n";

	test ();


	cout << "result=> " << (global_fail? ". F A I L .\n" : "success.\n");
	return 0;
}


void test ()
{
	cout << "----------------------------------------------------------\n";
	cout << "test\n\n";

	test_Line ();
	test_Point ();
	test_Floats ();
	test_Panel ();
	test_Vector ();

}

void test_Line ()
{
	cout << "\n----------------------------------------------------------\n";
	cout << "test Line\n";


	Line clockLines[13];
	Point zero (0, 0);
	Vector vector (1, 0);

	for (int t = 0; t < 13; ++t)
	{
		clockLines[t].set (zero, vector.toPoint ());
		vector.rotate (3.14159265f/6.0f);
	}


	//returns the bounding panel:
	//[1]	Panel getBoundingPanel () const

	/*	test cases:
		1.	p1.x < p2.x, p1.y < p2.y
		2.	p1.x < p2.x, p1.y > p2.y
		3.	p1.x > p2.x, p1.y < p2.y
		4.	p1.x > p2.x, p1.y > p2.y
	*/


	{	cout << "\n[1](1)\n";

		Line line (Point(45,30), Point(160,120));
		Panel panel = line.getBoundingPanel ();
		cout << panel.toString() << "\n";

		if (panel.getLeft () == 45 && panel.getRight () == 160 && panel.getBottom () == 30 && panel.getTop() == 120)
			cout << "all good.\n";
		else
			fail ();
	}

	{	cout << "\n[1](2)\n";

		Line line (Point(45,120), Point(160,30));
		Panel panel = line.getBoundingPanel ();
		cout << panel.toString() << "\n";

		if (panel.getLeft () == 45 && panel.getRight () == 160 && panel.getBottom () == 30 && panel.getTop() == 120)
			cout << "all good.\n";
		else
			fail ();
	}

	{	cout << "\n[1](3)\n";

		Line line (Point(160,30), Point(45,120));
		Panel panel = line.getBoundingPanel ();
		cout << panel.toString() << "\n";

		if (panel.getLeft () == 45 && panel.getRight () == 160 && panel.getBottom () == 30 && panel.getTop() == 120)
			cout << "all good.\n";
		else
			fail ();
	}

	{	cout << "\n[1](4)\n";

		Line line (Point(160,120), Point(45,30));
		Panel panel = line.getBoundingPanel ();
		cout << panel.toString() << "\n";

		if (panel.getLeft () == 45 && panel.getRight () == 160 && panel.getBottom () == 30 && panel.getTop() == 120)
			cout << "all good.\n";
		else
			fail ();
	}


	// returns the intersection region of the discrete lines bounding panels, if any.
	//[2]	aab::types::Maybe<Panel> findIntersectionPanel (const Line other)

	/* test factors:

		two lines. Properties:

		(one is right of other
		|| one is up of other
		|| one is left of other
		|| one is down of other
		|| one is right and up of other
		|| one is left and up of other
		|| one is right and down of other
		|| one is left and down of other)

		&& one is horizontal || vertical || backslash || forwardslash
		&& other is horizontal || vertical || backslash || forwardslash

	*/

	//returns the interscetion point of the infinate lines, if any.
	//[3]	aab::types::Maybe<Point> findOpenIntersectionPoint (const Line other)

	// returns the intersection point of the discrete lines (i.e within the bounding panels) if any.
	//[4]	aab::types::Maybe<Point> findIntersectionPoint (const Line other)


}

void test_Point ()
{
	cout << "\n----------------------------------------------------------\n";
	cout << "test Point\n\n";
}

void test_Floats ()
{
	cout << "\n----------------------------------------------------------\n";
	cout << "test Floats\n\n";
}

void test_Panel ()
{
	cout << "\n----------------------------------------------------------\n";
	cout << "test Panel\n\n";
}

void test_Vector ()
{
	cout << "\n----------------------------------------------------------\n";
	cout << "test Vector\n\n";
}

