

#include"../diagnostic.hpp"



template<typename D> void A (bool callC);

template<typename D> void B ();

template<typename D> void C ();


template<typename D>
void A (bool callC)
{
	D d ("void A");

	d << "value of callC is:\t" << callC << "\n";
	if (callC)
	{
		d << "calling C" << "\n";
		C <D>();
	}
	else
	{
		d << "not calling C" << "\n";
	}
}

template<typename D>
void B ()
{
	D d ("void B");

	d << "calling A" << "\n";

	A<D> (false);
}

template<typename D>
void C ()
{
	D d ("void C");

	d << "calling B" << "\n";

	B<D> ();

	d << "calling A false" << "\n";

	A<D> (false);
}

template<typename D>
bool test_diagnostic ()
{

	D d ("bool test_diagnostic");

	d << "calling A true" << "\n";
	A<D> (true);
	d << "calling B" << "\n";
	B<D> ();
	d << "calling C" << "\n";
	C<D> ();
	d << "calling A false" << "\n";
	A<D> (false);
	d << "calling C" << "\n";
	C<D> ();
	d << "calling B" << "\n";
	B<D> ();

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

int main()
{
    
    using std::cout; 
    using std::endl;
    
    cout << "testing Diagnostic <diagnostic_disable>\n";
    test_diagnostic <aab::test::Diagnostic <aab::test::diagnostic_disable> > ();
    cout << "finished testing Diagnostic <diagnostic_disable>\n";
    std::cin.get();
    
    cout << "testing Diagnostic <diagnostic_tree>\n";
    test_diagnostic <aab::test::Diagnostic <aab::test::diagnostic_tree> > ();
    cout << "finished testing Diagnostic <diagnostic_tree>\n";
    std::cin.get();
    
    cout << "testing Diagnostic <diagnostic_method>\n";
    test_diagnostic <aab::test::Diagnostic <aab::test::diagnostic_method> > ();
    cout << "finished testing Diagnostic <diagnostic_method>\n";
    std::cin.get();
    
    cout << "testing Diagnostic <diagnostic_out>\n";
    test_diagnostic <aab::test::Diagnostic <aab::test::diagnostic_out> > ();
    cout << "finished testing Diagnostic <diagnostic_out>\n";
    std::cin.get();
    
    return 0;
}
