#include "sortingcompetition.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

SortingCompetition::SortingCompetition()
{
	fname = "";
}

//Pretty simple constructor, does exactly what you'd expect.
SortingCompetition::SortingCompetition(const string& inputFileName)
{
	fname = inputFileName;
}

//Changes the filename
void SortingCompetition::setFileName(const string& inputFileName)
{
	fname = inputFileName;
}

//Reads data in.
bool SortingCompetition::readData()
{
	//Also im trying to decide if c_strings are a better option or strings, we'll have to see if strcmp is significantly faster than comparing strings
	//There might be some other way to compare strings I kind of forgot.
	if (fname == "")
	{
		std::cout << "Please use a file name.\n";
		return false;
	}

	std::ifstream in(fname.c_str(), ios::in);

	in >> numWords;
	string temp;
	for (int i = 0; i < numWords; i++)
	{
		in >> temp;
		words.push_back(temp);
	}
	in.close();

	return true;
}

bool SortingCompetition::prepareData()
{
	buckets.resize(81); 
	for (int x = 0; x < words.size(); x++)
	{
		int size = words[x].size(); 
		if (buckets[size].size() == 0)
		{
			bool exists = false; 
			for (int x = 0; x < usedBuckets.size(); x++)
				if (size == strtol(words[x].c_str(), NULL, 10))
					exists = true; 
			if (!exists)
				usedBuckets.push_back(size); 
		}
		buckets[size].push_back(words[x]);
	}
	return true; 
}

void SortingCompetition::sortData()
{
	for (int x = 0; x < usedBuckets.size(); x++)
		selectionSort(x); 
}

void SortingCompetition::outputData(const string& outputFileName)
{
	ofstream out(outputFileName.c_str());
	for (int i = 1; i < buckets.size(); i++)
	{
		for (int k = 0; k < buckets[i].size(); k++)
		{
			out << buckets[i][k] + '\n'; 
		}
	}
}

void SortingCompetition::selectionSort(int x)
{
	int tracker;
	string temp;

	for (int i = 0; i < buckets[x].size(); i++)
	{
		tracker = i; //make the current index of the unsorted part = to tracker
		for (int j = i + 1; j <buckets[x].size(); j++)
		{
			if (buckets[x][j] < buckets[x][tracker])
				tracker = j;	//tracker will keep track of the index that the bigger value is in
		}
		//if swap is needed 
		if (tracker != i)
		{
			temp = buckets[x][i];
			buckets[x][i] = buckets[x][tracker];
			buckets[x][tracker] = temp;
		}
	}

}
void SortingCompetition::bubbleSort(int x)
{
	string temp;
	for(int i = 0; i < buckets[x].size(); i++)
	{
		for(int j = 0;  j < buckets[x].size()-1; j++)
		{
			if(buckets[x][j] < buckets[x][j+1])
			{
				temp = buckets[x][j+1];
				buckets[x][j+1] = buckets[x][j];
				buckets[x][j] = temp;	
			}
		}
	}
}

void SortingCompetition::quickSort(int x)
{
	if(!(buckets[x].size() >= 3))
	{
		bubbleSort(x);
		return;
	}	
	int medianIndex = findMedian(buckets[x][0],buckets[x][buckets[x].size()/2],buckets[x][buckets[x].size()-1]);
       	if(medianIndex == 1)
	{
		medianIndex = buckets[x].size()/2;
	}
	else if(medianIndex == 2)
	{
		medianIndex = buckets[x].size()-1;
	}
	//put values into correct partitions
	//repeat logn times
}

inline int SortingCompetition::findMedian(const string& first,const string& second,const string& third) const
{
	if((first < second && first > third) || (first > second && first < third))
	{
		return 0;
	}
	else if ((second < first && second > third) || (second < third && second > first))
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

void SortingCompetition::introSort(int x)
{
}
