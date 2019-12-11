#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include "Lexer.h"
#include "Tokens.h"
#include "parser.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	Lexer activate(argv[1]);

	parser parsing;
	parsing.setvector(activate.getVector());
	parsing.startParser();

	Interpreter interpreter = Interpreter(parsing);
	interpreter.evalQueries();

	return 0;
}