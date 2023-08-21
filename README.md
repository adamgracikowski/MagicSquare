# Magic Square:

The main incentive for this project was an assignment given to my friend as a part of a discrete mathematics academic course that he attended to.

## Table of Contents:

- [What is a Magic Square?](#what-is-a-magic-square?)
- [Classification of Magic Squares](#classification-of-magic-squares)
- [About the Implementation](#about-the-implementation)
- [Features of the MagicSquare class](#features-of-the-magicsquare-class)
- [Usage of the MagicGenerator class](#usage-of-the-magicgenerator-class)
- [Author](#author)
- [Contributing](#contributing)
- [Show your support](#show-your-support)

## [What is a Magic Square?](https://en.wikipedia.org/wiki/Magic_square)

A Magic Square is a square array of numbers consisting of the distinct positive integers 1, 2, ..., n^2^  arranged such that the sum of the n numbers in any horizontal, vertical, or main diagonal line is always the same number, known as the magic constant.
Magic Squares have a long history, dating back to at least 190 BCE in China. At various times they have acquired occult or mythical significance, and have appeared as symbols in works of art.
As such, Magic Square problems are part of [recreational mathematics](https://en.wikipedia.org/wiki/Recreational_mathematics).

<p align="center">
<img src="https://mathworld.wolfram.com/images/eps-svg/MagicSquare_800.svg" alt="Magic Square example" />
</p>

## Classification of Magic Squares:

Magic Squares are generally classified according to their order n as:
- ***Odd*** -  if n is odd, 
- ***Doubly even*** - if n is a multiple of 4, 
- ***Singly even*** - if n is even but not divisible by 4.

This classification is based on different techniques required to construct such squares.  

Magic Squares can also be classified according to their properties. **Semi-magic Square** is a square array which rows and columns sum to give the magic constant. **Ordinary Magic Square** is a square array which any horizontal, vertical, or main diagonal line is always the magic constant.

## About the Implementation:

The `MagicSquare` class makes up the core of the implementation. As for the data structure used, the STL's `std::vector` was chosen due to the effective random element access and move semantics.

To construct the Magic Square for odd values of n, [Siamese method](https://en.wikipedia.org/wiki/Siamese_method) was used and for doubly even values of n [Strachey method](https://en.wikipedia.org/wiki/Strachey_method_for_magic_squares) algorithm was implemented. Constructing the Magic Square for singly even values of n involved a combination of [Siamese method](https://en.wikipedia.org/wiki/Siamese_method) and the method described in the following [article](https://www.wikihow.com/Solve-a-Magic-Square).

`MagicGenerator` class allows the user to interactively play with properties of the Magic Square - change its size, shuffle rows or columns and most importantly save it to a text file for later use.

## Features of the MagicSquare class:

All the public methods of the `MagicSquare` class with a short explanation are correlated in the tables below:

| Member function: | Explanation: |
|---|---|
|**Constructors:**||
|`explicit MagicSquare(size_type n = defaultSize)`|Default constructor with the `defaultSize` of `6`.|
|`MagicSquare(const MagicSquare&) = default`|Default copy constructor|
|`MagicSquare(MagicSquare&&) = default`|Default move Constructor|
|**Destructor:**||
|`~MagicSquare() = default`|Default destructor|
|**Assignment operators:**||
|`MagicSquare& operator=(const MagicSquare&) = default`|Default copy assignment operator.|
|`MagicSquare& operator=(MagicSquare&&) = default`|Default move assignment operator.|
|**Getters:**||
|`size_type getSize() const`|Returns the size of the square.|
|`size_type getMagicConst() const`|Returns the magic constant.|
|`size_type getMaxNumber() const`|Returns the biggest number that the square contains, that is n^2^.|
|`value_type getRowSum(size_type idx) const`|Returns the sum of the elements int the given row.|
|`value_type getColumnSum(size_type idx) const`|Returns the sum of the elements int the given column.|
|`value_type getForwardDiagonalSum() const`|Returns the sum of the elements int the forward diagonal.|
|`value_type getBackDiagonalSum() const`|Returns the sum of the elements int the back diagonal.|
|**Modifiers:**||
|`bool moveNumber(value_type number, position_type posiiton)`|Changes the position of the `number` to `position` provided that the `number` is found and the `position` is correct. Otherwise, it does nothing.|
|`void shuffleRows()`|Randomly rearranges rows of the square.|
|`void shuffleColumns()`|Randomly rearranges rows of the square.|
|`void transpose()`|Self-explanatory.|
|`void swapColumns(size_type colIdx1, size_type colIdx2)`|Swaps column under `col1Idx` with a column under `col2Idx`.|
|`void swapRows(size_type rowIdx1, size_type rowIdx2)`|Swaps row under `row1Idx` with a column under `row2Idx`.|
|**Overloaded operators:**||
|`const row_type& operator[](size_type rowIdx) const`|Allows for use of the table notation on a `MagicSquare` object i.e. `square[1][2]`.|
|`friend std::ostream& operator<<(std::ostream& os, const MagicSquare& K)`|Overloaded operator<<.|
|`friend std::istream& operator>>(std::istream& is, MagicSquare& K)`|Overloaded operator>>.|
|**Other:**||
|`bool isOrdinaryMagic() const`|Returns `true` if the square is ordinary magic.|
|`bool isSemiMagic() const`|Returns `true` if the square is semi-magic.|
|`position_type findNumber(value_type number) const`|Returns a position of `number` in a square. If the `number` is not found, returns `MagicSquare::noPosition`|
|`bool saveToTextFile(std::string filename) const`|Appends the contents of the square to the text file `filename`. If the file doesn't exist, it is created. Returns `true`, if the operation was successful.|
|`bool saveToBinaryFile(std::string filename) const`|Appends the contents of the square to the binary file `filename`. If the file doesn't exist, it is created. Returns `true`, if the operation was successful.|

|Member types:| Explanation:|
|---|---|
|`value_type`|`int`|
|`reference`|`int&`|
|`const_reference`|`const int&`|
|`row_type`|`std::vector<int>`|
|`container_type`|`std::vector<std::vector<int>>`|
|`size_type`|`int`|
|`position_type`|`std::pair<int, int>`|

## Usage of the MagicGenerator class:

The MagicGenerator class provides a single public method: `void start()`, which is responsible for displaying interactive menu and managing user choices.
The following snippet of code shows an exemplary usage of the class.

```cpp
#include "MagicGenerator.h"

int main() {	
	MagicGenerator generator;
	generator.start();
}
```
The result of running the program is as follows:

![Screenshot]()

## Author:

My GitHub: [@adamgracikowski](https://github.com/adamgracikowski)

## Contributing:

All contributions, issues, and feature requests are welcome! 🤝

## Show your support:

Give a ⭐️ if you like this project and its documentation!
