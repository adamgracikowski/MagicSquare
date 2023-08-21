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

MagicSquare::position_type MagicSquare::findNumber(value_type number) const
{
	if (isValidNumber(number))
	{
		for (size_type i{}, n{ getSize() }; i < n; ++i)
		{
			for (size_type j{}; j < n; ++j)
			{
				if (square[i][j] == number)
					return position_type(i, j);
			}
		}
	}
	return noPosition;
}

const MagicSquare::row_type& MagicSquare::operator[](size_type rowIdx) const
{
	if (!isValidIdx(rowIdx))
		throw InvalidIdx(rowIdx, getSize());
	return square[rowIdx];
}

MagicSquare::size_type MagicSquare::calculateFieldWidth() const
{
	return size_type(to_string(getMaxNumber()).size());
}

void MagicSquare::fillSquare()
{
	if (n % 4 == 0)
		fillDoublyEven();
	else if (n % 4 == 2)
		fillSinglyEven();
	else
		fillOdd();
}

void MagicSquare::fillDoublyEven()
{
	value_type lowerBound{ 1 }, upperBound{ getMaxNumber() };

	for (size_type i{}, n{ getSize() }; i < n; ++i)
	{
		for (size_type j{}; j < n; ++j)
		{
			if (isToBeFilled(position_type(i, j)))
				square[i][j] = lowerBound;
			else
				square[i][j] = upperBound;
			lowerBound++;
			upperBound--;
		}
	}
}

void MagicSquare::fillSinglyEven()
{
	using st = size_type;

	st n{ getSize() };

	if (n == 2)
	{
		square[0][0] = 1;
		square[0][1] = 3;
		square[1][0] = 4;
		square[1][1] = 2;
		return;
	}

	st quadrantSize = n / 2;
	value_type quadrantIncrement = quadrantSize * quadrantSize;

	MagicSquare A(quadrantSize);
	A.fillOdd(1);
	MagicSquare B(quadrantSize);
	B.fillOdd(1 + quadrantIncrement);
	MagicSquare C(quadrantSize);
	C.fillOdd(1 + 2 * quadrantIncrement);
	MagicSquare D(quadrantSize);
	D.fillOdd(1 + 3 * quadrantIncrement);

	st k = (n - 2) / 4;
	for (st i{}; i < k; ++i)
	{
		A.swapColumnsWithOther(i, D, i);
	}

	for (st i{}; i < k - 1; ++i)
	{
		C.swapColumnsWithOther(quadrantSize - 1 - i, B, quadrantSize - 1 - i);
	}

	st quadrantCenter = (quadrantSize - 1) / 2;

	swap(A[quadrantCenter][0],
		D[quadrantCenter][0]);
	swap(A[quadrantCenter][quadrantCenter],
		D[quadrantCenter][quadrantCenter]);

	insertSubsquare(position_type(0, 0), A);
	insertSubsquare(position_type(0, n / 2), C);
	insertSubsquare(position_type(n / 2, 0), D);
	insertSubsquare(position_type(n / 2, n / 2), B);
}

void MagicSquare::fillOdd(value_type lowerBound)
{
	for (row_type& row : square)
		std::fill(row.begin(), row.end(), 0);

	size_type i{ 1 }, j{ size_type((n + 1) / 2 - 2) };

	value_type maxNumber{ getMaxNumber() };
	for (size_type k{}, n{ getSize() }; k < maxNumber; ++k)
	{
		position_type nowaPozycja = findNewPosition(position_type(i, j));
		i = nowaPozycja.first;
		j = nowaPozycja.second;
		square[i][j] = lowerBound++;
	}
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

MagicSquare::position_type MagicSquare::findNewPosition(position_type oldPosition) const
{
	size_type nextI{ oldPosition.first - 1 }, nextJ{ oldPosition.second + 1 };
	if (nextI == noPosition.first)
		nextI = getSize() - 1;
	if (nextJ == getSize())
		nextJ = 0;
	if (square[nextI][nextJ] != 0)
	{
		nextI = oldPosition.first + 1;
		nextJ = oldPosition.second;
	}
	return position_type(nextI, nextJ);
}

bool MagicSquare::isToBeFilled(position_type position) const
{
	size_type i{ position.first }, j{ position.second };
	return (((i >= 0 && i < n / 4) || (i > 3 * n / 4 - 1 && i < n)) &&
		((j >= 0 && j < n / 4) || (j > 3 * n / 4 - 1 && j < n)) ||
		((i > n / 4 - 1 && i <= 3 * n / 4 - 1 && j > n / 4 - 1 && j < 3 * n / 4)));
}

MagicSquare::row_type& MagicSquare::operator[](size_type rowIdx)
{
	if (!isValidIdx(rowIdx))
		throw InvalidIdx(rowIdx, getSize());
	return square[rowIdx];
}

void MagicSquare::swapColumnsWithOther(size_type colIdx1, MagicSquare& other, size_type colIdx2)
{
	for (size_type i{ colIdx1 }, n{ getSize() }; i <= colIdx2; ++i)
	{
		for (size_type j{}; j < n; ++j)
			swap(square[j][i], other.square[j][i]);
	}
}

void MagicSquare::insertSubsquare(position_type position, MagicSquare& sub)
{
	size_type i1{}, j1{};
	for (size_type i{ position.first }; i < position.first + sub.n; ++i, ++i1)
	{
		for (size_type j{ position.second }; j < position.second + sub.n; ++j, ++j1)
		{
			square[i][j] = sub.square[i1][j1];
		}
		j1 = 0;
	}
}