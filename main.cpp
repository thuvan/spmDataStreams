#include <iostream>
#include <map>
#include <cassert>
#include <list>
#include<vector>
#include <bits/stdc++.h>
#include <unordered_map>
#include <string>
//#include <stdio.h>

using namespace std;



char ch, file_name[255]="input.txt";
FILE *fp;
int row=0;
int c=0;
int dataCount=0;

void openInputFile();
void closeInputFile();
int streamReadNext();


void add2Pattern(int pre, int cur);
void addItem(int i);
void addPattern(int arr[], int n);

list<int> intList;
map<vector<int>, int> patterns;
int maxPatternLengthDefault = 5;
int maxPatternLength = 0;

void updatePattern(map<vector<int>, int>::iterator it)
{
  int size = intList.size();
  //cout<< "size of intList: " << size<<endl;
  vector<int> vect = it->first;
  if(size < maxPatternLengthDefault)
    maxPatternLength = size;
  else
    maxPatternLength = maxPatternLengthDefault;

    //cout<<"maxPatternLength = "<< maxPatternLength<<endl;
  for(int i=3;i<=maxPatternLength;i++)
  {


    int arr[i];
    //cout<<"i =: "<< i<<endl;
    for(int j=0; j<i-1;j++)
    {
        list<int>::iterator in = intList.begin();
        advance(in, size-i+j);

        arr[j] = *in;
        //cout<<endl<< "j = " << j <<" *in = "<<*in<<endl;
    }
    arr[i-1] = vect.at(vect.size()-1);
    //cout<<endl<< "i - 1 = " << i-1 <<" *it = "<<vect.at(vect.size()-1)<<endl;

    //cout <<endl<<"arr: ";
    int arrSize = (sizeof(arr)/sizeof(*arr));
    //for (int k = 0; k < arrSize; k++)
        //cout <<" "<<arr[k];

    addPattern(arr, arrSize);
  }
}

void addPattern(int arr[], int n)
{
  //cout<<endl<<" add Pattern: arr size: "<< n<<endl;
  //for (int k = 0; k < n; k++)
    //cout <<" "<<arr[k];

  vector<int> temp(arr,arr+n);

  //cout<<endl<<"temp: ";
  //for (std::vector<int>::const_iterator i = temp.begin(); i != temp.end(); ++i)
    //std::cout << *i << ' ';


  map<vector<int>, int>::iterator it ;
  it = patterns.find(temp);
  if(it == patterns.end())
  {
    //cout<<"Key-value pair not present in map";
    patterns[temp] = 1;

    //cout << "After insert first time: Key-value pair returned : "<<endl;
    it = patterns.find(temp);
    //for (std::vector<int>::const_iterator i = (it->first).begin(); i != (it->first).end(); ++i)
    //std::cout << *i << ' ';
    //cout<<"->" << it->second <<endl;
  }
  else{
    int count = it->second +1;
    it->second = count;
    //cout << "Key-value pair returned : "<<endl;
    //for (std::vector<int>::const_iterator i = (it->first).begin(); i != (it->first).end(); ++i)
      //std::cout << *i << ' ';
    //cout<<"->" << it->second <<endl;
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
      //cout<<"Key-value pair not present in map (2)";
      patterns[temp] = 1;
      it = patterns.find(temp);
      //for (std::vector<int>::const_iterator i = (it->first).begin(); i != (it->first).end(); ++i)
        //std::cout << *i << ' ';
      //cout<<"->" << it->second <<endl;

      updatePattern(it);
    }
    else{
      int count = it->second +1;
      it->second = count;
      //cout << "Key-value pair returned (2) : ";
      //for (std::vector<int>::const_iterator i = (it->first).begin(); i != (it->first).end(); ++i)
        //std::cout << *i << ' ';
      //cout<<"->" << it->second <<endl;

      updatePattern(it);
    }
  }
}
void addItem(int i)
{

  intList.push_back(i);
  int size = intList.size();
  list<int>::iterator it = intList.begin();
  if(size!=1)
  {
      advance(it, size-2);
      //cout <<"*it: "<<*it <<endl;
      add2Pattern(*it,i);
  }


}



template<typename K, typename V>
void print_map(std::map<K,V> const &m)
{
    for (auto const& pair: m) {
        for (std::vector<int>::const_iterator i = (pair.first).begin(); i != (pair.first).end(); ++i)
            std::cout << *i << ' ';
        cout<<"->" << pair.second <<endl;
    }
}

