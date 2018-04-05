/*
* Ali Rahman
* DSA Coding Assignment 1
* This Program contains classes used to define a SimpleList which is used in two
* derived classes, Stack and Queue.  When the program runs it asks the user for
* an input text file and an output text file before reading the input file line
* by line performing the specified commands, create, push, or pop.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <list>
#include <iterator>
#include <sstream>

using namespace std;

void tokenize(const string &s, vector<string> &v){
  char *dups = strdup(s.c_str());       //duplicating input string to avoid overrite
  char *token = strtok(dups, " ");      //strtok based on spaces
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
    T data;         // type T data variable
    Node* next;     // pointer to next node
  };
  Node *head; //start
  Node *tail; //end
  string name;
  int count;  //list size
public:
  int getSize();
  void init();
  string retrievename();
  void newName(string s);
  virtual void push(T type) = 0;  //virtual functions declared in derived classes
  virtual T pop() = 0;            //pop does not require any input arguments
};

//Member Function Definitions
template <typename T>
void SimpleList<T>::init(){
  head = NULL;                  //initializing head and tail nudes to start SimpleList
  tail = NULL;
  count = 0;                    //initializing size of stack/queue to zero
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
  n->data = type;        //sets data variable in node to input variable
  n->next = NULL;
  if(count == 0){        //if no nodes in list set head and tail to new node
    tail = n;
    head = n;
  }
  tail->next = n;       //sets the current tail's next node to the new node
  tail = n;             //moves tail node to new tail
  count++;              //updates list size
}
template <typename T>
void SimpleList<T>::insertStart(T type){
  Node *n = new Node;
  n->data = type;
  n->next = NULL;
  if(count == 0){       //if list is empty then the head and tail of the list are both set to the new node
    tail = n;
    head = n;
  }
  n->next = this->head; //sets the next node of the current node to the head
  head = n;             //moves head node to new head
  count++;              //updates list size
}
template <typename T>
T SimpleList<T>::removeStart(){
  Node *n = head;       //creates node that corresponds to head
  T ret = n->data;      //obtains return value
  head = head->next;    //moves head back
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
      //iterates through list to find if stack/queue with specified name exists
      if((*iter)->retrievename() == name){
        return *iter;                  //returns pointer to Stack/Queue that corresponds to name specified
      }
    }
    return NULL;                       //otherwise returns NULL
}

template <typename T>
void CreateFunc(list<SimpleList<T> *> *SList, string list_Name, string list_Type, ofstream *outf){
  if(searchList(SList, list_Name) != NULL){
    (*outf) << "ERROR: This name already exists!" << endl;  //name exists
  }
  else{
    if(list_Type == "stack"){
      SimpleList<T> *p = new Stack<T>(list_Name);           //creates new Stack and initializes
      SList->push_back(p);                                  //pushes stack onto appropriate list
    } else if(list_Type == "queue"){
      SimpleList<T> *q = new Queue<T>(list_Name);           //creates new Queue and initializes
      SList->push_back(q);                                  //pushes queue onto appropriate list
    } else{
      cerr << "ERROR: Invalid List Type!" << endl;          //Additional Error Check for list type
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
        (*outf) << "Value popped: " << SL->pop() << endl;
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
  getline (cin,inputfile);

  cout << "Enter name of output file: ";
  getline (cin,outputfile);

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
      if(vect[1][0] == 'i'){        //conversion
        pushbuf = vect[2];          //from
        stringstream buf(pushbuf);  //string to
        buf >> intVal;              //int
        PushFunc(&listSLi, vect[1], intVal, &outfile);
      } else if(vect[1][0] == 'd'){ //conversion
        pushbuf = vect[2];          //from
        stringstream buf(pushbuf);  //string to
        buf >> doubleVal;           //double
        PushFunc(&listSLd, vect[1], doubleVal, &outfile);
      } else if(vect[1][0] == 's'){
        string stringVal = vect[2].c_str();   //constant string pushed
        PushFunc(&listSLs, vect[1], stringVal, &outfile);
      }
    } else if(vect[0] == "pop"){
      if(vect[1][0] == 'i'){
        PopFunc(&listSLi, vect[1], &outfile);
      } else if(vect[1][0] == 'd'){
        PopFunc(&listSLd, vect[1], &outfile);
      } else if(vect[1][0] == 's'){
        PopFunc(&listSLs, vect[1], &outfile);
      }
    }
    vect.clear();           //clears vector for next iteration to avoid problems
  }
  outfile.close();          //closing file streams at end of program
  infile.close();

  return 0;
}
