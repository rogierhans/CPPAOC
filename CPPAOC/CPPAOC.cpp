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


class QuadraticInterval
{
private:
	double const MaxValue = 10000000000;


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
	QuadraticInterval Copy()
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

	//public Tuple<double, double> Intersects(QuadraticInterval otherInterval)
	//{
	//    double a = otherInterval.A - A;
	//    double b = otherInterval.B - B;
	//    double c = otherInterval.C - C;
	//    if (c == 0)
	//    {
	//        if (b == 0)
	//        {
	//            return new Tuple<double, double>(double.MinValue, double.MinValue);
	//        }
	//        else
	//        {
	//            var test = -a / b;
	//            return new Tuple<double, double>(test, test);
	//        }

	//    }
	//    else
	//    {
	//        double discriminant = (b * b - a * c * 4);
	//        if (discriminant < 0)
	//        {
	//            return new Tuple<double, double>(double.MinValue, double.MinValue);
	//        }
	//        else
	//        {
	//            double left = -b / (2 * c);
	//            double right = (Math.Sqrt(discriminant) / (2 * c));
	//            return new Tuple<double, double>(left - right, left + right);
	//        }
	//    }
	//}

	//public double FirstIntersect(QuadraticInterval otherInterval)
	//{
	//    double a = otherInterval.A - A;
	//    double b = otherInterval.B - B;
	//    double c = otherInterval.C - C;
	//    // Console.WriteLine("{0} {1} {2}", a, b, c);
	//    if (c == 0 && b != 0)
	//    {
	//        return -a / b;
	//    }
	//    else if (c == 0)
	//    {
	//        return double.MinValue;
	//    }
	//    double discriminant = (b * b - a * c * 4);
	//    if (discriminant < 0)
	//    {
	//        return double.MinValue;
	//    }
	//    double solution = ((-b - (Math.Sqrt(discriminant))) / (2 * c));
	//    return solution;
	//}

	//public double SecondIntersect(QuadraticInterval otherInterval)
	//{
	//    double a = otherInterval.A - A;
	//    double b = otherInterval.B - B;
	//    double c = otherInterval.C - C;
	//    //Console.WriteLine("{0} {1} {2}", a, b, c);
	//    //Console.ReadLine();
	//    if (c == 0 && b != 0)
	//    {
	//        return -a / b;
	//    }
	//    else if (c == 0)
	//    {
	//        return double.MinValue;
	//    }
	//    double discriminant = (b * b - a * c * 4);
	//    if (discriminant < 0)
	//    {
	//        return double.MinValue;
	//    }
	//    double solution = ((-b + (Math.Sqrt(discriminant))) / (2 * c));
	//    return solution;
	//}

	//public  Tuple<bool, double> IntersectInIntervalCombined(double iFrom, double iTo, QuadraticInterval interval, double p)
	//{
	//    var interstion = Intersects(interval);
	//    double firstIntersect = interstion.Item1;

	//    if (iFrom <= firstIntersect && firstIntersect <= iTo && p < firstIntersect)
	//    {
	//        return new Tuple<bool, double>(true, firstIntersect);
	//    }
	//    double secondIntersect = interstion.Item2;
	//    if (iFrom <= secondIntersect && secondIntersect <= iTo && p < secondIntersect)
	//    {
	//        return new Tuple<bool, double>(true, secondIntersect);
	//    }
	//    return new Tuple<bool, double>(false, 0);
	//}
	//public bool IntersectInIntervalBool(double iFrom, double iTo, QuadraticInterval interval, double p)
	//{
	//    var interstion = Intersects(interval);
	//    double firstIntersect = interstion.Item1;

	//    if (iFrom <= firstIntersect && firstIntersect <= iTo && p < firstIntersect)
	//    {
	//        return true;
	//    }
	//    double secondIntersect = interstion.Item2;
	//    if (iFrom <= secondIntersect && secondIntersect <= iTo && p < secondIntersect)
	//    {
	//        return true;
	//    }
	//    return false;
	//}
	//public double IntersectInIntervalDouble(double iFrom, double iTo, QuadraticInterval interval, double p)
	//{
	//    var interstion = Intersects(interval);
	//    double firstIntersect = interstion.Item1;
	//    double secondIntersect = interstion.Item2;
	//    if (iFrom <= firstIntersect && firstIntersect <= iTo && p < firstIntersect) return firstIntersect;
	//    if (iFrom <= secondIntersect && secondIntersect <= iTo && p < secondIntersect) return secondIntersect;
	//    throw new Exception("????????");
	//}
};


