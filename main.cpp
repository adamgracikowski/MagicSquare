#include <iostream>
#include "MagicGenerator.h"

using namespace std;

int main() {
#if 1 // Generator	
	MagicGenerator generator;
	generator.start();
#endif // Generator

#if 0 // MagicSquare Tests
	using st = MagicSquare::size_type;
	st okCounter{}, testBegin = 3, testEnd = 100, testCases = testEnd - testBegin + 1;
	for (st i{ testBegin }; i <= testEnd; ++i) {
		MagicSquare K(i);
		bool c{ K.isOrdinaryMagic() };
		if (c) okCounter++;
		cout << "Test " << K.getSize() << ": " << (c ? "ok" : "FAILURE") << endl;
	}
	cout << endl << "Tests result: " << (okCounter * 100 / testCases) << "% correct." << endl;
#endif // MagicSquare Tests
}