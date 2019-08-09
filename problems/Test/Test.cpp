﻿// Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include <algorithm>
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

#include "..\Common\Common.h"
//#include "..\Common\GraphNode.h"
#include "..\Common\TreeNode.h"
//#include "..\Common\ListNode.h"
using namespace std;


//////////////////////////////////////////////////////////////////////////
// Encodes a tree to a single string.
//string serialize(TreeNode* root) {
//	if (!root) return "[]";
//	string res;
//	vector<string> con;
//	queue<TreeNode*> q;
//	q.push(root);
//	// 层次遍历树
//	while (!q.empty()) {
//		TreeNode* node = q.front();
//		if (!node) {
//			con.push_back("null");
//			q.pop();
//			continue;
//		}
//		else {
//			con.push_back(to_string(node->val));
//		}
//		q.pop();
//		q.push(node->left);
//		q.push(node->right);
//	}
//	// 去除vector后面的多余null
//	int n = con.size();
//	while (con[--n] == "null");
//	// 拼接结果字符串
//	res += "[";
//	for (int i = 0; i <= n; ++i) {
//		if (i == n)
//			res += con[i] + "]";
//		else
//			res += con[i] + ",";
//	}
//	return res;
//}
//
//// Decodes your encoded data to tree.
//TreeNode* deserialize(string data) {
//	int n = data.size();
//	if (n <= 2) return nullptr;
//	vector<int> con;
//	// 获取字符串中的节点数据
//	for (int i = 1; i < n - 1; ++i) {
//		int num = 0;
//		int fu = 1;
//		if (data[i] == 'n') {
//			i += 4;
//			num = -999;
//		}
//		while ((i < n - 1) && (data[i] != ',')) {
//			// 负数处理
//			if (data[i] == '-') {
//				fu = -1;
//				++i;
//			}
//			num = num * 10 + data[i++] - '0';
//		}
//		con.push_back(num*fu);
//	}
//	// 层次建树
//	int i = 0;
//	int siz = con.size();
//	TreeNode* root = new TreeNode(con[i]);
//	queue<TreeNode*> q;
//	q.push(root);
//	while (!q.empty()) {
//		TreeNode* node = q.front();
//		q.pop();
//		if (!node)
//			continue;
//		// 当前节点左节点
//		if ((2 * i + 1) < siz && con[2 * i + 1] != -999) {
//			node->left = new TreeNode(con[2 * i + 1]);
//		}
//		else {
//			node->left = nullptr;
//		}
//		// 当前节点右节点
//		if ((2 * i + 2) < siz && con[2 * i + 2] != -999) {
//			node->right = new TreeNode(con[2 * i + 2]);
//		}
//		else {
//			node->right = nullptr;
//		}
//		q.push(node->left);
//		q.push(node->right);
//		i++;
//	}
//	return root;
//}

//////////////////////////////////////////////////////////////////////////
// Encodes a tree to a single string.
string serialize(TreeNode* root) 
{
	string str;
	queue<TreeNode *> qTree;
	qTree.push(root);

	while (!qTree.empty())
	{
		TreeNode *qHead = qTree.front();
		qTree.pop();

		if (qHead == nullptr)
		{
			str += "null,";
			continue;
		}
		str += to_string(qHead->val);
		str += ",";
		qTree.push(qHead->left);
		qTree.push(qHead->right);
	}
	int len = str.size();
	while (true)
	{
		if (len > 1 && str.back() == ',') len -= 1;
		else break;
		if (len > 4 && str.substr(len - 4, 4) == "null") len -= 4;
		else break;
	}
	str = str.substr(0, len);
	return str;
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data)
{
	auto split = [](string str, string pattern)
	{
		string::size_type Postion;
		vector<string> result;
		str += pattern;
		size_t size = str.size();
		for (size_t i = 0; i < size; i++)
		{
			Postion = str.find(pattern, i);
			if (Postion < size)
			{
				string s = str.substr(i, Postion - i);
				result.push_back(s);
				i = Postion + pattern.size() - 1;
			}
		}
		return result;
	};

	if (data.empty()) return nullptr;
	if (data.back() == '\n') data.pop_back();
	vector<string> splitData = split(data, ",");
	if (data == "" || splitData[0] == "null") return nullptr;

	TreeNode *root = new TreeNode(stoi(splitData[0].c_str()));
	queue<TreeNode *> qTree;
	qTree.push(root);

	int i = 1;
	while (!qTree.empty())
	{
		TreeNode *qHead = nullptr;
		while (qHead == nullptr)
		{
			if (qTree.empty()) return root;
			qHead = qTree.front();
			qTree.pop();
		}

		auto f = [&qTree](const string &s, TreeNode **p) 
		{
			if (s == "null")
			{
				qTree.push(nullptr);
			}
			else
			{
				*p = new TreeNode(stoi(s.c_str()));
				qTree.push(*p);
			}
		};

		if (i == splitData.size()) return root;
		f(splitData[i], &qHead->left);
		i++;

		if (i == splitData.size()) return root;
		f(splitData[i], &qHead->right);
		i++;
	}
	return root;
}


