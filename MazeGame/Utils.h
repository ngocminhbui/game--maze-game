#pragma once
#include <string>
using namespace std;
#include <math.h>


class Utils{
	public:
		static string intToString(int value){
			string result;
			int len = log10(value) + 1;
			result.resize(len);
			while (value != 0){
				result[--len] = char(value % 10+48);
				value = value / 10;
			}
			cout << result;
			return result;
		}
		static void increaseOrder(int &a, int &b){
			if (a > b){
				int temp = a;
				a = b;
				b = temp;
			}
		}
};