class SUC
{
public:
	double Objective;
	int TotalTime;
	int pMax;
	int pMin;
	int RampUp;
	int RampDown;
	int SU;
	int SD;
	int MinDownTime;
	int MinUpTime;
	double StartCost;
	double A;
	double B;
	double C;
	vector<double> LagrangeMultipliers;
	vector<double> BM;
	vector<double> CM;

	void PrintStats()
	{
		cout << pMin << " " << pMax << " " << RampUp << " " << RampDown << " " << SU << " " << SD << " " << MinUpTime << " " << MinDownTime << endl;
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
	//
	//	public void SetRandomLM()
	//	{
	//		LagrangeMultipliers = new List<double>();
	//		Random rng = new Random();
	//		for (int i = 0; i < TotalTime; i++)
	//		{
	//			LagrangeMultipliers.Add(B * (rng.NextDouble() * 3));
	//
	//		}
	//	}
	//
	//
	//
	//	public void WriteToFile(string filename)
	//	{
	//		var objects = new List<object>() {
	//			Objective,
	//				TotalTime,
	//				pMax,
	//				pMin,
	//				RampUp,
	//				RampDown,
	//				SU,
	//				SD,
	//				MinDownTime,
	//				MinUpTime,
	//				StartCost,
	//				A,
	//				B,
	//				C,
	//				string.Join("\t", LagrangeMultipliers),
	//				string.Join("\t", BM),
	//				string.Join("\t", CM)
	//		};
	//		File.WriteAllLines(filename, objects.Select(x = > x.ToString()).ToList());
	//	}
	static SUC ReadFromFile(string filename)
	{
		auto suc = new SUC();
		auto lines = File.ReadAllLines(filename);
		int i = 0;
		suc.Objective = double.Parse(lines[i++]);
		suc.TotalTime = int.Parse(lines[i++]);
		suc.pMax = int.Parse(lines[i++]);
		suc.pMin = int.Parse(lines[i++]);
		suc.RampUp = int.Parse(lines[i++]);
		suc.RampDown = int.Parse(lines[i++]);
		suc.SU = int.Parse(lines[i++]);
		suc.SD = int.Parse(lines[i++]);
		suc.MinDownTime = int.Parse(lines[i++]);
		suc.MinUpTime = int.Parse(lines[i++]);
		suc.StartCost = double.Parse(lines[i++]);
		suc.A = double.Parse(lines[i++]);
		suc.B = double.Parse(lines[i++]);
		suc.C = double.Parse(lines[i++]);
		suc.LagrangeMultipliers = lines[i++].Split('\t').Select(x = > double.Parse(x)).ToList();
		suc.BM = lines[i++].Split('\t').Select(x = > double.Parse(x)).ToArray();
		suc.CM = lines[i++].Split('\t').Select(x = > double.Parse(x)).ToArray();
		return suc;
	}
};

class F
{
public:
	//SUC UC;
	vector<QuadraticInterval> Intervals;
	int StartIndex = 0;

	F(F& other)
	{
		StartIndex = other.StartIndex;
		//UC = other.UC;

		Intervals.push_back(other.Intervals[0].Copy());
		for (int i = 1; i < other.Intervals.size(); i++)
		{
			if (other.Intervals[i].From != other.Intervals[i].To)
			{
				Intervals.push_back(other.Intervals[i].Copy());
			}
		}
	}

	//private void Print()
	//{
	//	// if (StartIndex == 0)
	//	{
	//		for (int i = 0; i < Intervals.Count; i++)
	//		{
	//			Console.WriteLine("{0} {1}", i, Intervals[i]);
	//		}
	//	}
	//}

	//public F(SUC uc, int startIndex, double startCost)
	//{
	//	UC = uc;
	//	StartIndex = startIndex;
	//	if (startIndex == 0)
	//	{
	//		Intervals.Add(new QuadraticInterval(UC.pMin, UC.pMax, 0, 0, 0, StartIndex));
	//	}
	//	else
	//	{
	//		Intervals.Add(new QuadraticInterval(UC.pMin, UC.SU, startCost, 0, 0, StartIndex));
	//	}
	//	IncreasePoints(startIndex);
	//}