int main()
{
	vector<TreeNode *> N;
	vector<string> A;
	TreeNode *pHead = nullptr;

	A.push_back("1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31");
	pHead = deserialize(A.back());
	N.push_back(pHead);

	//A.push_back("1,2,3,4,5,null,7,8,9,null,null,null,15,null");
	//pHead = deserialize(A.back());
	//N.push_back(pHead);

	//A.push_back("");
	//pHead = deserialize(A.back());
	//N.push_back(pHead);

	//A.push_back("1");
	//pHead = deserialize(A.back());
	//N.push_back(pHead);

	//A.push_back("1,2,3");
	//pHead = deserialize(A.back());
	//N.push_back(pHead);

	//A.push_back("1,2,3,null,5");
	//pHead = deserialize(A.back());
	//N.push_back(pHead);

	for (int i = 0; i < N.size(); i++)
	{
		cout << endl << "///////////////////////////////////////" << endl;
		cout << N[i] << endl;
		DrawTreeNode(N[i]);
		//cout << "serialize = " << endl;
		//string s = serialize(N[i]);
		////cout << s << endl;
		//cout << N[i] << endl;
		//cout << "deserialize = " << endl;
		////TreeNode *ans = deserialize(s);
		//TreeNode *ans;
		//s >> &ans;
		//cout << ans << endl;
	}

	//vector<int> x = GetOffsetForDraw(15);
	//printVectorInt(x);
}

//int main()
//{
//	vector<vector<vector<int>>> N;
//	vector<vector<vector<int>>> A;
//
//	N.push_back({ { 1,3 }, { 2,6 }, { 8,10 }, { 15,18 } });
//	A.push_back({ { 1,6 }, { 8,10 }, { 15,18 } });
//
//	N.push_back({ { 1,4 }, { 4,5 } });
//	A.push_back({ { 1,5 } });
//
//	for (int i = 0; i < N.size(); i++)
//	{
//		cout << endl << "/////////////////////////////////" << endl;
//		printVectorVectorInt(N[i]);
//		vector<vector<int>> ans = merge(N[i]);
//		cout << "merge = " << endl;
//		printVectorVectorInt(A[i]);
//		cout << "my answer = " << endl;
//		printVectorVectorInt(ans);
//	}
//}

// int main()
// {
// 	vector<int> N;
// 	vector<int> A;
// 
// 	N.push_back(4);
// 	A.push_back(1);
// 
// 
// 	for (int i = 0; i < N.size(); i++)
// 	{
// 		cout << endl << "/////////////////////////////////" << endl;
// 		cout << N[i] << " = " << A[i] << endl;
// 		bool ans = canWinNim(N[i]);
// 		cout << "my answer = " << ans << endl;
// 	}
// }


//int main()
//{
//	vector<ListNode *> lists;
//	ListNode *pHead = nullptr;
//	StringToListNode(&pHead, "[4,7,5,3]");
//	lists.push_back(pHead);
//	pHead = nullptr;
//
//	for (auto p : lists)
//	{
//		PrintLinkList(p);
//		pHead = sortList(p);
//		PrintLinkList(pHead);
//		cout << endl;
//	}
//}




//int main()
//{
//	vector<vector<int>> N;
//	vector<int> K;
//	//vector<double> A;
//
//	//N.push_back({ -1, 0, 1, 2, -1, -4 });
//	//K.push_back(1142);
//	//A.push_back(2);
//
//	//N.push_back({ -1, 2, 1, -4 });
//	//K.push_back(1);
//
//	//N.push_back({ 0, 2, 1 });
//	//K.push_back(3);
//
//	N.push_back({ 1, 1, 1, 1 });
//	K.push_back(0);
//
//	//N.push_back({ -1, 0, 1, 2, -1, -4 });
//	//N.push_back({ 0, 0, 1 });
//	//N.push_back({ 0, 0, 0 });
//	//N.push_back({ 0, 0, 0, 1 });
//	//N.push_back({  });
//	//N.push_back({ -2, -3, 0, 0, -2 });
//	//N.push_back({ -1, 0, 1, 0 });
//	//N.push_back({ 3, 0, -2, -1, 1, 2 });
//	//N.push_back({ 1, 1, -2 });
//	//N.push_back({ -4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6 });
//	//N.push_back({ -4, -2, 1, -5, -4, -4, 4, -2, 0, 4, 0, -2, 3, 1, -5, 0 });
//
//
//	for (int i = 0; i < N.size(); i++)
//	{
//		cout << endl << "/////////////////////////////" << endl;
//		printVectorInt(N[i]);
//		sort(N[i].begin(), N[i].end());
//		printVectorInt(N[i]);
//		int a = threeSumClosest(N[i], K[i]);
//		cout << "target = " << K[i] << endl;
//		cout << "threeSum = " << a << endl;
//	}
//}

