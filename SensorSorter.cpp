// SensorSorter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> assets;
	vector<int> finalAssets;
	string row, row1;
	int sensorNum = 0;
	int compare = 0;

	ifstream assetNames("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/SensorSorter/assetNames.csv");
	if (!assetNames.is_open()) 	{
		cout << "File not found!\n";
		return 0;
	}

	while (getline(assetNames, row)) {
		auto substring = row.substr(5, row.length());

		ifstream def1830("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/SensorSorter/"+ substring +"_1830SensorIds.csv");
		if (!assetNames.is_open()) {
			cout << "File not found!\n";
			return 0;
		}

		ifstream def1831("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/SensorSorter/" + substring + "_1831SensorIds.csv");
		if (!assetNames.is_open()) {
			cout << "File not found!\n";
			return 0;
		}

		ofstream output("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/SensorSorter/asset_" + substring + "_SensorIds.csv");

		while (getline(def1830, row1)) {
			assets.push_back(stoi(row1));
		}
		while (getline(def1831, row1)) {
			assets.push_back(stoi(row1));
		}

		sort(assets.begin(), assets.end());

		for (int i = assets.size(); i > 0; i--) {
			sensorNum = assets.front();
			if (sensorNum == compare)
			{}
			else{
				output << sensorNum << endl;
				cout << sensorNum << " is the current Sensor Id." << endl;
			}
			compare = sensorNum;
			assets.erase(assets.begin());
		}

		def1830.close();
		def1831.close();
		output.close();
	}
	assetNames.close();
}

