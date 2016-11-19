// This file is a quick cheatsheet for syntax

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#include <set> // set, multiset
#include <unordered_set>
#include <map> // map, multimap
#include <unordered_map>
using namespace std; 

// 1D Vector
vector<int> arr (10, 0); // initialize 10 elements iwth 0
arr.size();
if(!arr.empty())
for(int i = 0; i < arr.size(); i++)

// 2D Vector

int size = 10;
vector< vector<int> > matrix(size, vector<int> (size, 0))
for (int i = 0; i < matrix.size(); i++)
{
  for (int j = 0; j < matrix[i].size(); j++)
  {
  }
}

// Strings
s1.assign(s2);
s1.compare(s2);
s1.append(s2);
s1.push_back(singleCharacter);
s1.insert(startIndex, s2);
s1.erase(startIndex, amountToErase);
s1.substr(startIndex, lengthOfSubstr);

// Queue
queue<int> q;
q.empty();
q.push(val);
q.front();
q.pop();
q.size();

// Stack
stack<int> s;
s.empty();
s.push(val);
s.top();
s.pop();
s.size();

// Set (single unique value)
set<int> s;

// Map
map<int, int> m;
m[key] = val;
if(m.count(key)) // check if it exist 
if(m.find(key) != m.end()) // check if it exist
m.erase(key)
