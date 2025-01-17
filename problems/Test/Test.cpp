﻿// Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <functional>

#include <algorithm>
#include <array>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <stack>
#include <list>
#include <string>
#include <random>
#include <bitset>
#include <sstream>

#include "..\Common\Common.h"
//#include "..\Common\GraphNode.Hi"
//#include "..\Common\TreeNode.h"
//#include "..\Common\ListNode.Hi"
using namespace std;


//////////////////////////////////////////////////////////////////////////
bool wordPattern(string pattern, string str)
{
	unordered_set<string> s;
	unordered_map<char, string> m;
	vector<string> vec;
	istringstream ss(str);
	string item;
	char delim = ' ';
	while (getline(ss, item, delim))
	{
		vec.push_back(item);
	}
	if (pattern.size() != vec.size()) return false;
	for (auto i = 0; i < pattern.size(); i++)
	{
		if (m.count(pattern[i]) != 0)
		{
			if (m[pattern[i]] != vec[i]) return false;
		}
		else
		{
			if (s.count(vec[i]) != 0) return false;
			m[pattern[i]] = vec[i];
			s.insert(vec[i]);
		}
	}
	return true;
}

//template<typename... Args>
//auto FunForward(Args... args)
//{
//	return calculate(args...);
//}


int main()
{
	double time = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);

	auto f_time_begin = [&time, &nFreq, &nBeginTime, &nEndTime]()
	{
		cout << endl << "/////////////////////////////" << endl;
		QueryPerformanceCounter(&nBeginTime);
	};

	auto f_time_end = [&time, &nFreq, &nBeginTime, &nEndTime]()
	{
		QueryPerformanceCounter(&nEndTime);
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
		cout << "////////////////////////////////////////////////////////// time: " << time * 1000 << "ms" << endl;
	};

	//////////////////////////////////////////////////////////////////////////
	vector<string> TESTS;
	vector<string> K;
	vector<bool> ANSWERS;

	TESTS.push_back("abba");
	K.push_back("dog cat cat dog");
	ANSWERS.push_back(true);

	TESTS.push_back("abba");
	K.push_back("dog cat cat fish");
	ANSWERS.push_back(false);

	TESTS.push_back("aaaa");
	K.push_back("dog cat cat dog");
	ANSWERS.push_back(false);

	TESTS.push_back("abba");
	K.push_back("dog dog dog dog");
	ANSWERS.push_back(false);

	TESTS.push_back("jquery");
	K.push_back("jquery");
	ANSWERS.push_back(false);

	TESTS.push_back("aaa");
	K.push_back("aa aa aa aa");
	ANSWERS.push_back(false);

	for (int i = 0; i < TESTS.size(); i++)
	{
		f_time_begin();

		auto ans = wordPattern(TESTS[i], K[i]);
		cout << checkAnswer<decltype(ans)>(ans, ANSWERS[i]) << endl;
		//solve(TESTS[i]);
		//cout << checkAnswer<vector<vector<char>>>(TESTS[i], ANSWERS[i]) << endl;

		f_time_end();
	}
}


//////////////////////////////////////////////////////////////////////////
// TreeNode
//	vector<TreeNode *> N;
//	N.push_back(StringToTreeNode("3,9,20,null,null,15,7"));


//////////////////////////////////////////////////////////////////////////
// List Node
//	ListNode *pHead = StringToListNode("[4,7,5,3]");


