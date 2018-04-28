// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " "
	   << (*ipD)->val2 << " "
	   << (*ipD)->val3 << " "
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }

  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.


list<Data *>::iterator i, notsorted, lastsorted, next_sort, later_sorted;


void insertionSort(list<Data *> &l){
  i = l.begin();
  for (i++; i != l.end(); i++){
    notsorted = i;
    lastsorted = i; lastsorted--;
    while ((*notsorted)->val1 < (*lastsorted) ->val1  && notsorted != l.begin()){
      iter_swap(notsorted--, lastsorted--);
    }
  }
}


int getMax2(list<Data *> &l){
    i = l.begin();
    unsigned int mx = (*i)->val2;
    for (i = l.begin(); i != l.end(); i++){
      if ((*i)->val2 > mx)
          mx = (*i)->val2;
    }
    return mx;
}

void countSort2(vector<Data *> &v, int exp, int BASE){
  vector<Data *> vi(v.size());
  int count[BASE] = {0};
  int z = 0;
  for (z = 0; z < v.size(); z++){
    count[(((v[z])->val2)/exp)%BASE]++;
  }
  for (int k = 1; k < BASE; k++){
    count[k] += count[k - 1];
  }
  int n = 1;
  z = v.size();
  z--;
  while (n){
    vi[count[(((v[z])->val2)/exp) % BASE] - 1] = (v[z]);
    count[ (((v[z])->val2)/exp)%BASE ]--;
    if(z == 0){
      break;
    }
    z--;
  }
  v.swap(vi);
}

void RadixSort2(list<Data *> &l){
  int BASE = 500000;
  vector<Data *> v{ make_move_iterator(begin(l)), make_move_iterator(end(l)) };
  unsigned int m  = getMax2(l);
  for (unsigned long exp = 1; m/exp > 0; exp *= BASE){
    countSort2(v, exp, BASE);
  }
  list<Data *> newList(v.begin(), v.end());
  l.swap(newList);
}

int getMax3(list<Data *> &l){
    i = l.begin();
    unsigned int mx = (*i)->val3;
    for (i = l.begin(); i != l.end(); i++){
      if ((*i)->val3 > mx)
          mx = (*i)->val3;
    }
    return mx;
}

void countSort3(vector<Data *> &v, int exp, int BASE){
  vector<Data *> vi(v.size());
  int count[BASE] = {0};
  int z = 0;
  for (z = 0; z < v.size(); z++){
    count[(((v[z])->val3)/exp)%BASE]++;
  }
  for (int k = 1; k < BASE; k++){
    count[k] += count[k - 1];
  }
  int n = 1;
  z = v.size();
  z--;
  while (n){
    vi[count[(((v[z])->val3)/exp) % BASE] - 1] = (v[z]);
    count[ (((v[z])->val3)/exp)%BASE ]--;
    if(z == 0){
      break;
    }
    z--;
  }
  v.swap(vi);
}

void RadixSort3(list<Data *> &l){
  int BASE = 92;
  vector<Data *> v{ make_move_iterator(begin(l)), make_move_iterator(end(l)) };
  unsigned int m  = getMax3(l);
  for (unsigned long exp = 1; m/exp > 0; exp *= BASE){
    countSort3(v, exp, BASE);
  }
  list<Data *> newList(v.begin(), v.end());
  l.swap(newList);
}

bool cmp4(const Data* a1, const Data* a2){
  return(a1->val4 < a2->val4);
}

void sortDataList(list<Data *> &l, int field) {
  // Fill in this function
  if(field == 1){
    insertionSort(l);
  } else if(field == 2){
    RadixSort2(l);
  } else if(field == 3){
    RadixSort3(l);
  } else if(field == 4){
    vector<Data *> v{ make_move_iterator(begin(l)), make_move_iterator(end(l)) };
    stable_sort(v.begin(), v.end(), cmp4);
    list<Data *> newList(v.begin(), v.end());
    l.swap(newList);
  }
}