	//internal double BestValue()
	//{
	//	double bestValue = Intervals[0].ValueMinimum();
	//	for (int i = 1; i < Intervals.Count; i++)
	//	{
	//		var interval = Intervals[i];
	//		bestValue = Math.Min(bestValue, interval.ValueMinimum());
	//	}
	//	return bestValue;
	//}

	//public void NextPoints(int h)
	//{
	//	int Index = GetOptimalNode();
	//	var bestInterval = Intervals[Index];
	//	double pStar = bestInterval.MinimumAtInterval();
	//	double To = bestInterval.To;
	//	bestInterval.To = pStar;
	//	var midInterval = new QuadraticInterval(Math.Max(pStar - UC.RampDown, UC.pMin), Math.Min(pStar + UC.RampUp, UC.pMax), bestInterval.ValueMinimum(), 0, 0, StartIndex);
	//	Intervals.Insert(Index + 1, midInterval);
	//	var rightInterval = bestInterval.Copy();
	//	rightInterval.From = pStar;
	//	rightInterval.To = To;
	//	Intervals.Insert(Index + 2, rightInterval);
	//	ShiftLeft(Index);
	//	ShiftRight(Index + 2);
	//	Trim();
	//}


	//private int GetOptimalNode()

	//{
	//	int INDEX = 0;
	//	var min = Intervals[INDEX].MinimumHack();
	//	while (min > Intervals[INDEX].To && INDEX < Intervals.Count - 1)
	//	{
	//		INDEX++;
	//		min = Intervals[INDEX].MinimumHack();
	//	}
	//	return INDEX;

	//}


	//public void ShiftLeft(int index)
	//{
	//	for (int i = 0; i <= index; i++)
	//	{

	//		var interval = Intervals[i];
	//		interval.From = Math.Max(UC.pMin, interval.From - UC.RampDown);
	//		interval.To = Math.Max(UC.pMin, interval.To - UC.RampDown);
	//		interval.A = interval.A + UC.RampDown * interval.B + UC.RampDown * UC.RampDown * interval.C;
	//		interval.B = interval.B + UC.RampDown * interval.C * 2;
	//	}
	//}



	//public void ShiftRight(int index)
	//{
	//	for (int i = index; i < Intervals.Count; i++)
	//	{
	//		var interval = Intervals[i];
	//		interval.From = Math.Min(UC.pMax, interval.From + UC.RampUp);
	//		interval.To = Math.Min(UC.pMax, interval.To + UC.RampUp);
	//		interval.A = interval.A - UC.RampUp * interval.B + UC.RampUp * UC.RampUp * interval.C;
	//		interval.B = interval.B - (UC.RampUp * 2 * interval.C);
	//	}
	//}
	//public void Trim()
	//{
	//	var first = Intervals.First();
	//	while (first.From == first.To)
	//	{
	//		Intervals.RemoveAt(0);
	//		first = Intervals.First();
	//	}
	//	var last = Intervals.Last();
	//	while (last.From == last.To)
	//	{
	//		Intervals.RemoveAt(Intervals.Count - 1);
	//		last = Intervals.Last();
	//	}
	//}

	//public void IncreasePoints(int t)
	//{
	//	foreach(var interval in Intervals)
	//	{
	//		interval.A += UC.A;
	//		interval.B += -UC.LagrangeMultipliers[t] + UC.B + UC.BM[t];
	//		interval.C += UC.C + UC.CM[t];
	//	}
	//}

	//internal double BestEnd()
	//{
	//	double bestValue = Intervals[0].ValueMinimumRestriced(UC.SD);
	//	for (int i = 1; i < Intervals.Count; i++)
	//	{
	//		var interval = Intervals[i];
	//		if (interval.From <= UC.SD)
	//		{
	//			bestValue = Math.Min(bestValue, interval.ValueMinimumRestriced(UC.SD));
	//		}
	//	}
	//	return bestValue;
	//}
};

int main()
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


	QuadraticInterval QI(0, 100, 10, 1, 0.1, 0);
	QuadraticInterval Q2(0, 100, 0, 2, 0.1, 0);
	double min = 0;
	double max = 100;
	double intersect = QI.IntersectPoint(Q2, min, max);
	cout << intersect << endl;

	//day01_part1();
	//day01_part2();
	//for (size_t i = 0; i < 1000; i++)
	//{
	//	day20_part2();
	//}

	//day01_part2();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << "[µs]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() / 1000 << "[ns]" << std::endl;

	return 0;
}
