// assetFormatter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string getVal(string *row);

int main()
{
	// file variables needed
	ifstream assetInput;
	ifstream sensorInput;
	ofstream output; 

	// Variables to store information from assetInput files
	string row;
	string reportId;
	string timestamp;
	string def;
	string sensorId;
	string sensorVal;
	string fileName;
	string rowNum;
	string currentReportId = "-1"; // represents null, starter currentreportId
	string assetName;
	string assetRow;
	string sensorRow;
	string asset;

	vector <string> sensorIds;
	// To search through the sensorId vector
	int counter = 0;

	// Open file that contains asset file names
	ifstream assetNames("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/SensorSorter/assetNames.csv");
	if (!assetNames.is_open())
	{
		cout << "Asset names did not open, oh no! \n";
		return 0;
	}

	// For Every asset file
	while (getline(assetNames, assetName))
	{
		assetName = assetName.substr(5, assetName.length()); // remove asset from the name as files only have asset#
		assetInput.open("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/SensorSorter/" + assetName + "S.csv");	// File containing relative asset information
		sensorInput.open("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/SensorSorter/" + assetName + "_SensorIds.csv"); // File containing relative sensor ids for the assets
		getline(assetInput, assetRow); // get rid of header
		output.open("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/SensorSorter/Formatted/" + assetName + ".csv");	// open output file
		cout << assetName << "\n";

		// If either file is not open, end program.
		if (!assetInput.is_open() || !sensorInput.is_open())
		{
			cout << "Oh no! A sensor or asset file hasn't been found for asset name " + assetName << "\n";
			return 0;
		}

		// Clear sensor vector so ready for new set of sensor ids
		sensorIds.clear();

		// Getting the relative sensor Ids
		while (getline(sensorInput, sensorRow))
		{
			sensorIds.push_back(sensorRow);
		}

		sensorInput.close(); // close sensor input

		// print header to output file
		output << "def,timestamp,reportId,";
		for (int i = 0; i < sensorIds.size(); i++)
		{
			output << sensorIds[i] << ",";
		}

		// For all lines in the asset file
		while (getline(assetInput, assetRow))
		{
			// Assigning values to relative variables
			reportId = getVal(&assetRow);
			timestamp = getVal(&assetRow);
			def = getVal(&assetRow);
			sensorId = getVal(&assetRow);
			sensorVal = getVal(&assetRow);
			cout << reportId << " " << timestamp << "  " << def  << "  " << sensorId << "  " << sensorVal << endl;
			//asset = getVal(&assetRow);	// not used, skips over in file


			// Update information for new report id
			if (currentReportId != reportId && reportId != "")
			{
				counter = 0; // reset counter, new line
				// go to new line
				output << endl;
				// update report id and definition
				currentReportId = reportId;
				// output new information to line
				output << def << "," << timestamp << "," << reportId << ",";
			}

			// Search through sensor vector, find relative one and print
			while(counter < sensorIds.size())
			{	
				if (sensorIds[counter] == sensorId)
				{
					output << sensorVal << ",";
					counter++;
					break;
				}
				else
				{
					output << ",";
				}
				counter++;
			}
		}
		if (assetName == "20321")
			system("pause");

		// close files to prepare to open new ones next iteration
		assetInput.close();
		output.close();
	}

}

string getVal(string *row)
{
	auto comma = row->find(',');
	string temp = row->substr(0, comma);
	*row = row->substr(comma + 1, row->length());
	return temp;
}