void writeResults(std::map<vector<int>,int> const &m, int time)
{
  ofstream myfile;
  string fileName = "output_rule_time_" + to_string(time) +".txt";
  myfile.open (fileName);
  string text ="";
  int patternSize = m.size();
  for (auto const& pair: m) {
        vector<int> temp = pair.first;
        int size = temp.size();
        if(size>=2)
        {
            for(int i=0;i<size-1; i++)
            {
                text.append(to_string(temp[i]));
                text +=" ";
            }
            text+= "-> ";
            text += to_string(temp[size-1]);
            text+= " ; ";
            text += to_string(static_cast<double>(pair.second) / patternSize);
            text +="\n";
        }

  }
  myfile << text;
  myfile.close();
  cout<<endl<<"Already written the output_rule.txt";
}

void createRule(map<vector<int>,int> const &m)
{
    cout<<"Begin sort: "<<endl;
    // Declaring the type of Predicate that accepts 2 pairs and return a bool
	typedef std::function<bool(std::pair<std::vector<int>, int>, std::pair<std::vector<int>, int>)> Comparator;

	// Defining a lambda function to compare two pairs. It will compare two pairs using second field
	Comparator compFunctor =
			[](std::pair<std::vector<int>, int> elem1 ,std::pair<std::vector<int>, int> elem2)
			{
				return elem1.second >= elem2.second;
			};

	// Declaring a set that will store the pairs using above comparision logic
	std::set<std::pair<std::vector<int>, int>, Comparator> setOfWords(
			m.begin(), m.end(), compFunctor);

	// Iterate over a set using range base for loop
	// It will display the items in sorted order of values
	for (std::pair<std::vector<int>, int> element : setOfWords)
    {
        for (std::vector<int>::const_iterator i = (element.first).begin(); i != (element.first).end(); ++i)
            std::cout << *i << ' ';
        cout<<"->" << element.second <<endl;
    }

}
/*
int main()
{
  // this main function uses random data
  cout << "Hello world!" << endl;
  StreamReader stream;

  int batchSize = 3;
  int countForBatch = 0;
  int time = -1;
  while (stream.hasNext()){
    uint64_t addr = stream.readNext();
    //cout <<"item: "<< addr << " "<<endl;
    addItem(addr);
    //cout << addr << " ";

    countForBatch++;
      if(countForBatch==batchSize)
      {
          //createRule(patterns);
          countForBatch = 0;
          time++;
          writeResults(patterns, time);
      }

  }
  print_map(patterns);
  //createRule(patterns);
  //writeResults(patterns, time);
  cin.get();
  return 0;
}
*/

int main()
{
  // This main function uses file input
  cout << "Hello world!" << endl;

  openInputFile();
  int addr;

  int batchSize = 3;// you can modify batchsize
  int countForBatch = 0;
    /*
  int a[13] = {1,2,4,1,2,4,5,2,4,5,2,4,5};
  int arrSize = (sizeof(a)/sizeof(*a));
  cout <<"arr size: "<<arrSize <<endl;
  for (int k = 0; k <=arrSize - 1; k++)
  {
      cout << "item: " << a[k]<< endl;
      addItem(a[k]);
      countForBatch++;
      if(countForBatch==batchSize)
      {
          createRule(patterns);
          countForBatch = 0;
      }

  }


  print_map(patterns);
  createRule(patterns);
  */
  int time = -1;

  while (EOF!=(addr=streamReadNext())){
    addItem(addr);
    countForBatch++;
      if(countForBatch==batchSize)
      {
          countForBatch = 0;
          time++;
          writeResults(patterns, time);
      }

  }
  print_map(patterns);
  closeInputFile();

  cin.get();
  return 0;
}


void openInputFile(){
  fp = fopen(file_name, "r"); // read mode
  if (fp == NULL){
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }
}
void closeInputFile(){
  if (fp != NULL)
    fclose(fp);
}

int streamReadNext(){
  int data;
  char ch;
  int inc;
  if(EOF!=(inc=fscanf(fp,"%d%c", &data, &ch))){
      if (inc == 2){
        ++c;//COLUMN count
        dataCount++;
        if(ch == '\n'){
          ++row;
          c = 0;
        }else if(ch != ','){
          fprintf(stderr, "format error of different separator(%c) of Row at %d \n", ch, row);
        }
      }else{
        fprintf(stderr,"fscanf return %d",inc);
      }
      return data;
  }
  return EOF;
}

