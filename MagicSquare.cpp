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

