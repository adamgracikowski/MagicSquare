#include "MagicGenerator.h"

using namespace std;

vector<string> MagicGenerator::menuOptions = vector<string>({
	"END", "MOVE NUMBER",
	"FIND NUMBER", "CHANGE SIZE",
	"SAVE TO TEXT FILE", "TRANSPOSE",
	"SHUFFLE ROWS", "SHUFFLE COLUMNS",
	"PRINT SQUARE", "CHECK IF ORDINARY MAGIC",
	"CHECK IF SEMI MAGIC"
	});

MagicGenerator::MagicGenerator(size_type starting_size)
	: K(starting_size) {}

void MagicGenerator::start()
{
	size_type choice{ 1 };
	string welcomeMsg("--- WELCOME TO MAGIC SQUARE GENERATOR ---");

	cout << welcomeMsg << endl;
	do {
		printLine(size_type(welcomeMsg.size()));
		cout << "What do you want to do?" << endl;

		displayMenuOptions();
		try {
			choice = readOptionFromUser();

			switch (choice) {
			case MOVE_NUMBER:
				moveNumber();
				break;
			case FIND_NUMBER:
				findNumber();
				break;
			case CHANGE_SIZE:
				changeSize();
				break;
			case SAVE_TO_TEXT_FILE:
				saveToTextFile();
				break;
			case TRANSPOSE:
				K.transpose();
				break;
			case SHUFFLE_ROWS:
				K.shuffleRows();
				break;
			case SHUFFLE_COLUMNS:
				K.shuffleColumns();
				break;
			case PRINT_SQUARE:
				printSquare();
				break;
			case CHECK_IF_ORDINARY_MAGIC:
				cout << boolalpha << K.isOrdinaryMagic() << endl;
				break;
			case CHECK_IF_SEMI_MAGIC:
				cout << boolalpha << K.isSemiMagic() << endl;
				break;
			case END:
				stop();
				break;
			}
		}
		catch (const InvalidInput& e) {
			e.what();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (choice);
}

void MagicGenerator::stop() const noexcept
{
	cout << "END..." << endl;
}

void MagicGenerator::displayMenuOptions() const noexcept
{
	for (size_type i{}; i < menuOptions.size(); ++i)
		cout << i << "." << menuOptions[i] << endl;
}

MagicGenerator::size_type MagicGenerator::readOptionFromUser() const
{
	size_type choice{};
	cout << "Enter an option number: ";
	if (!(cin >> choice)) throw InvalidInput("Invalid Input.");
	if (choice < 0 || choice >= menuOptions.size()) throw InvalidInput("Option number out of range.");
	return choice;
}

void MagicGenerator::moveNumber()
{
	value_type number{};
	size_type newRow{}, newCol{};

	number = readInputFromUser<value_type>("Enter a number to be moved: ");
	newRow = readInputFromUser<size_type>("Enter a new row index: ");
	newCol = readInputFromUser<size_type>("Enter a new column index: ");

	if (!K.moveNumber(number, position_type(newRow, newCol))) {
		cout << "The relocation of " << number << " was unsuccessful." << endl;
	}
	else {
		cout << "The number " << number << " was moved to position: ("
			<< newRow << "," << newCol << ")" << endl;
	}
}

void MagicGenerator::findNumber()
{
	value_type number{};
	position_type positionOfNumber;

	number = readInputFromUser<value_type>("Enter a number to be found: ");

	if ((positionOfNumber = K.findNumber(number)) == MagicSquare::noPosition) {
		cout << "The number " << number << " was not found." << endl;
	}
	else {
		cout << "The number " << number << " was found at: "
			<< "(" << positionOfNumber.first << "," << positionOfNumber.second << ")" << endl;
	}
}

void MagicGenerator::changeSize()
{
	size_type size{};

	size = readInputFromUser<size_type>("Enter a new size: ");
	if (size < 1) cout << "The size must be a positive integer." << endl;
	else {
		K = MagicSquare(size);
		cout << "The size was changed." << endl;
	}
}

void MagicGenerator::saveToTextFile()
{
	string filename{};
	filename = readInputFromUser<string>("Enter a file name: ");

	if (K.saveToTextFile(filename)) {
		cout << "Your Magic Square was saved in " << filename << endl;
	}
	else cout << "Something went wrong." << endl;
}

void MagicGenerator::printSquare() const
{
	cout << "This is your current Magic Square!" << endl
		<< endl << K << endl;
}

void MagicGenerator::printLine(size_type numberOfChars, char c) const noexcept
{
	while (numberOfChars--) cout << c;
	cout << endl;
}
