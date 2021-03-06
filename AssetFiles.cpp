
#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string getValue(string *row);

int main()
{
	string row;
	string reportId, def, asset, timestamp, sensorId, sensorVal, fileName, index;
	string currentAsset;

	ifstream parsedData("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/parsedData.csv");
	if (!parsedData.is_open()) {
		cout << "File could not be found." << endl;
		return 0;
	}
	ofstream fileOfFiles("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/Outputs/fileOfAssets.csv");

	getline(parsedData, row);

	reportId = getValue(&row);
	def = getValue(&row);
	asset = getValue(&row);
	currentAsset = asset;
	timestamp = getValue(&row);
	sensorId = getValue(&row);
	sensorVal = getValue(&row);
	fileName = getValue(&row);
	index = row;

	fileOfFiles << "asset" << asset << endl;
	ofstream assetFile("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/Outputs/asset" + currentAsset + ".csv");
	assetFile << "Asset_Id,Definition,Report_Id,Timestamp,Sensor_Id,Sensor_Val,File_Name,Index" << endl;
	assetFile << asset << "," << def << "," << reportId << "," << timestamp << "," << sensorId << "," << sensorVal << "," << fileName << "," << index << endl;

	while (getline(parsedData, row)) {
		reportId = getValue(&row);
		def = getValue(&row);
		asset = getValue(&row);
		timestamp = getValue(&row);
		sensorId = getValue(&row);
		sensorVal = getValue(&row);
		fileName = getValue(&row);
		index = row;
		
		if (asset != currentAsset)
		{
			assetFile.close();
			assetFile.open("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/Outputs/asset" + asset + ".csv");
			currentAsset = asset;
			assetFile << asset << "," << def << "," << reportId << "," << timestamp << "," << sensorId << "," << sensorVal << "," << fileName << "," << index << endl;
			fileOfFiles << "asset" << asset << endl;
		}
		else
		{
			assetFile << asset << "," << def << "," << reportId << "," << timestamp << "," << sensorId << "," << sensorVal << "," << fileName << "," << index << endl;
		}
	}
	fileOfFiles.close();
	assetFile.close();
	parsedData.close();
}

string getValue(string *row) 
{
	auto comma = row->find(',');
	string temp = row->substr(0, comma);
	*row = row->substr(comma + 1, row->length());
	return temp;
}