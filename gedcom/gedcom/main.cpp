/*

//===========//
//GEDCOM TAGS//
//===========//

*/

//this is a test of github
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include "Record.h"

using namespace std;

//MEMORY ACCESS ERRORS EVERYWHERE!
void readGEDRecord(FILE* f, vector<Record>& records)
{
	char tempString[255] = "\0";
	int i = 0;
	int recIndex = 0;
	Record addRecord;
	while (fgets(tempString, 50, f) != NULL && recIndex < 9)
	{
		if (tempString[0] == '0' && !(i == 0))
		{
			records.push_back(addRecord);
			addRecord.setEmpty();
			addRecord.recordLines.push_back(tempString);
			recIndex++;
		}
		else
		{
			addRecord.recordLines.push_back(tempString);
		}
		i++;
	}

	cout << "TOTAL LINES: " << i << "\nTOTAL RECORDS: " << recIndex << "\n";
}

void displayRecords(std::vector<Record> records)
{
	for (int i = 0; i < records.size(); i++)
	{
		cout << "\n\nRECORD #" << i + 1 << "\n";
		for (int j = 0; j < records[i].recordLines.size(); j++)
		{
			if (records[i].recordLines[j][0] == '1')
				cout << "|---";
			else if (records[i].recordLines[j][0] == '2')
				cout << "|-------";
			else if (records[i].recordLines[j][0] == '3')
				cout << "|-----------";
			else if (records[i].recordLines[j][0] == '4')
				cout << "|---------------";

			cout << records[i].recordLines[j];
		}
	}
}

int main(void)
{
	FILE* ged = fopen("C:\\ged_files\\gm2107.GED", "r");
	vector<Record> records;

	if (ged == nullptr)
	{
		cout << "ged is NULL";
	}
	else
	{
		cout << "gm2107.GED opened successfully!\n";
		readGEDRecord(ged, records);

		cout << "Size: " << records.size() << "\n";

		//records[2].populate();
		//cout << "getName():\t" << records[2].getName();

		displayRecords(records);
	}

	return 0;
}