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
#include <sstream>
using namespace std;

double const MaxValue = 10000000000;
class QuadraticInterval
{
public:
	double From;
	double To;
	double A, B, C;
	int ZID;

	QuadraticInterval(double from, double to, double a, double b, double c, int zid)
	{
		From = from;
		To = to;
		A = a;
		B = b;
		C = c;
		ZID = zid;
	}
	QuadraticInterval Copy() const
	{
		QuadraticInterval newQI(From, To, A, B, C, ZID);
		return newQI;
	}
	double IntersectPoint(QuadraticInterval& other, double& Point, double& NextPoint)
	{
		if (Point == To)
			return To;
		double p = (A - other.A) / (other.B - B);
		if (From <= p && p <= NextPoint && other.From <= p && p <= NextPoint)
		{
			double val1 = A + B * p;
			double val2 = other.A + other.B * p;
			if (std::abs(val1 - val2) > 0.001)
			{
				cout << "ERROR val1 and val2 differ to much" << endl;
			}
			return p;
		}
		if (To < NextPoint)
		{
			return To;
		}
		cout << "ERROR" << endl;

		return 0;
	}

	double Minimum()
	{
		if (C == 0)
		{
			if (B > 0)
			{
				return From;
			}
			else
			{
				return To;
			}
		}
		return (-B / (2 * C));
	}

	double MinimumHack()
	{
		if (C == 0)
		{
			if (B > 0)
			{
				return -MaxValue;
			}
			else if (B == 0)
			{
				return From;
			}
			else
			{
				return MaxValue;
			}
		}
		return (-B / (2 * C));

	}
	double MinimumAtInterval()
	{
		if (C == 0)
		{
			if (B > 0)
			{
				return From;
			}
			else
			{
				return To;
			}
		}
		double minimum = (-B / (2 * C));
		if (minimum < From)
		{
			return From;
		}
		else if (minimum > To)
		{
			return To;
		}
		else
		{
			return minimum;
		}
	}
	bool NonEmptyInterval(double from, double to)
	{
		double realFrom = std::max(From, from);
		double realTo = std::min(To, to);
		return realFrom <= realTo;
	}
	//(double, double) MinimumPointAndValue(double from, double to)
	//{
	//    if (To < from || From > to)
	//        return (double.MaxValue, double.MaxValue);


	//    double minimum = Math.Min(to, Math.Max(from, MinimumAtInterval())); ;
	//    return (minimum, GetValueInt(minimum));
	//}
	double MinimumAtIntervalRestricted(double max)
	{
		double minimum = MinimumAtInterval();
		if (max < From)
		{
			cout << "error" << endl;
			return MaxValue;
		}
		if (minimum > max)
			return max;
		else
			return minimum;
	}

	double GetValue(double p)
	{

		return A + p * B + (p * p * C);
	}

	double ValueMinimum()
	{
		double minimum = MinimumAtInterval();
		return GetValue(minimum);
	}

	double ValueMinimumRestriced(double max)
	{
		double minimum = MinimumAtIntervalRestricted(max);
		return GetValue(minimum);
	}


	double GetValueInt(double p)
	{
		if (p <= To && From <= To)
			return A + p * B + (p * p * C);
		else
			return MaxValue;
	}


	void Print() {
		cout << From << " " << To << " " << A << " " << B << " " << C << " " << endl;
	}
};


struct SUC
{
public:
	double Objective = 0;
	int TotalTime = 0;
	int pMax = 0;
	int pMin = 0;
	int RampUp = 0;
	int RampDown = 0;
	int SU = 0;
	int SD = 0;
	int MinDownTime = 0;
	int MinUpTime = 0;
	double StartCost = 0;
	double A = 0;
	double B = 0;
	double C = 0;
	vector<double> LagrangeMultipliers;
	vector<double> BM;
	vector<double> CM;

