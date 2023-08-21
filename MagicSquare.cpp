#include "MagicSquare.h"

#include <algorithm>
#include <numeric>
#include <fstream>
#include <iomanip>

using namespace std;

const MagicSquare::position_type MagicSquare::noPosition{make_pair(-1, -1)};

MagicSquare::MagicSquare(size_type n)
	: n{ n }, magicConst{ value_type(n * (n * n + 1) / 2) }, square(n, row_type(n))
{
	fillSquare();
}

ostream& operator<<(ostream& os, const MagicSquare& K)
{
	for (const auto& row : K.square)
	{
		for (const auto& number : row)
		{
			os << setw(K.calculateFieldWidth()) << number << " ";
		}
		os << endl;
	}
	return os;
}

istream& operator>>(istream& is, MagicSquare& K)
{
	using st = MagicSquare::size_type;
	st size{};
	bool isStdout = (&is == &cin);
	string errorMsg("Loading error.");

	if (isStdout)
		cout << "Enter size: ";

	if (!(is >> size))
	{
		cerr << errorMsg << endl;
		return is;
	}

	if (isStdout)
	{
		K = MagicSquare(size);
		return is;
	}

	MagicSquare K1(size);
	for (st i{}, n{ K1.getSize() }; i < n; ++i)
	{
		for (st j{}; j < n; ++j)
		{
			if (!(is >> K1.square[i][j]))
			{
				cerr << errorMsg << endl;
				return is;
			}
		}
	}
	K = K1;
	return is;
}

MagicSquare::size_type MagicSquare::getMaxNumber() const
{
	return n * n;
}

MagicSquare::size_type MagicSquare::getSize() const
{
	return n;
}

MagicSquare::size_type MagicSquare::getMagicConst() const
{
	return magicConst;
}

MagicSquare::size_type MagicSquare::calculateFieldWidth() const
{
	return size_type(to_string(getMaxNumber()).size());
}

