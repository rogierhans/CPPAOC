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

int day01_part1()
{
	fstream newfile;
	vector<int> list;
	newfile.open("C:\\Users\\Rogier\\Dropbox\\AOC2\\AOC2\\InputFiles\\2021_01\\input.txt", ios::in);
	if (newfile.is_open()) {
		string tp;
		while (getline(newfile, tp)) {
		 list.push_back( stoi(tp));
		}
	}
	int counterPart1 = 0;
	for (size_t i = 1; i < list.size(); i++)
	{
		if (list[i] > list[i - 1]) counterPart1++;
	}

	cout << counterPart1 << "\n";
	
	return 0;
}
int day01_part2()
{


	fstream newfile;
	vector<int> list;
	newfile.open("C:\\Users\\Rogier\\Dropbox\\AOC2\\AOC2\\InputFiles\\2021_01\\input.txt", ios::in);
	if (newfile.is_open()) {
		string tp;
		while (getline(newfile, tp)) {
			list.push_back(stoi(tp));
		}
	}
	int counterPart2 = 0;
	for (size_t i = 3; i < 2000; i++)
	{
		if (list[i] > list[i - 3]) counterPart2++;
	}
	cout << counterPart2 << "\n";

	return 0;
}