	void PrintStats()
	{
		cout << Objective << " " << pMin << " " << pMax << " " << RampUp << " " << RampDown << " " << SU << " " << SD << " " << MinUpTime << " " << MinDownTime << endl;
		//for (size_t t = 0; t < CM.size(); t++)
		//{
		//	cout << CM[t] << endl;
		//}
	
	}
	SUC()
	{
	}

	SUC(double a, double b, double c, double start, int pma, int pmi, int rampUp, int rampDown, int minUpTime, int minDownTime, int su, int sd, int totalTime)
	{

		pMax = pma;
		pMin = pmi;
		SU = su;
		SD = sd;
		RampUp = max(rampUp, 1);
		RampDown = max(rampDown, 1);
		MinDownTime = minDownTime;
		MinUpTime = minUpTime;
		StartCost = start;
		A = a;
		B = b;
		C = c;
		TotalTime = totalTime;
	}

	//	public void SetLM(List<double> LM, double[] bm, double[] cm)
	//	{
	//		LagrangeMultipliers = LM; BM = bm; CM = cm;
	//
	//	}
	static vector<double> split_string_to_vec(const string &s) {
		vector<double> result;
		stringstream ss(s);
		string item;

		while (getline(ss, item, '\t')) {
			result.push_back(stod(item));
		}

		return result;
	}
	static SUC ReadFromFile(string filename)
	{
		SUC suc;

		fstream newfile;
		vector<string> lines;
		newfile.open(filename, ios::in);
		if (newfile.is_open()) {
			string tp;
			while (getline(newfile, tp)) {
				lines.push_back(tp);
			}
		}
		int i = 0;
		suc.Objective = stod(lines[i++]);
		suc.TotalTime = stoi(lines[i++]);
		suc.pMax = stoi(lines[i++]);
		suc.pMin = stoi(lines[i++]);
		suc.RampUp = stoi(lines[i++]);
		suc.RampDown = stoi(lines[i++]);
		suc.SU = stoi(lines[i++]);
		suc.SD = stoi(lines[i++]);
		suc.MinDownTime = stoi(lines[i++]);
		suc.MinUpTime = stoi(lines[i++]);
		suc.StartCost = stod(lines[i++]);
		suc.A = stod(lines[i++]);
		suc.B = stod(lines[i++]);
		suc.C = stod(lines[i++]);
		suc.LagrangeMultipliers = split_string_to_vec(lines[i++]);
		suc.BM = split_string_to_vec(lines[i++]);
		suc.CM = split_string_to_vec(lines[i++]);
		return suc;
	}
};

struct F
{
public:
	SUC UC;
	vector<QuadraticInterval> Intervals;
	int StartIndex = 0;

	F(const F& other)
	{
		StartIndex = other.StartIndex;
		UC = other.UC;

		Intervals.push_back(other.Intervals[0].Copy());
		for (int i = 1; i < other.Intervals.size(); i++)
		{
			if (other.Intervals[i].From != other.Intervals[i].To)
			{
				Intervals.push_back(other.Intervals[i].Copy());
			}
		}
		
	}

	void Print()
	{

		for (int i = 0; i < Intervals.size(); i++)
		{
			Intervals[i].Print();
		}

	}


	void IncreasePoints(int t)
	{
		//cout << "----b4 increase----" << endl;
		//Print(); 
		for (size_t i = 0; i < Intervals.size(); i++)
		{
			Intervals[i].A += UC.A;
			Intervals[i].B += -UC.LagrangeMultipliers[t] + UC.B + UC.BM[t];
			Intervals[i].C += UC.C + UC.CM[t];
			//cout << UC.CM[t] << endl;
		}
		//cout << "Fter increase" << endl;
		//Print();
		//cout << "____________________" << endl;
	}


