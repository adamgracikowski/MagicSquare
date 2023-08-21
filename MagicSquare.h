#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <utility>

class MagicSquare
{
public:
	friend class MagicGenerator;
	friend std::ostream& operator<<(std::ostream& os, const MagicSquare& K);
	friend std::istream& operator>>(std::istream& is, MagicSquare& K);

	/* Member types: */
	using value_type = int;
	using reference = int&;
	using const_reference = const int&;
	using row_type = std::vector<int>;
	using container_type = std::vector<std::vector<int>>;
	using size_type = int;
	using position_type = std::pair<int, int>;

	static const position_type noPosition;

	/* Constructors: */
	explicit MagicSquare(size_type n = defaultSize);
	MagicSquare(const MagicSquare&) = default;
	MagicSquare(MagicSquare&&) = default;
	~MagicSquare() = default;

	MagicSquare& operator=(const MagicSquare&) = default;
	MagicSquare& operator=(MagicSquare&&) = default;

	/* Const member functions: */
	size_type getSize() const;
	size_type getMagicConst() const;
	size_type getMaxNumber() const;

	bool isOrdinaryMagic() const;
	bool isSemiMagic() const;

	value_type getRowSum(size_type idx) const;
	value_type getColumnSum(size_type idx) const;
	value_type getForwardDiagonalSum() const;
	value_type getBackDiagonalSum() const;

	position_type findNumber(value_type number) const;

	const row_type& operator[](size_type rowIdx) const;

	bool saveToTextFile(std::string filename) const;
	bool saveToBinaryFile(std::string filename) const;

	/* Modifiers: */
	bool moveNumber(value_type number, position_type posiiton);
	void shuffleRows();
	void shuffleColumns();
	void transpose();
	void swapColumns(size_type colIdx1, size_type colIdx2);
	void swapRows(size_type rowIdx1, size_type rowIdx2);
private:
	container_type square;
	size_type n;
	size_type magicConst;
	static const size_type defaultSize { 6 };

	/* Filling algorithms: */
	void fillSquare();

	bool isValidIdx(size_type idx) const;
	bool isValidPosition(position_type position) const;
	bool isValidNumber(value_type number) const;

	size_type calculateFieldWidth() const;

};