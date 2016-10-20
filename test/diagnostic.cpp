
/**
*
*	diagnostic.cpp"
*
**/

#include"diagnostic.hpp"
namespace aab	{
namespace test	{


std::ostream * Diagnostic <diagnostic_method>::out = &std::cout;
char Diagnostic <diagnostic_method>::methodOpenBrace = '{';
char Diagnostic <diagnostic_method>::methodCloseBrace = '}';
std::string Diagnostic <diagnostic_method>::tab = "\t";
std::stack <std::string> Diagnostic <diagnostic_method>::methods;

int Diagnostic <diagnostic_tree>::increment = 0;
std::ostream * Diagnostic <diagnostic_tree>::out = &std::cout;
char Diagnostic <diagnostic_tree>::methodOpenBrace = '{';
char Diagnostic <diagnostic_tree>::methodCloseBrace = '}';
std::string Diagnostic <diagnostic_tree>::tabString = "";

std::ostream * Diagnostic <diagnostic_out>::out = &std::cout;

/*
typedef Diagnostic <diagnostic_method> Diag;

void A (bool callC);
void B ();
void C ();


void A (bool callC)
{
	Diag d ("void A");

	d << "value of callC is:\t" << callC << "\n";
	if (callC)
	{
		d << "calling C" << "\n";
		C ();
	}
	else
	{
		d << "not calling C" << "\n";
	}
}

void B ()
{
	Diag d ("void B");

	d << "calling A" << "\n";

	A (false);
}

void C ()
{
	Diag d ("void C");

	d << "calling B" << "\n";

	B ();

	d << "calling A false" << "\n";

	A (false);
}


bool test_diagnostic ()
{

	Diag d ("bool test_diagnostic");

	d << "calling A true" << "\n";
	A (true);
	d << "calling B" << "\n";
	B ();
	d << "calling C" << "\n";
	C ();
	d << "calling A false" << "\n";
	A (false);
	d << "calling C" << "\n";
	C ();
	d << "calling B" << "\n";
	B ();

	d << "test types : "
	<< "\nint \t" << -0xffff
	<< "\nunsigned int \t" << 0xffffffff
	<< "\nbool\t" << true
	<< "\nbool\t" << false
	<< "\nfloat\t" << 4.5f
	<< "\ndouble\t" << -0.0006
	<< "\ndouble\t" << 10000000000000.0
	<< "\nlong\t" << 4856956L
	<< "\nunsigned long\t" << 34534545UL
	<< "\nchar\t" << 'h';


	return true;
}
*/

}		//	test
}		//	aab

