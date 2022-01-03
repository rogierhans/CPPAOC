// CPPAOC.cpp : Defines the entry point for the application.
//

#include "CPPAOC.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>

using namespace std;

int day20_part1()
{
	fstream newfile;
	vector<string> list;
	newfile.open("C:\\Users\\Rogier\\Dropbox\\AOC2\\AOC2\\InputFiles\\2021_20\\input.txt", ios::in);
	if (newfile.is_open()) {
		string tp;
		while (getline(newfile, tp)) {
		 list.push_back(tp);
		}
	}
	int counterPart1 = 0;
	int array[250][250]{};
	for (size_t i = 1; i < list.size(); i++)
	{
		for (size_t j = 0; j < list[i].length(); j++)
		{
			array[i][j] = list[i][j] == '#' ? 1 : 0;
		}
	}


	for (size_t i = 1; i < 250; i++)
	{
		for (size_t j = 0; j < 250; j++)
		{
			cout << array[i][j] ;
		}
		cout << "\n";
	}


	return 0;
}

int day20_part2()
{
	return 0;
}