#include <iostream>
#include "streamreader.h"
#include <map>
#include <cassert>
#include <list>
#include<vector>
#include <bits/stdc++.h>

using namespace std;
void add2Pattern(int pre, int cur);
void addItem(int i);
void addPattern(int arr[]);

list<int> intList;
map<vector<int>, int> patterns;
int maxPatternLength = 5;

void updatePattern(map<vector<int>, int>::iterator it)
{
  int size = intList.size();
  vector<int> vect = it->first;
  for(int i=2;i<maxPatternLength;i++)
  {
    list<int>::iterator it = intList.begin();

    int arr[i];
    for(int j=0; j<i-1;j++)
    {
      arr[j] = advance(it, size-i+j);
    }
    arr[i-1] = vect.at(vect.size());
    addPattern(arr);
  }
}

void addPattern(int arr[])
{
  int n = sizeof(arr) / sizeof(arr[0]);
  vector<int> temp(arr,arr+n);
  map<vector<int>, int>::iterator it ;
  it = patterns.find(temp);
  if(it == patterns.end())
  {
    cout<<"Key-value pair not present in map";
    patterns[temp] = 1;
  }
  else{
    int count = it->second +1;
    it->second = count;
    cout << "Key-value pair returned : "
      <<"->" << it->second <<endl;
  }
}

void add2Pattern(int pre, int cur)
{
  vector<int> temp{ pre, cur };
  if(pre!=-1)
  {
    map<vector<int>, int>::iterator it ;
    it = patterns.find(temp);
    if(it == patterns.end())
    {
      cout<<"Key-value pair not present in map";
      patterns[temp] = 1;
      it = patterns.find(temp);
      updatePattern(it);
    }
    else{
      int count = it->second +1;
      it->second = count;
      cout << "Key-value pair returned : "
        <<"->" << it->second <<endl;
    }
  }
}
void addItem(int i)
{

  int size = intList.size();
  list<int>::iterator it = intList.begin();
  if(size!=0)
    add2Pattern(advance(it, size-1),i);
  intList.push_back(i);

}

int main()
{
  cout << "Hello world!" << endl;
  StreamReader stream;

  while (stream.hasNext()){
    uint64_t addr = stream.readNext();

    addItem(addr);

    cout << addr << " ";
  }

  return 0;
}

