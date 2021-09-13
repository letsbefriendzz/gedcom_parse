#pragma once

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
};