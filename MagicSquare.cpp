#include "MagicSquare.h"
#include "SquareExceptions.h"

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

bool MagicSquare::isOrdinaryMagic() const
{
	value_type magicConst{ getMagicConst() };
	return (isSemiMagic() &&
		getForwardDiagonalSum() == magicConst &&
		getBackDiagonalSum() == magicConst);
}

bool MagicSquare::isSemiMagic() const
{
	value_type magicConst{ getMagicConst() };
	for (size_type i{}, n{ getSize() }; i < n; ++i)
	{
		if (getRowSum(i) != magicConst || getColumnSum(i) != magicConst)
			return false;
	}
	return true;
}

MagicSquare::value_type MagicSquare::getRowSum(size_type idx) const
{
	if (!isValidIdx(idx))
		throw InvalidIdx(idx, getSize());

	return accumulate(square[idx].begin(), square[idx].end(), 0);
}

MagicSquare::value_type MagicSquare::getColumnSum(size_type idx) const
{
	value_type result{};
	if (isValidIdx(idx))
	{
		for (size_type i{}, n{ getSize() }; i < n; ++i)
		{
			result += square[i][idx];
		}
	}
	else
		throw InvalidIdx(idx, getSize());
	return result;
}

MagicSquare::value_type MagicSquare::getForwardDiagonalSum() const
{
	value_type result{};
	for (size_type i{}, n{ getSize() }, j{ n - 1 }; i < n; ++i, --j)
	{
		result += square[i][j];
	}
	return result;
}

MagicSquare::value_type MagicSquare::getBackDiagonalSum() const
{
	value_type result{};
	for (size_type i{}, n{ getSize() }; i < n; ++i)
	{
		result += square[i][i];
	}
	return result;
}

MagicSquare::size_type MagicSquare::calculateFieldWidth() const
{
	return size_type(to_string(getMaxNumber()).size());
}

bool MagicSquare::isValidIdx(size_type idx) const
{
	return (idx >= 0 && idx < getSize());
}

bool MagicSquare::isValidPosition(position_type position) const
{
	return (isValidIdx(position.first) && isValidIdx(position.second));
}

bool MagicSquare::isValidNumber(value_type number) const
{
	return (number >= 1 && number <= getMaxNumber());
}

bool MagicSquare::saveToTextFile(std::string filename) const
{
	ofstream file(filename, ios::out | ios::app);
	if (!file)
		return false;
	file << *this << endl;
	file.close();
	return true;
}

bool MagicSquare::saveToBinaryFile(std::string filename) const
{
	ofstream file(filename, ios::out, ios::binary);
	if (!file)
		return false;
	if (file.write((char*)&(*this), sizeof(*this)))
	{
		file.close();
		return true;
	}
	file.close();
	return false;
}

bool MagicSquare::moveNumber(value_type number, position_type position)
{
	if (isValidPosition(position) && isValidNumber(number))
	{
		position_type positionOfNumber = findNumber(number);
		swapRows(position.first, positionOfNumber.first);
		swapColumns(position.second, positionOfNumber.second);
		return true;
	}
	return false;
}

void MagicSquare::shuffleRows()
{
	random_shuffle(square.begin(), square.end());
}

void MagicSquare::shuffleColumns()
{
	transpose();
	shuffleRows();
	transpose();
}

void MagicSquare::transpose()
{
	for (size_type i{}, n{ getSize() }; i < n; ++i)
	{
		for (size_type j{ i + 1 }; j < n; ++j)
		{
			swap(square[i][j], square[j][i]);
		}
	}
}

void MagicSquare::swapColumns(size_type colIdx1, size_type colIdx2)
{
	if (isValidIdx(colIdx1) && isValidIdx(colIdx2))
	{
		for (size_type i{}, n{ getSize() }; i < n; ++i)
		{
			swap(square[i][colIdx1], square[i][colIdx2]);
		}
	}
}

void MagicSquare::swapRows(size_type rowIdx1, size_type rowIdx2)
{
	if (isValidIdx(rowIdx1) && isValidIdx(rowIdx2))
	{
		swap(square[rowIdx1], square[rowIdx2]);
	}
}