	F(SUC uc, int startIndex, double startCost)
	{
		UC = uc;
		StartIndex = startIndex;
		if (startIndex == 0)
		{
			Intervals.push_back(QuadraticInterval(UC.pMin, UC.pMax, 0, 0, 0, StartIndex));
		}
		else
		{
			Intervals.push_back(QuadraticInterval(UC.pMin, UC.SU, startCost, 0, 0, StartIndex));
		}
		//Print();
		IncreasePoints(startIndex);

	}


	double BestValue()
	{
		double bestValue = Intervals[0].ValueMinimum();
		for (int i = 1; i < Intervals.size(); i++)
		{
			auto& interval = Intervals[i];
			bestValue = min(bestValue, interval.ValueMinimum());
		}
		return bestValue;
	}


	int GetOptimalNode()
	{
		int INDEX = 0;
		double min = Intervals[INDEX].MinimumHack();
		while (min > Intervals[INDEX].To && INDEX < Intervals.size() - 1)
		{
			INDEX++;
			min = Intervals[INDEX].MinimumHack();
		}
		return INDEX;
	}


	void ShiftLeft(int index)
	{

			for (int i = 0; i <= index; i++)
		{

			auto& interval = Intervals[i];
			interval.From = max((double)UC.pMin, interval.From - UC.RampDown);
			interval.To = max((double)UC.pMin, interval.To - UC.RampDown);
			interval.A = interval.A + UC.RampDown * interval.B + UC.RampDown * UC.RampDown * interval.C;
			interval.B = interval.B + UC.RampDown * interval.C * 2;
		}
	}



	void ShiftRight(int index)
	{
		for (int i = index; i < Intervals.size(); i++)
		{
			auto& interval = Intervals[i];
			interval.From = min((double)UC.pMax, interval.From + UC.RampUp);
			interval.To = min((double)UC.pMax, interval.To + UC.RampUp);
			interval.A = interval.A - UC.RampUp * interval.B + UC.RampUp * UC.RampUp * interval.C;
			interval.B = interval.B - (UC.RampUp * 2 * interval.C);
		}
	}
	void Trim()
	{
		vector<QuadraticInterval> list;
		for (size_t i = 0; i < Intervals.size(); i++)
		{
			if (Intervals[i].From != Intervals[i].To)
				list.push_back(Intervals[i]);
		}
		Intervals = list;
	}



	double BestEnd()
	{
		double bestValue = Intervals[0].ValueMinimumRestriced(UC.SD);
		for (int i = 1; i < Intervals.size(); i++)
		{
			auto& interval = Intervals[i];
			if (interval.From <= UC.SD)
			{
				bestValue = min(bestValue, interval.ValueMinimumRestriced(UC.SD));
			}
		}
		return bestValue;
	}

	void NextPoints()
	{
		int Index = GetOptimalNode();
		auto& bestInterval = Intervals[Index];
		double pStar = bestInterval.MinimumAtInterval();
		double To = bestInterval.To;
		bestInterval.To = pStar;
		QuadraticInterval midInterval(max(pStar - UC.RampDown, (double)UC.pMin), min(pStar + UC.RampUp, (double)UC.pMax), bestInterval.ValueMinimum(), 0, 0, StartIndex);

		Intervals.insert(Intervals.begin() + Index + 1, midInterval);
		QuadraticInterval rightInterval = bestInterval.Copy();
		rightInterval.From = pStar;
		rightInterval.To = To;
		Intervals.insert(Intervals.begin() + Index + 2, rightInterval);
		ShiftLeft(Index);
		ShiftRight(Index + 2);
		Trim();
		
	}


};



class RRF
{
public:
	bool Reduction = true;
	vector<vector<F>> Fs;

	SUC UC;

	RRF(SUC uc, bool reduction)
	{
		UC = uc;
		Reduction = reduction;
	}

	void AddNew(int h, double startCost)
	{
		Fs[h].push_back(F(UC, h, startCost));
	}

