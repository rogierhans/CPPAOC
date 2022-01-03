// CPPAOC.cpp : Defines the entry point for the application.
//

#include "CPPAOC.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include "Day01.h"
#include "Day20.h"
using namespace std;

int main()
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	//day01_part1();
	//day01_part2();
	day20_part1();
	//day01_part2();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

	return 0;
}
