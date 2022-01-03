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

void print(const std::vector<std::vector<int>>& v) {
	for (size_t i = 1; i < v.size(); i++)
	{
		for (size_t j = 0; j < v[i].size(); j++)
		{
			cout << v[i][j];
		}
		cout << "\n";
	}
}

int day20_part1()
{
	fstream newfile;
	vector<string> list;
	newfile.open("C:\\Users\\Rogier\\Dropbox\\AOC2\\AOC2\\InputFiles\\2021_20\\input.txt", ios::in);
	int map[512];
	if (newfile.is_open()) {
		string first;
		getline(newfile, first);
		for (size_t i = 0; i < first.length(); i++)
		{
			map[i] = (first[i] == '#' ? 1 : 0);	
		}
		string tp;
		while (getline(newfile, tp)) {
			list.push_back(tp);
		}
	}
	int counterPart1 = 0;
	const int height = 250;
	int array[height][height]{};
	for (size_t i = 1; i < list.size(); i++)
	{
		for (size_t j = 0; j < list[i].length(); j++)
		{
			array[i + 75][j + 75] = (list[i][j] == '#' ? 1 : 0);
		}
	}
	/*
	for (size_t i = 0; i < 75; i++)
	{
		for (size_t j = 0; j < 75; j++)
		{
			cout << array[i + 75][j + 75];
		}
		cout << "\n";
	}*/
	int count = 0;
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			if (array[i][j] == 1) count++;
		}
	}
	cout << count << endl;

	return 0;
}

int day20_part2()
{
	return 0;
}