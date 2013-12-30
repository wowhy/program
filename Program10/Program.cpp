#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

string ToString(bool input)
{
	return input ? "true" : "false";
}

/* 斐波那契数列 */
int fab(int n)
{
	if (n <= 2)
		return 1;

	return fab(n - 2) + fab(n - 1);
}

int AdditiveSequence(int n, int t0, int t1)
{
	if (n == 0)
		return t0;

	if (n == 1)
		return t1;

	return AdditiveSequence(n - 1, t1, t0 + t1);
}

int nfab(int n)
{
	return AdditiveSequence(n, 0, 1);
}

int fab2(int n)
{
	int r = 1;
	int t = 1;
	for (int i = 2; i < n; ++i)
	{
		r = t + r;
		t = r - t;
	}

	return r;
}

/* 回文 */
bool CheckPalindrome(string::iterator ibegin, string::iterator iend)
{
	if (ibegin >= iend)
		return true;

	return *ibegin == *iend && CheckPalindrome(ibegin + 1, iend - 1);
}

bool IsPalindrome(string str)
{
	if (str.length() <= 1)
		return true;

	return CheckPalindrome(str.begin(), str.end() - 1);
}


/* 二分查找 */
int BinarySearch(string key, vector<string> arry, int low, int high)
{
	int mid, cmp;
	if (low > high) return -1;
	mid = (low + high) / 2;
	cmp = key.compare(arry[mid]);
	if (cmp == 0)
		return mid;
	if (cmp < 0)
	{
		return BinarySearch(key, arry, low, mid - 1);
	}
	else
	{
		return BinarySearch(key, arry, mid + 1, high);
	}
}

int FindStringInSortedArray(string key, vector<string> arry, int n)
{
	return BinarySearch(key, arry, 0, n - 1);
}

/* lesson 4.8 */
// 1.
int CannonBall(int n)
{
	if (n <= 1)
		return 1;

	return CannonBall(n - 1) + (2 * (n - 1) + 1);
}

// 2.
int RaiseIntToPower(int n, int k)
{
	assert(k >= 0, "k can't smaller than 0");

	if (n == 0 || n == 1)
		return n;

	if (k == 0)
		return 1;

	return RaiseIntToPower(n, k - 1) * n;
}

// 3.
int GCD(int x, int y)
{
	if (x < y) return GCD(y, x);
	if (x % y == 0)
		return y;

	return GCD(y, x % y);
}

// 6.
int DigitSum(int n)
{
	if (n < 10)
		return n;

	return DigitSum(n / 10) + n % 10;
}

// 8.
int C(int n, int k)
{
	if (n == 0)
		return 1;
	if (k == 0)
		return 1;
	if (n == k)
		return 1;

	return C(n - 1, k - 1) + C(n - 1, k);
}

// 9.
string Reverse(string str)
{
	if (str.length() == 0)
		return str;
	return string({ str.end() - 1, str.end() }) + Reverse({ str.begin(), str.end() - 1 });
}

// 10.
string IntegerToString(int n)
{
	if (n < 10)
		return string(new char[]{ '0' + (char)n, '\0' });
	return IntegerToString(n / 10) + string(new char[]{ '0' + (char)(n % 10), '\0' });
}

int main()
{
	//cout << fab(10) << endl;
	//cout << fab2(10) << endl;

	// cout << ToString(IsPalindrome("10001"));

	//vector<string> v = { "a", "b", "c", "d" };
	//cout << FindStringInSortedArray("c", v, v.size());

	// 4.8
	// 1
	//cout << CannonBall(2) << endl
	//	<< CannonBall(3) << endl
	//	<< CannonBall(4) << endl;

	// 2
	//cout << RaiseIntToPower(2, 3) << endl
	//	<< RaiseIntToPower(3, 4) << endl;

	// 3
	// cout << GCD(15, 10) << endl;

	// 6
	// cout << DigitSum(1729) << endl;

	// 8
	// cout << C(6, 2);

	// 9
	//cout << Reverse("program") << endl;

	// 10
	cout << IntegerToString(56267698) << endl;
}