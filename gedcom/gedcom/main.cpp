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

class GEDtag
{
public:
	std::string layer; //?????
	std::string tag;
	std::string value;
};

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

	void parse()
	{
		if (!(recordLines.size() == 0))
		{
			this->name = recordLines[2];
			cout << this->name;
		}
	}
};

GEDtag parseLine(const char* f)
{
	GEDtag returnValue;
	char lvl = '\0';
	char tag[5] = "\0";
	int i = 0;
	lvl = f[i];
	char val[255] = "\0";
	for (i = 2; f[i] != NULL && f[i] != ' ' && f[i] != '\n'; i++)
	{   
		tag[i - 2] = f[i];
	}
	while (f[i] != '\0')
	{
		val[i] = f[i];
		i++;
	}
	cout << lvl << endl;
	cout << tag << endl;
	return returnValue;
}


//MEMORY ACCESS ERRORS EVERYWHERE!
void readGEDRecord(FILE* f, vector<Record>& records)
{
	char tempString[255] = "\0";
	int i = 0;
	int recIndex = 0;
	Record addRecord;
	while (fgets(tempString, 50, f) != NULL && recIndex < 3)
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

		parseLine(records[0].recordLines[0].c_str());

		//for (int i = 0; i < records.size(); i++)
		//{
		//	cout << "\n\nRECORD #" << i + 1 << "\n";
		//	for (int j = 0; j < records[i].recordLines.size(); j++)
		//	{
		//		cout << records[i].recordLines[j];
		//	}
		//}
	}

	return 0;
}