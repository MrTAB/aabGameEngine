
/**
*
*	diagnostic.hpp
*
*   Used for diagnostic printouts that can be omitted entirely from release via
*   Changing the template to the empty version.
**/

#if !defined(AAB_TEST_DIAGNOSTIC_CLASS)
#define AAB_TEST_DIAGNOSTIC_CLASS
#include<boost/algorithm/string/replace.hpp>
#include<string>
#include<iostream>
#include<stack>
namespace aab	{
namespace test	{


enum DiagnosticParameter
{
	diagnostic_disable,
	diagnostic_tree,
	diagnostic_method,
	diagnostic_out
};



template <const DiagnosticParameter T_DP>
class Diagnostic
{
};

template <>
class Diagnostic <diagnostic_disable>
{
	public:

	inline explicit Diagnostic (std::string)
	{
		 // nothing //
	}

	inline ~Diagnostic ()
	{
		 // nothing //
	}

	template <typename T_ostreamable>
	inline Diagnostic  & operator << (const T_ostreamable &)
	{
		return *this;
	}
};


template <>
class Diagnostic <diagnostic_tree>
{
	private:

		static int increment;
		static std::ostream * out;
		static char methodOpenBrace;
		static char methodCloseBrace;
		static std::string tabString;

	public:

	explicit Diagnostic (std::string method)
	{
		*out<< method
			<< "\n"
			<< tabString
			<< methodOpenBrace
			<< "\n";

		tabString += " ";
		++increment;
		*out << tabString;
	}

	virtual ~ Diagnostic ()
	{
		--increment;
		tabString.erase (tabString.end () - 1, tabString.end ());
		*out<< "\n"
			<< tabString
			<< methodCloseBrace
			<< "\n"
			<< tabString;
	}

	Diagnostic & operator << (std::string outtee)
	{
		boost::algorithm::replace_all (outtee, "\n", "\n" + tabString);

		*out << outtee;

		return *this;
	}

	Diagnostic & operator << (char outtee)
	{
		if (outtee == '\n')
		{
			*out << '\n' << tabString;
		}
		else
		{
			*out << outtee;
		}

		return *this;
	}

	Diagnostic & operator << (const int outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const unsigned int outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const long outtee)
	{
		*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const unsigned long outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const double outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const float outtee)
	{	*out << outtee;
		return *this;
	}
};




template <>
class Diagnostic <diagnostic_method>
{
	private:

		static std::ostream * out;
		static bool initialized;
		static char methodOpenBrace;
		static char methodCloseBrace;
		static std::string tab;
		static std::stack <std::string> methods;

	public:

	explicit Diagnostic (std::string method)
	{
		if (! methods.empty ())
		{
			*out<< "\n"
				<< methodCloseBrace
				<< "\n";
		}

		methods.push (method);

		*out<< methods.top ()
			<< "\n"
			<< methodOpenBrace
			<< "\n"
			<< tab;
	}

	virtual ~ Diagnostic ()
	{
		methods.pop ();

		if (methods.empty ())
		{
			*out<< "\n"
				<< methodCloseBrace
				<< "\n";
		}
		else
		{
			*out<< "\n"
				<< methodCloseBrace
				<< "\n"
				<< methods.top ()
				<< "\n"
				<< methodOpenBrace
				<< "\n"
				<< tab;
		}
	}

	Diagnostic & operator << (std::string outtee)
	{
		boost::algorithm::replace_all (outtee, "\n", "\n" + tab);

		*out << outtee;

		return *this;
	}

	Diagnostic & operator << (char outtee)
	{
		if (outtee == '\n')
		{
			*out << '\n' << tab;
		}
		else
		{
			*out << outtee;
		}

		return *this;
	}

	Diagnostic & operator << (const int outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const unsigned int outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const long outtee)
	{
		*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const unsigned long outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const double outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const float outtee)
	{	*out << outtee;
		return *this;
	}
};

template <>
class Diagnostic <diagnostic_out>
{
	private:

		static std::ostream * out;

	public:

	explicit Diagnostic (std::string method)
	{
		*out<< method;
	}

	virtual ~ Diagnostic ()
	{
        // do nothing //
	}

	Diagnostic & operator << (std::string outtee)
	{
		*out << outtee;
		return *this;
	}

	Diagnostic & operator << (char outtee)
	{
        *out << outtee;
		return *this;
	}

	Diagnostic & operator << (const int outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const unsigned int outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const long outtee)
	{
		*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const unsigned long outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const double outtee)
	{	*out << outtee;
		return *this;
	}
	Diagnostic & operator << (const float outtee)
	{	*out << outtee;
		return *this;
	}
};


}		//	test
}		//	aab
#endif	//	AAB_TEST_DIAGNOSTIC_CLASS




