#include "pch.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
	string row;
	string header;
	vector<string> backwards;
	string assetid;

	ifstream fileOfAssets("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/Outputs/fileOfAssets.csv");
	if (!fileOfAssets.is_open()) {
		cout << "File could not be found: fileofAssets." << endl;
		return 0;
	}

	while (getline(fileOfAssets, assetid))
	{
		ifstream reverse("Some link that works/" + assetid + ".csv");
		if (!reverse.is_open()) {
			cout << "File could not be found: " << assetid << ".csv" << "\n";
			return 0;
		}
		ofstream output("C:/Users/Me/Desktop/file" + assetid + ".csv");
		getline(reverse, header);
		if (reverse.is_open()) {
			while (getline(reverse, row)) {
				backwards.push_back(row);
			}
		}
		output << header << "\n";
		for (int i = 0; i < backwards.size(); i++) {
			output << backwards.back() << "\n";
			backwards.pop_back();
		}
		output.close();
		reverse.close();
	}
	fileOfAssets.close();
}


