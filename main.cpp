#include <iostream>
#include "calculator.h"

#define UNUSED(var) (void)(var)

using std::cout;
using std::endl;
using std::cin;


int main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	
	bool exitNow = false;
	char input[100];
	
	do {
		
		cout << "input expression: ";
		cin.getline(input,100);
		cin.clear();
		
		if (std::string(input) != "exit") {
			Calculator calc = input;
			if (calc.calculate()) {
				cout << "Result: " << calc.getResult() << endl;
			} else {
				cout << "Calculation error." << endl;
			}
		} else {
			exitNow = true;
		}
		
	} while (!exitNow);
	
	return 0;
}
