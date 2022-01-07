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
