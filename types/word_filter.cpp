
/**
*
*	word_filter.cpp
*
*
**/


#include"word_filter.hpp"
#include<boost/algorithm/string/replace.hpp>
#include<algorithm>
namespace aab	{
namespace types	{
using std::for_each;
using std::pair;
using std::string;
/*
class WordReplacer
{
	private:

		std::string & word;

	public:

	void operator () (pair <string, string> replacer)
	{
		// modify to consider case.
		boost::algorithm::replace_all (word, replacer.first, replacer.second);
	}
};


WordFilter::WordFilter ()
{
	// nothing //
}

WordFilter::~WordFilter ()
{
	// nothing //
}


void WordFilter::setFilterFor (const string word, const string replaced)
{
	map [word] = replaced;
}

void WordFilter::removeFilterFor (const std::string word)
{
	map.erase (word);
}

void WordFilter::clearFilters ()
{
	map.clear ();
}


bool WordFilter::hasFilterFor (const string word) const
{
	return map.find (word) != map.end ();
}

std::string WordFilter::getReplacedOf (string & word) const
{
	FilterMap::iterator itr = map.find (word);

	if (itr == map.end ()
	{
		return "";
	}

	return *itr;
}

int WordFilter::countFilters () const
{
	return map.size ();
}

bool WordFilter::hasFilters () const
{
	return ! map.empty ();
}

void WordFilter::operator () (string & word) const
{
	filter (word);
}

void WordFilter::filter (string & word) const
{
	for_each (map.begin (), map.end (), WordReplacer (word));
}

std::string WordFilter::filterOf (const :string & word) const
{
	string newWord (word);

	filter (newWord);

	return newWord;
}
*/

}		//	types
}		//	aab

