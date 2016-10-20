
/**
*
*	word_filter.hpp
*
*	This is a crude first edition of the filter. It is capable of
*	filtering exact words only out of strings.
*	Planned extensions involve regular expressions, e.g f.ck to
*	stop feck fick fack etc.
*
*	Add filters for particular words using setFilterFor ().
*	Filter a sentence by using filter() or filterOf () if you
*	want a filtered copy of the string and to not change the
*	original. operator () is equivalent to filter ()
*	The filter ignores the concept of whole words (so if a
*	filtered word is found inside another word, it will be
*	swapped. The filter is CURRENTLY CASE SENSITIVE!!! (i know, i know..)
*
*	example:
*
*		WordFilter filter;
*
*		filter.setFilterFor ("feck", "rum");
*		filter.setFilterFor ("bazoonga", "balloon");
*		filter.setFilterFor ("tentacle", "*@%?$");
*		filter.setFilterFor ("ass", "donkey");
*
*
*		//	obtain users message
*
*		std:string users_message = getUsersMessageSomehow ();
*
*		//	filter
*		filter.filter (user_message);
*
*
*		//	output possibly less obsene version of original message,
*		//	depending on the audiences opinion on balloons, alcohol
*		//	and farmyard animals.
*
*		outPutUsersMessageSomehow (user_message);
*
*
*	note: If some of the words you use to replace a filtered word
*	are actually filtered words, then those words may or may not
*	be in the final string.
*
**/

#if !defined(AAB_TYPES_WORD_FILTER_CLASS)
#define AAB_TYPES_WORD_FILTER_CLASS
#include<string>
#include<map>
namespace aab	{
namespace types	{


class WordFilter
{
	private:

		typedef std::map <std::string, std::string> FilterMap;

		FilterMap map;

	public:

	explicit WordFilter ();
	virtual ~WordFilter ();

	void setFilterFor (const std::string word, const std::string replaced);
	void removeFilterFor (const std::string word);
	void clearFilters ();

	bool hasFilterFor (const std::string word) const;
	std::string getReplacedOf (std::string & word) const;
	int countFilters () const;
	bool hasFilters () const;

	void operator () (std::string & word) const;
	void filter (std::string & word) const;
	std::string filterOf (const std::string & word) const;
};


}		//	types
}		//	aab
#endif	//	AAB_TYPES_WORD_FILTER_CLASS
