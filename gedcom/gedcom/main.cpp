/*

//===========//
//GEDCOM TAGS//
//===========//

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

class Record
{
private:
	int id;
	std::string fname;
	std::string lname;
	bool sex; //true = man, false - woman

	//Date birth;
	//Date death;

	std::string birth_date;
	std::string death_date;

	std::string birth_location;
	std::string death_location;

	std::string notes;

	std::string FAMS;
	std::string FAMC;

	
public:
	vector<std::string> recordLines;

	Record()
	{
		//init to empty
		setEmpty();
	}

	~Record()
	{
		//
	}

	void setEmpty()
	{
		recordLines.clear();
	}
};


//MEMORY ACCESS ERRORS EVERYWHERE!
void readGEDRecord(FILE* f, vector<Record>& records)
{
	char tempString[255] = "\0";
	int i = 0;
	int recIndex = 0;
	Record addRecord;
	while (fgets(tempString, 50, f) != NULL && recIndex < 100)
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

int main(void)
{
	FILE* ged = fopen("gm2107.GED", "r");
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

		for (int i = 0; i < records.size(); i++)
		{
			cout << "\n\nRECORD #" << i << "\n";
			for (int j = 0; j < records[i].recordLines.size(); j++)
			{
				cout << records[i].recordLines[j];
			}
		}
	}
}