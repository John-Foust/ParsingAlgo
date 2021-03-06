// SingleFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// SingleFile.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

struct report
{
	string Id;
	vector<string> sensors;
} report;

int main()
{
	string row, sensorId, sensorDef, sensorVal;
	string fileName = ""; string fileEnd = "_0";
	vector<struct report> reports;
	vector<string> fileList;
	vector<string> tempFileList;
	ifstream sensorFile;

	ofstream output("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/Outputs/MassiveSingleFile.csv");
	output << "Report_Id,Parsed_Value,File_Name" << endl;

	vector<struct report> finalReport = reports;

	for (int i = 0; i <= 165; i++) {
		fileName.clear();
		for (int j = 0; j < 5; j++) {
			fileName += "0";
		}

		if (i >= 10 && i < 100) {
			fileName.erase(fileName.begin() + 4);
		}
		else if (i >= 100 && i < 1000)
		{
			fileName.erase(fileName.begin() + 3, fileName.end());
		}
		else if (i >= 1000 && i < 10000) {
			fileName.erase(fileName.begin() + 2, fileName.end());
		}
		else if (i >= 10000 && i < 100000) {
			fileName.erase(fileName.begin() + 1, fileName.end());
		}
		else if (i >= 100000) {
			fileName.erase(fileName.begin(), fileName.end());
		}
		fileName += to_string(i) + "_0";

		sensorFile.open("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/DataElementLog/" + fileName + ".csv");
		
		cout << fileName << endl;
		while (getline(sensorFile, row)) {
			const auto comma = row.find(',');
			const auto commaTwo = row.find(',', comma + 1);

			sensorId = row.substr(0, comma);
			sensorVal = row.substr(commaTwo + 1, row.length());

			//cout << sensorId << "  " << sensorVal << "  " << fileName << endl;
			output << sensorId << "," << sensorVal << "," << fileName << endl; 
		}
		sensorFile.close();
	}
	output.close();
}

