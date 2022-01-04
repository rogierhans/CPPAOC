// CPPAOC.cpp : Defines the entry point for the application.
//

#include "CPPAOC.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include "Day20.h"

using namespace std;
const int sizeArray = 250;

void print(int(&array)[sizeArray][sizeArray]) {
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			cout << array[i][j];
		}
		cout << "\n";
	}
}

int day20_part1()
{

	return 0;
}


void ParseLines(int(&map)[512], std::vector<std::string>& list)
{
	fstream newfile;
	newfile.open("C:\\Users\\Rogier\\Dropbox\\AOC2\\AOC2\\InputFiles\\2021_20\\input.txt", ios::in);

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
}

int day20_part2()
{
	vector<string> list;
	int map[512]{};

	ParseLines(map, list);


	int array[sizeArray][sizeArray]{};
	for (size_t i = 1; i < list.size(); i++)
	{
		for (size_t j = 0; j < list[i].length(); j++)
		{
			array[i + 75][j + 75] = (list[i][j] == '#' ? 1 : 0);
		}
	}

	int array2[sizeArray][sizeArray]{};

	for (size_t i = 0; i < sizeArray; i++)
	{
		for (size_t j = 0; j < sizeArray; j++)
		{
			array2[i][j] = 1;
		}
	}

	const int heightMinusOne = sizeArray - 1;
	for (size_t k = 0; k < 25; k++)
	{
		for (size_t i = 1; i < heightMinusOne; i++)
		{
			for (size_t j = 1; j < heightMinusOne; j++)
			{
				int number = 0;
				number += array[i - 1][j - 1] << 8;
				number += array[i - 1][j] << 7;
				number += array[i - 1][j + 1] << 6;

				number += array[i][j - 1] << 5;
				number += array[i][j] << 4;
				number += array[i][j + 1] << 3;

				number += array[i + 1][j - 1] << 2;
				number += array[i + 1][j] << 1;
				number += array[i + 1][j + 1];
				array2[i][j] = map[number];
			}
		}
		for (size_t i = 1; i < heightMinusOne; i++)
		{
			for (size_t j = 1; j < heightMinusOne; j++)
			{
				int number = 0;
				number += array2[i - 1][j - 1] << 8;
				number += array2[i - 1][j] << 7;
				number += array2[i - 1][j + 1] << 6;

				number += array2[i][j - 1] << 5;
				number += array2[i][j] << 4;
				number += array2[i][j + 1] << 3;

				number += array2[i + 1][j - 1] << 2;
				number += array2[i + 1][j] << 1;
				number += array2[i + 1][j + 1];
				array[i][j] = map[number];
			}

		}
	}
	int count = 0;
	for (size_t i = 0; i < sizeArray; i++)
	{
		for (size_t j = 0; j < sizeArray; j++)
		{
			if (array[i][j] == 1) count++;
		}
	}
	//cout << count << endl;
	return count;
}