	void Update(int t)
	{
		for (int i = 0; i < Fs[t-1].size(); i++)
		{
			F newElement = F(Fs[t-1][i]);
			//z.Print();
			//newElement.Print();
			//cout << endl;
			Fs[t].push_back(newElement);

		}
		for (int i = 0; i < Fs[t].size(); i++)
		{
		//	Fs[t][i].Print();
			Fs[t][i].NextPoints();
			//Fs[t][i].Print();
			Fs[t][i].IncreasePoints(t);
			//Fs[t][i].Print();

			//Fs[t][i].Print();
		}
	}

	double GetBestStop(int h)
	{
		double bestStop = MaxValue;
		//h-1???
		for (auto Z : Fs[h - 1])
		{
			if (h - Z.StartIndex >= UC.MinUpTime || Z.StartIndex == 0)
			{
				bestStop = min(Z.BestEnd(), bestStop);
			}
		}
		//cout << "best" << bestStop << endl;
		return bestStop;
	}


	double BestValue(int h)
	{
		double bestValue = MaxValue;
		for (auto Z : Fs[h])
		{
			bestValue = min(bestValue, Z.BestValue());
		}
		return bestValue;
	}

	void Print(int t) {
		for (size_t i = 0; i < Fs[t].size(); i++)
		{
			//cout << "F" << i << endl;
			Fs[t][i].Print();
		}
	}

	vector<vector< double>> stop;
	void FillInDP()
	{
		vector<vector<double>> newstop(UC.LagrangeMultipliers.size(), std::vector<double>(UC.MinDownTime, 0.0));
		stop = newstop;
		//for (int tau = 0; tau < UC.MinDownTime; tau++)
		//{
		//	stop[0, tau] = 0;
		//}
		for (int z = 0; z < UC.LagrangeMultipliers.size(); z++)
		{
			Fs.push_back(vector<F>());
		}
		AddNew(0, UC.StartCost);
		//Print(0);
		for (int h = 1; h < UC.TotalTime; h++)
		{

			stop[h][ UC.MinDownTime - 1] = min(stop[h - 1][ UC.MinDownTime - 2], stop[h - 1][ UC.MinDownTime - 1]);
			for (int t = 1; t < UC.MinDownTime - 1; t++)
			{
				stop[h][ t] = stop[h - 1][ t - 1];
			}
			stop[h][0] = GetBestStop(h);
		
			Update(h);
			double bestStart = min(UC.StartCost, UC.StartCost + stop[h - 1][UC.MinDownTime - 1]);
			AddNew(h, bestStart);
			//Print(h);
		}
		//for (size_t i = 0; i < stop.size(); i++)
		//{
		//	for (size_t j = 0; j < stop[i].size(); j++)
		//	{
		//		cout << stop[i][j] << " ";
		//	}
		//	cout << endl;
		//}
	}
	double GetScore()
	{


		FillInDP();
		double bestValue = 0;
		for (int tau = 0; tau < UC.MinDownTime; tau++)
		{
			bestValue = min(bestValue, stop[UC.LagrangeMultipliers.size() - 1][ tau]);
		}
		bestValue = min(bestValue, BestValue(UC.LagrangeMultipliers.size() - 1));
		return bestValue;
	}

};


int main()
{



	SUC suc = SUC::ReadFromFile("C:\\Users\\Rogier\\OneDrive - Universiteit Utrecht\\1UCTest\\GA10\\0.suc");
	suc.PrintStats();
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


	for (size_t i = 0; i < 1000; i++)
	{
		RRF rrf(suc, false);
		double score = rrf.GetScore();
		//cout << "score: " << score << endl;
	}


	//F f(suc, 0, 0);
	//f.Print();
	//f.NextPoints();s
	//f.IncreasePoints(0);
	//f.Print();
	//day01_part1();
	//day01_part2();
	//for (size_t i = 0; i < 1000; i++)
	//{
	//	day20_part2();
	//}

	//day01_part2();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

	return 0;
}

//    double minimum = Math.Min(to, Math.Max(from, MinimumAtInterval())); ;
//    return (minimum, GetValueInt(minimum));
//}

