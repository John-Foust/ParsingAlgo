// ReportOrganizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// ReportOrganizer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct report
{
	string reportId;
	string timeStamp;
	vector<struct sensor> sensors;
} report;

struct sensor 
{
	long sensorId;
	string sensorVal;
} sensor;
 ifstream transReports("C:/Users/fibro/Downloads/ids/sortedTransmissionReports.csv"); // location of the file that holds report ids
 ifstream logFile("F:/SortedLogs");	// location of the log file
 ofstream parsedData("F:/parsedData.csv");	// output file
 ofstream notFound("F:/NotFoundData.csv");	// output file

void PrintInfo(string rowL, string rowR, string rReportid, int flag);
string grabFirstDataVal(string *row, int flag);

int main()
{
	string rowL;
	string rowR;
	string LreportId;
	string RreportId;
	vector<struct report> reports;
	int iterFlag = 0; // symbolises if it is the first iteration
	int found = 0; // if the report has been found
	// Checks to see if all the files have opened.
	if (!transReports.is_open() || !logFile.is_open() || !parsedData.is_open() || !notFound.is_open()) {
		cout << "File could not be found." << endl;	
		return 0;
	}

	// get rid of header
	LreportId = grabFirstDataVal(&rowL, 1);

	// Set default values before entering loop
	LreportId = grabFirstDataVal(&rowL, 1);
	RreportId = grabFirstDataVal(&rowR, 0);

	while (!logFile.eof() && !transReports.eof())
	{
		// If Logreport id > transreport id, not found since in sorted order in both files
		if (stoi(LreportId) > stoi(RreportId))
		{
			PrintInfo(rowL, rowR, RreportId, 0); // Print to not found
			grabFirstDataVal(&rowR, 0);	// grab new report id from transReports
			iterFlag = 1;
		}
		else if (iterFlag == 1) // if its the first iteration for the reportId
		{
			iterFlag = 0;
			//continue; // Avoid skipping over the current reportId and line by continuing
		}
		else
		{
			LreportId = grabFirstDataVal(&rowL, 1);	// Current line did not find the id, so grab new id
		}
		
		// Loop as long as LreportId is equal to RreportId
		while (LreportId == RreportId)
		{
			PrintInfo(rowL, rowR, RreportId, 1);	// Prints to output file
			LreportId = grabFirstDataVal(&rowL, 1);
			found = 1;
		}

		// if the report id has been found, grab new id from transReports
		if (found == 1)
		{
			RreportId = grabFirstDataVal(&rowR, 0);
			iterFlag = 1;
			found = 0;
		}
	}
	transReports.close();
	logFile.close();
	parsedData.close();
}


// Gets file line and grabs report id from a file line : 0 = transReports, 1 = logFile
string grabFirstDataVal(string *row, int flag)
{
	if(flag == 0)
		getline(transReports, *row);
	else if(flag == 1)
		getline(logFile, *row);
	
	auto spot = row->find(',');
	string temp = row->substr(0, spot);
	*row = row->substr(spot+1, row->length());
	if (flag == 2)
	{
		
	}
	return temp;
}

// Combines input from log file and report file and outputs to a file : 0 = not found, 1 = found
void PrintInfo(string rowL, string rowR, string rReportid, int flag)
{
	//system("pause");
	string def = grabFirstDataVal(&rowR, 2);
	string asset = grabFirstDataVal(&rowR, 2);
	string timeStamp = grabFirstDataVal(&rowR, 2);
	// report id was not found
	if (flag == 0)
	{
		notFound << rReportid << "," << def << "," << asset << "," << timeStamp << endl;
	}
	// report id was found
	else if (flag == 1)
	{
		parsedData << rReportid << "," <<  def << "," << asset << "," << timeStamp << ",";
		// we found a match,
		parsedData << grabFirstDataVal(&rowL, 2)  << ",";	// sensor id
		parsedData << grabFirstDataVal(&rowL, 2) << ",";	// sensor value
		parsedData << grabFirstDataVal(&rowL, 2) << ",";	// file name
		parsedData << grabFirstDataVal(&rowL, 2);	// row number
		parsedData << endl;
	}

}