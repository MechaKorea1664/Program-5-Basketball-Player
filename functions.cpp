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
		commaPos.clear();
		commaPos.push_back(0);
		quotePairVector.clear();
		csvLine.clear();
		getline(inFS, line);

		bool quoteStart = false;
		if (line.length() != 0) {
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == ',')
					commaPos.push_back(i);
				else if (line[i] == '\"' && quoteStart == false) {
					quoteStart = true;
					quotePair.startPos = i;
				}
				else if (line[i] == '\"' && quoteStart == true) {
					quoteStart = false;
					quotePair.endPos = i;
					quotePairVector.push_back(quotePair);
				}
			}

			//cout << "commaPos: " << endl;
			//printIntVetor(commaPos);
			//cout << "quotePair: " << endl;
			//for (int i = 0; i < quotePairVector.size(); i++) {
			//	cout << "index " << i << " : " << quotePairVector[i].startPos << " to " << quotePairVector[i].endPos << endl;
			//}

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
				if (line[commaPos[i]] == '\"') {
					continue;
				}

				if (isInQuote) {
					csvLine.push_back(line.substr(quoteStartPos + 1, quoteEndPos - quoteStartPos - 1));
					isInQuote = false;
					continue;
				}
				else {
					int commaStartPos;
					if (isFirst) {
						commaStartPos = 0;
						isFirst = false;
					}
					else {
						commaStartPos = commaPos[i] + 1;
					}
					if (i + 1 <= commaPos.size() - 1) {
						csvLine.push_back(line.substr(commaStartPos, commaPos[i + 1] - commaStartPos));
						continue;
					}
					else {
						csvLine.push_back(line.substr(commaStartPos));
						continue;
					}
				}
			}
			output.push_back(csvLine);
		}
	}
	inFS.close();
	return output;
}