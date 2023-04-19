#include <iostream>
#include <vector>
using namespace std;

struct quotePosPair{
	int startPos;
	int endPos;
};

vector<vector<string>> readFromCSV(string filename);