#pragma once
#include "MagicSquare.h"

#include <exception>
#include <sstream>
#include <string>

class SquareException : public std::exception
{
public:
	SquareException() = default;
	virtual const char* what() const noexcept = 0;
};

class InvalidIdx : public SquareException
{
public:
	explicit InvalidIdx(MagicSquare::size_type idx, MagicSquare::size_type squareSize)
	{
		std::stringstream msg{};
		msg << "Invalid Index: " << idx << " out of range [" << 0 << ", " << (squareSize - 1) << "].";
		this->msg = msg.str();
	}
	virtual const char* what() const noexcept
	{
		std::cout << msg << std::endl; return msg.c_str();
	}
private:
	std::string msg;
};