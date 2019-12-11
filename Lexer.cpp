#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctype.h>
#include "Lexer.h"
#include "Tokens.h"

using namespace std;

Lexer::Lexer(char* readMe) {


	ifstream myfile;
	myfile.open(readMe);

	char item;
	int line_num = 1;
	int hold_num = 0;
	int i = 0;
	bool done = false;

	string currentString = "";
	string temp;
	Tokens t;

	while (myfile.get(item)) {

		if (isalpha(item)) {

			while (isalnum(item)) {

				currentString = currentString + item;
				myfile.get(item);
			}
			if (currentString == "Queries")
			{
				t = Tokens("QUERIES", currentString, line_num);
				myTokens.push_back(t);
				currentString == "";
				currentString.clear();
			}
			else if (currentString == "Rules")
			{
				t = Tokens("RULES", currentString, line_num);
				myTokens.push_back(t);
				currentString == "";
				currentString.clear();
			}
			else if (currentString == "Facts")
			{
				t = Tokens("FACTS", currentString, line_num);
				myTokens.push_back(t);
				currentString == "";
				currentString.clear();
			}
			else if (currentString == "Schemes")
			{
				t = Tokens("SCHEMES", currentString, line_num);
				myTokens.push_back(t);
				currentString == "";
				currentString.clear();
			}
			else if (item != '\'') {
				t = Tokens("ID", currentString, line_num);
				myTokens.push_back(t);
				currentString == "";
				currentString.clear();
			}

		}

		switch (item) {

		case '+':
			t = Tokens("ADD", "+", line_num);
			myTokens.push_back(t);

			break;
		case '*':
			t = Tokens("MULTIPLY", "*", line_num);
			myTokens.push_back(t);

			break;
		case ':':

			if (myfile.peek() == '-') {
				t = Tokens("COLON_DASH", ":-", line_num);
				myTokens.push_back(t);
				myfile.get(item);
			}
			else {

				t = Tokens("COLON", ":", line_num);
				myTokens.push_back(t);
			}

			break;
		case '(':
			t = Tokens("LEFT_PAREN", "(", line_num);
			myTokens.push_back(t);

			break;
		case ')':

			t = Tokens("RIGHT_PAREN", ")", line_num);
			myTokens.push_back(t);

			break;
		case '?':
			t = Tokens("Q_MARK", "?", line_num);
			myTokens.push_back(t);

			break;
		case '.':
			t = Tokens("PERIOD", ".", line_num);
			myTokens.push_back(t);

			break;
		case ',':
			t = Tokens("COMMA", ",", line_num);
			myTokens.push_back(t);
			break;

		case '#':

			currentString = currentString + item;
			myfile.get(item);
			hold_num = line_num;

			if (item == '|') {

				while (done == false) {

					if (item == '\n') {

						line_num++;
					}

					currentString = currentString + item;
					myfile.get(item);
					if (item == '|' && myfile.peek() == '#') {

						currentString = currentString + item;
						done = true;
					}

					if (myfile.eof()) {

						// t = Tokens("UNDEFINED", currentString, hold_num);
						// myTokens.push_back(t);
						currentString = "";
						currentString.clear();
						hold_num = 0;
						break;
					}

				}
				if (item == '|' && myfile.peek() == '#') {

					myfile.get(item);
					currentString = currentString + item;
					//t = Tokens("COMMENT", currentString, hold_num);
					//myTokens.push_back(t);
					currentString == "";
					currentString.clear();
					hold_num = 0;
					done = false;
					break;


				}
				break;

			}
			else {

				while (item != '\n') {
					currentString = currentString + item;
					myfile.get(item);
				}
				//t = Tokens("COMMENT", currentString, hold_num);
				//myTokens.push_back(t);
				currentString == "";
				currentString.clear();
				myfile.putback(item);
				hold_num = 0;
				break;
			}


		case '\'':

			i++;
			hold_num = line_num;
			currentString = currentString + item;
			myfile.get(item);

			if (item == '\n') {
				line_num++;

				while (done == false) {

					if (myfile.eof()) {
						currentString = currentString + item;
						t = Tokens("UNDEFINED", currentString, hold_num);
						myTokens.push_back(t);
						currentString == "";
						currentString.clear();
						hold_num = 0;
						done = false;
						i = 0;
						break;
					}

					if (item == '\'') {

						i++;
					}
					currentString = currentString + item;
					myfile.get(item);

					if (item == '\n' && myfile.peek() == '\n') {

						done = true;
					}

					if (item == '\n') {

						line_num++;
					}

				}
				if (i % 2 != 0) {

					currentString = currentString + item;
					t = Tokens("UNDEFINED", currentString, hold_num);
					myTokens.push_back(t);
					currentString == "";
					currentString.clear();
					hold_num = 0;
					done = false;
					i = 0;
					break;

				}
				if (myfile.peek() == EOF) {
					break;
				}
				t = Tokens("STRING", currentString, hold_num);
				myTokens.push_back(t);
				currentString == "";
				currentString.clear();
				hold_num = 0;
				done = false;
				i = 0;
				break;

			}
			if (item == '\'') {

				i++;
				currentString = currentString + item;
				myfile.get(item);

				while (item == '\'') {
					i++;
					currentString = currentString + item;
					myfile.get(item);
				}
				if (item == '\n' && i % 2 == 0) {
					line_num++;
					t = Tokens("STRING", currentString, hold_num);
					myTokens.push_back(t);
					currentString == "";
					currentString.clear();
					hold_num = 0;
					done = false;
					i = 0;
					break;

				}
				else if (item != '\'' && i % 2 == 0) {
					t = Tokens("STRING", currentString, hold_num);
					myTokens.push_back(t);
					currentString == "";
					currentString.clear();
					myfile.putback(item);
					hold_num = 0;
					done = false;
					i = 0;
					break;

				}
			}
			if (i == 1) {

				while (item != '\'') {
					currentString = currentString + item;
					myfile.get(item);

					if (item == '\'' && myfile.peek() == '\'') {

						currentString = currentString + item;
						myfile.get(item);
						currentString = currentString + item;
						myfile.get(item);

					}
				}
				currentString = currentString + item;
				t = Tokens("STRING", currentString, hold_num);
				myTokens.push_back(t);
				currentString == "";
				currentString.clear();
				hold_num = 0;
				i = 0;
				done = false;
				break;



			}

			while (myfile.peek() != '\n') {

				currentString = currentString + item;
				myfile.get(item);
			}
			currentString = currentString + item;
			t = Tokens("STRING", currentString, hold_num);
			myTokens.push_back(t);
			currentString == "";
			currentString.clear();
			hold_num = 0;
			i = 0;
			done = false;
			break;


		case '\n':
			line_num++;

			break;
		case ' ':
			break;
		case '\t':
			break;
		default:
			currentString = currentString + item;

			t = Tokens("UNDEFINED", currentString, line_num);
			myTokens.push_back(t);
			currentString = "";
			cout << currentString;
			break;
		}


	}
	t = Tokens("EOF", "", line_num);
	myTokens.push_back(t);

	int k = myTokens.size();
	for (int i = 0; i < k; i++) {

		myTokens[i].toString();

	}

	// cout << "Total Tokens = " << k << "\n";
}

vector <Tokens> Lexer::getVector() {

	return myTokens;
}
