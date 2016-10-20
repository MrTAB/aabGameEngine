/**
*
*	matrix.hpp
*
*	This is a matrix storage class, used for both right and left hand co-ordinate systems.
*	No co-ordinate system specific methods are supplied.
**/

#if !defined(AAB_TYPES_MATRIX_CLASS)
#define AAB_TYPES_MATRIX_CLASS
#include<cmath>
#include<algorithm>
namespace aab	{
namespace types	{

struct Matrix
{
	private:

	typedef float _f;

		inline int _pos(const int x, const int y) const // x,y <- [0,3]
		{
			return x + 4 * y;
		}

		inline bool _compare (const float a, const float b) const
		{
			return std::fabs(a-b) < 1e-5;
		}

	public:

	float e[16];

	inline void setAsIdentity ()
	{
		std::fill_n(e, 16, 0);
		e[0] = e[5] = e[10] = e[15] =  1;
	}

	inline
	void set (	_f a1, _f a2, _f a3, _f a4,
				_f b1, _f b2, _f b3, _f b4,
				_f c1, _f c2, _f c3, _f c4,
				_f d1, _f d2, _f d3, _f d4	)
	{
		e[0] = a1; e[1] = a2; e[2] = a3; e[3] = a4;
		e[4] = b1; e[5] = b2; e[6] = b3; e[7] = b4;
		e[8] = c1; e[9] = c2; e[10]= c3; e[11]= c4;
		e[12]= d1; e[13]= d2; e[14]= d3; e[15]= d4;
	}

	inline void transpose ()
	{
		Matrix original = *this;

		for  (int x=0;x<4;++x)
			for (int y=0;y<4;++y)
				this->e[_pos(x,y)] = original.e[_pos(y,x)];
	}

	inline bool operator == (const Matrix & o) const
	{
		return
			_compare(e[0],o.e[0]) && _compare(e[5],o.e[5]) && _compare(e[10],o.e[10]) && _compare(e[15],o.e[15]) &&
			_compare(e[1],o.e[1]) && _compare(e[4],o.e[4]) && _compare(e[2],o.e[2]) && _compare(e[8],o.e[8]) &&
			_compare(e[6],o.e[6]) && _compare(e[9],o.e[9]) && _compare(e[3],o.e[3]) && _compare(e[12],o.e[12]) &&
			_compare(e[7],o.e[7]) && _compare(e[13],o.e[13]) && _compare(e[11],o.e[11]) && _compare(e[14],o.e[14]);
	}

};

}	// types
}	// aab
#endif // AAB_TYPES_MATRIX_CLASS

