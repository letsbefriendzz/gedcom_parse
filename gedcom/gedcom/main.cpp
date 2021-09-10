/*

//===========//
//GEDCOM TAGS//
//===========//

*/

//this is a test of github
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

class GEDline
{
public:
	std::string layer; //?????
	std::string tag;
	std::string value;
};

//one file is getting to be a bit much for this project!
GEDline parseLine(const char* f)
{
	GEDline returnValue;
	char lvl = '\0';
	char tag[5] = "\0";
	int i = 0;
	int vali = 0;
	lvl = f[i];
	char val[255] = "\0";
	for (i = 2; f[i] != NULL && f[i] != ' ' && f[i] != '\n'; i++)
	{
		tag[i - 2] = f[i];
	}

	i++;
	while (f[i] != '\0')
	{
		val[vali] = f[i];
		i++;
		vali++;
	}
	val[i] = '\0';
	returnValue.layer = lvl;
	returnValue.tag = tag;
	returnValue.value = val;
	return returnValue;
}

class Record
{
private:
	int id;
	std::string name;
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

	void populate()
	{
		/*
		parseLine(recordLines[i].c_str())
		*/
		for (int i = 0; i < recordLines.size(); i++)
		{
			if (parseLine(recordLines[i].c_str()).tag == "NAME")
			{
				this->name = parseLine(recordLines[i].c_str()).value;
			}
			else if (parseLine(recordLines[i].c_str()).tag == "BIRT")
			{
				//This is where things get complicated!
				//GEDCOM uses generic tags for certain subtypes; in this case, the two subtypes of the BIRT
				//I need are the date and the location. These themselves are spearate tags, however I don't
				//think that there can be cloned parent tags...
				this->birth_date = parseLine(recordLines[i].c_str()).value;
			}
		}
	}

	std::string getName()
	{
		return this->name;
	}
};

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