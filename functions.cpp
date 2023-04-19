#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "functions.h"

using namespace std;

vector<vector<string>> readFromCSV(string filename){
	ifstream inFS;
	inFS.open(filename);
	vector<int> commaPos;
	quotePosPair quotePair;
	vector<quotePosPair> quotePairVector;
	string line;
	vector<string> csvLine;
	vector<vector<string>> output;
	while (inFS.is_open() && !inFS.eof()) {
		// clear previously used vectors.
		commaPos.clear();
		commaPos.push_back(0);
		quotePairVector.clear();
		csvLine.clear();
		// Get a line from the CSV file.
		getline(inFS, line);

		bool quoteStart = false;
		if (line.length() != 0) {
			// Iterate through the line for commas and quotes.
			for (int i = 0; i < line.length(); i++) {
				// If comma is found, add the index to commaPos vector.
				if (line[i] == ',')
					commaPos.push_back(i);
				// if quote is found, and quote has not started yet, set quotePair's startPos to current index.
				else if (line[i] == '\"' && quoteStart == false) {
					quoteStart = true;
					quotePair.startPos = i;
				}
				// if quote is found, and quote had been started previously, set quotePair's endPos to current index.
				// Push the finished quotePair to quotePairVector.
				else if (line[i] == '\"' && quoteStart == true) {
					quoteStart = false;
					quotePair.endPos = i;
					quotePairVector.push_back(quotePair);
				}
			}
			// isFirst is a boolean that shows if the line starts with double quotes or not.
			bool isInQuote = false, isFirst = true;
			if (line[0] == '\"') {
				isFirst = false;
			}
			int quoteStartPos, quoteEndPos;
			for (int i = 0; i < commaPos.size(); i++) {
				for (int j = 0; j < quotePairVector.size(); j++) {
					// looks for any pairs of quotations.
					if (commaPos[i] > quotePairVector[j].startPos && commaPos[i] < quotePairVector[j].endPos) {
						isInQuote = true;
						quoteStartPos = quotePairVector[j].startPos;
						quoteEndPos = quotePairVector[j].endPos;
						break;
					}
				}
				// if there is a double quote at this index, ignore this index, move to next index in commaPos.
				if (line[commaPos[i]] == '\"') {
					continue;
				}

				// If comma is in quote, get substring between startPos and endPos of quotePosPair (struct declard in functions.h).
				if (isInQuote) {
					csvLine.push_back(line.substr(quoteStartPos + 1, quoteEndPos - quoteStartPos - 1));
					isInQuote = false;
					continue;
				}
				// If not in quote...
				else {
					int commaStartPos;
					// ... and if this is the first comma of this line, make sure substring is generated from index 0.
					if (isFirst) {
						commaStartPos = 0;
						isFirst = false;
					}
					// Or else, make sure substring does not include the comma by adding 1 to index.
					else {
						commaStartPos = commaPos[i] + 1;
					}
					// If this is not the last index, push back substring from this commma's index + 1 to index before the next comma.
					// Length is determined by the difference of two comma positions.
					if (i + 1 <= commaPos.size() - 1) {
						csvLine.push_back(line.substr(commaStartPos, commaPos[i + 1] - commaStartPos));
						continue;
					}
					// Or else, get the substring from this comma's index + 1 to the end of the line.
					else {
						csvLine.push_back(line.substr(commaStartPos));
						continue;
					}
				}
			}
			// After the lines are divded into substrings, add to output.
			output.push_back(csvLine);
		}
	}
	// Close file and return the output.
	inFS.close();
	return output;
}