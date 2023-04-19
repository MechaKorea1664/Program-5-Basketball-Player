#include <iostream>
#include <vector>
using namespace std;

// Stores the index of double quote pairs.
struct quotePosPair{
	int startPos;
	int endPos;
};

// Reads CSV files. Able to find commas inside double quotes.
vector<vector<string>> readFromCSV(string filename);