#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <list>
#include <iterator>
#include <sstream>

using namespace std;

void tokenize(const string &s, vector<string> &v){
  char *dups = strdup(s.c_str());
  char *token = strtok(dups, " ");
  while(token != NULL){
    v.push_back(string(token));
    token = strtok(NULL, " ");
  }
  delete(dups);
}

template <typename T>
class SimpleList{
protected:
  void insertEnd(T type);
  void insertStart(T type);
  T removeStart();
private:
  class Node{
  public:
    T data;
    Node* next;
  };
  Node *head; //start
  Node *tail; //end
  string name;
  int count;
public:
  int getSize();
  void init();
  string retrievename();
  void newName(string s);
  virtual void push(T type) = 0;
  virtual T pop() = 0;            //pop does not require any input arguments
};

//Member Function Definitions
template <typename T>
void SimpleList<T>::init(){
  head = NULL;                  //initializing head and tail nudes to start SimpleList
  tail = NULL;
  count == 0;
}
template <typename T>
int SimpleList<T>::getSize(){
  return count;                 //used for determining if list is empty
}
template <typename T>
void SimpleList<T>::newName(string s){
    name = s;
}
template <typename T>
void SimpleList<T>::insertEnd(T type){
  Node *n = new Node;
  n->data = type;
  n->next = NULL;
  if(head == NULL){
    tail = n;
    head = n;
  }
  tail->next = n;
  tail = n;
  count++;
}
template <typename T>
void SimpleList<T>::insertStart(T type){
  Node *n = new Node;
  n->data = type;
  n->next = NULL;
  if(count == 0){
    tail = n;
    head = n;
  }
  n->next = this->head;
  head = n;
  count++;
}
template <typename T>
T SimpleList<T>::removeStart(){
  T ret = head->data;
  Node *n = head;
  head = head->next;
  delete n;     //Frees Memory to avoid Memory Leak
  count--;      //Decreases count to update number of nodes
  return ret;
}
template <typename T>
string SimpleList<T>::retrievename(){
  return name;
}

template <typename T>
class Stack: public SimpleList<T>{
public:
  Stack(string s1){
    this->newName(s1);
    this->init();
  }
  void push(T type){
    this->insertStart(type);
  }
  T pop(){
    return(this->removeStart());      //must return this value as it is used in functions
  }
};

template <typename T>
class Queue: public SimpleList<T>{
public:
  Queue(string s1){
    this->newName(s1);
    this->init();
  }
  void push(T type){
    this->insertEnd(type);
  }
  T pop(){
    return(this->removeStart());      //must return this value as it is used in functions
  }
};

template <typename T>
SimpleList<T>* searchList(list<SimpleList<T> *> *SList, string name){
    for (typename list<SimpleList<T> *>::iterator iter = SList->begin(); iter != SList->end(); iter++){
      if((*iter)->retrievename() == name){
        return *iter;
      }
    }
    return NULL;
}

template <typename T>
void CreateFunc(list<SimpleList<T> *> *SList, string list_Name, string list_Type, ofstream *outf){
  if(searchList(SList, list_Name) != NULL){
    (*outf) << "ERROR: This name already exists!" << endl;
  }
  else{
    if(list_Type == "stack"){
      SimpleList<T> *p = new Stack<T>(list_Name);
      SList->push_back(p);
    } else if(list_Type == "queue"){
      SimpleList<T> *p = new Queue<T>(list_Name);
      SList->push_back(p);
    } else{
      cerr << "ERROR: Invalid List Type!" << endl;
    }
  }
}

template <typename T>
void PushFunc(list<SimpleList<T> *> *SList, string list_Name, T push_Val, ofstream *outf){
  SimpleList<T> *SL = searchList(SList, list_Name);
    if (SL == NULL){
      (*outf) << "ERROR: This name does not exist!" << endl;
    }
    else{
      SL->push(push_Val);
    }
}

template <typename T>
void PopFunc(list<SimpleList<T> *> *SList, string list_Name, ofstream *outf){
  SimpleList<T> *SL = searchList(SList, list_Name);
    if (SL == NULL){
      (*outf) << "ERROR: This name does not exist!" << endl;
    }
    else{
      if(SL->getSize() == 0){
        (*outf) << "ERROR: This list is empty!" << endl;
      } else{
        T ret = SL->pop();
        (*outf) << "Value popped: " << ret << endl;
      }
    }
}

int intVal;
double doubleVal;

int main(){
  string pushbuf;
  string inputfile;
  string outputfile;
  string linebuf;
  vector<string> vect;                //vector for parsing
  ifstream infile;                    //infile stream
  ofstream outfile;                   //outfile stream

  list<SimpleList<int> *> listSLi;    //all integers stacks and queues
  list<SimpleList<double> *> listSLd; //all double stacks and queues
  list<SimpleList<string> *> listSLs; //all string stacks and queues

  cout << "Enter name of input file: ";
  std::getline (std::cin,inputfile);

  cout << "Enter name of output file: ";
  std::getline (std::cin,outputfile);

  infile.open(inputfile.c_str());         //open doesn't take strings as inputs
  if(!infile){                            //error handling for inputfile
    cerr << "ERROR: Unable to open " << inputfile;
    return(-1);
  }

  outfile.open(outputfile.c_str());       //open doesn't take strings as inputs
  if(!outfile){                           //error handling for outputfile
    cerr << "ERROR: Unable to open " << outputfile;
    return(-1);
  }
  while(getline(infile, linebuf)){
    outfile << "PROCESSING COMMAND: " << linebuf << endl;
    tokenize(linebuf, vect);
    if(vect[0] == "create"){
      if(vect[1][0] == 'i'){
        CreateFunc(&listSLi, vect[1], vect[2], &outfile);
      } else if(vect[1][0] == 'd'){
        CreateFunc(&listSLd, vect[1], vect[2], &outfile);
      } else if(vect[1][0] == 's'){
        CreateFunc(&listSLs, vect[1], vect[2], &outfile);
      }
    } else if(vect[0] == "push"){
      if(vect[1][0] == 'i'){
        pushbuf = vect[2];
        stringstream buf(pushbuf);
        buf >> intVal;
        PushFunc(&listSLi, vect[1], intVal, &outfile);
      } else if(vect[1][0] == 'd'){
        pushbuf = vect[2];
        stringstream buf(pushbuf);
        buf >> doubleVal;
        PushFunc(&listSLd, vect[1], doubleVal, &outfile);
      } else if(vect[1][0] == 's'){
        string stringVal = vect[2].c_str();
        PushFunc(&listSLs, vect[1], stringVal, &outfile);
      }
    } else if(vect[0] == "pop"){
      if(vect[1][0] == 'i'){
        PopFunc(&listSLi, vect[1], &outfile);
      } else if(vect[1][0] == 'd'){
        PopFunc(&listSLd, vect[1], &outfile);
      } else if(vect[1][0] == 's'){
        //PopFunc(&listSLs, vect[1], &outfile);
      }
    }
    vect.clear();
  }
  outfile.close();
  infile.close();

  return 0;
}
