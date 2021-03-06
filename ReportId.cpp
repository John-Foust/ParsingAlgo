// ReportOrganizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// ReportOrganizer.cpp : This file contains the 'main' function. Program execution begins and ends there.

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
	long long int s; long long int r;
	string row; string innerRow;
	string reportId; string sensor; string definition;
	string fileName = ""; string fileEnd = "_0";
	vector<struct report> reports;
	vector<string> fileList;
	vector<string> tempFileList;
	ifstream sensorFile;
	string sensorId, sensorDef, sensorVal;

	ifstream reportsFile("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/12239to35k_transmissionids.csv");	//location of the needed file
	//will return if the file cannot be found or opened
	if (!reportsFile.is_open()) {
		cout << "File could not be found." << endl;
		return 0;
	}

	//Outputting the info into a CSV file
	ofstream output("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/Outputs/reportIDfile 12239_to_35k.csv");
	ofstream output2("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/Outputs/notFoundIds 12239_to_35k.csv");

	output << "Report_Id,File_Name" << endl;
	int flag = 0;
	//Parsing through multiple CSV files, comparing Ids to reportId and inserting the sensors of matching Ids into the appropriate part of the struct
	vector<struct report> finalReport = reports;
	//cout << "before loop" << endl;
	for (int i = 165; i >= 0; i--) {
		fileName.clear();
		for (int j = 0; j < 5; j++) {
			fileName += "0";
		}
		//Changing the length of the preceding zeroes for the file names that have less
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
		//	cout << fileName << endl;
		fileList.push_back("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/DataElementLog/" + fileName + ".csv");
		//sensorFile.close();
	}

	//system("pause");
	//Grabs the reportId from the report file

	while (getline(reportsFile, row))
	{
		//const auto spot = row.find(',');
		//definition = row.substr(spot + 1, spot - 3);
		reportId = row;
		tempFileList = fileList;

		for (int i = tempFileList.size(); i > 0; i--)
		{
			flag = 0;
			string filename = tempFileList.back();
			sensorFile.open(filename);
			cout << " new file opened : " << filename << " searching for id: " << reportId << endl;

			while (getline(sensorFile, innerRow))
			{
				const auto innerSpot = innerRow.find(',');
				sensorId = innerRow.substr(0, innerSpot);
		//		cout << " report id : " << reportId << "  Sensor Id: " << sensorId << "   fileName   : " << filename << endl;
				r = stoll(reportId);
				s = stoll(sensorId);

				if (s > r)
				{
		//			cout << " report id : " << reportId << "  Sensor Id: " << sensorId << " Length differ, end loop" << endl;
					//	cout << r << "-  r  " << s << "- s " << endl;
					//system("pause");
					break;
				}

				if (reportId == sensorId) //reportId
				{
					cout << "found  " << reportId << endl;
					output << sensorId << "," << tempFileList.back() << endl; 
				//	system("pause");
						flag = 1;
					break;
				}
			}
			if (flag == 1)
				break;
			sensorFile.close();
			tempFileList.pop_back();
		}
		if (flag == 0)
			output2 << reportId << endl;
	}
	output.close();
	reportsFile.close();
}

