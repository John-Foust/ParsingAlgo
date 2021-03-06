
#include "pch.h"
#include "FileSort.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int flag;

string getValue(string *row)
{
	auto comma = row->find(',');
	string temp = row->substr(0, comma);
	*row = row->substr(comma + 1, row->length());
	return temp;
}


struct assetInfo {
	string asset;
	string def;
	int repId;
	string time;
	int sensId;
	string sensVal;
	string file;
	string index;
	bool operator() (assetInfo i, assetInfo j)
	{
		return (i.sensId < j.sensId);
	}
} assetStruct;


struct reportInfo {
	string asset;
	string def;
	int repId;
	string time;
	int sensId;
	string sensVal;
	string file;
	string index;
	bool operator() (reportInfo i, reportInfo j)
	{
		return (i.repId < j.repId);
	}
} report;


int main()
{
	vector<assetInfo> assets;
	vector<reportInfo> reports;
	string row, currentAsset;

	ifstream fileOfAssets("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/Outputs/fileOfAssets.csv");
	if (!fileOfAssets.is_open()) {
		cout << "File could not be found: fileofAssets." << endl;
		system("pause");
		return 0;
	}

	while (getline(fileOfAssets, row))
	{
		currentAsset = row;
		struct assetInfo tempStruct;
		struct reportInfo reportStruct;
		flag = 0;

		ifstream assetFile("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/Outputs/" + currentAsset + ".csv");
		if (!assetFile.is_open()) {
			cout << "File could not be found: asset file." << endl;
			system("pause");
			return 0;
		}

		ofstream output("C:/Users/Me/Desktop/Current & Past Schooling & Work/Fall 2018 (Masters)/FNN practice (Allison Practice)/ReportOrganizer/Outputs/Assets/" + currentAsset + ".csv");
		output << "Asset_Id,Sensor_Id,Report_Id,Sensor_Val,Definition,Timestamp,File_Name,Index" << endl;
		getline(assetFile, row); // skip headers

		while (getline(assetFile, row))
		{
			tempStruct.asset = getValue(&row);
			tempStruct.def = getValue(&row);
			tempStruct.repId = stoi(getValue(&row));
			tempStruct.time = getValue(&row);
			tempStruct.sensId = stoi(getValue(&row));
			tempStruct.sensVal = getValue(&row);
			tempStruct.file = getValue(&row);
			tempStruct.index = row;
			assets.push_back(tempStruct);
		}
		stable_sort(assets.begin(), assets.end(), assetStruct);

		reportStruct.asset = assets.back().asset;
		reportStruct.def = assets.back().def;
		reportStruct.repId = assets.back().repId;
		reportStruct.time = assets.back().time;
		reportStruct.sensId = assets.back().sensId;
		reportStruct.sensVal = assets.back().sensVal;
		reportStruct.file = assets.back().file;
		reportStruct.index = assets.back().index;
		reports.push_back(reportStruct);

		stable_sort(reports.begin(), reports.end(), report);

		while (assets.size() != 0)
		{
			//output << assets.back().asset << ",";
			output << assets.back().repId << ",";
			output << assets.back().time << ",";
			output << assets.back().def << ",";
			output << assets.back().sensId << ",";
			output << assets.back().sensVal << ",";
			output << assets.back().file << ",";
			output << assets.back().index << endl;
			assets.pop_back();
		}
		assetFile.close();
		output.close();
	}
	fileOfAssets.close();
}