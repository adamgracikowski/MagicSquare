#pragma once
#include "magicSquare.h"
#include "SquareExceptions.h"

#include <vector>
#include <string>

class MagicGenerator
{
public:
	/* Member types: */
	using size_type = MagicSquare::size_type;
	using value_type = MagicSquare::value_type;
	using position_type = MagicSquare::position_type;

	/* Constructors: */
	explicit MagicGenerator(size_type starting_size = MagicSquare::defaultSize);
	MagicGenerator(const MagicGenerator&) = delete;
	MagicGenerator& operator=(const MagicGenerator&) = delete;

	void start();
private:
	MagicSquare K;
	static std::vector<std::string> menuOptions;
	enum options {
		END, MOVE_NUMBER, FIND_NUMBER,
		CHANGE_SIZE, SAVE_TO_TEXT_FILE, TRANSPOSE,
		SHUFFLE_ROWS, SHUFFLE_COLUMNS, PRINT_SQUARE,
		CHECK_IF_ORDINARY_MAGIC, CHECK_IF_SEMI_MAGIC
	};

	void stop() const noexcept;
	void displayMenuOptions() const noexcept;
	size_type readOptionFromUser() const;

	template<typename T>
	T readInputFromUser(std::string prompt) const;

	void moveNumber();
	void findNumber();
	void changeSize();
	void saveToTextFile();
	void printSquare() const;
	void printLine(size_type numberOfChars, char c = '-') const noexcept;
};

template<typename T>
inline T MagicGenerator::readInputFromUser(std::string prompt) const
{
	T number{};
	std::cout << prompt;
	if (!(std::cin >> number)) {
		throw InvalidInput("The input was not a number.");
	}
	return number;
}

template<>
inline std::string MagicGenerator::readInputFromUser(std::string prompt) const
{
	std::string input{};
	std::cout << prompt;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (!getline(std::cin, input)) throw InvalidInput("Error while reading a string.");
	return input;
}
