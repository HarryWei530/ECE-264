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
  void insertStart(T type);
  void insertEnd(T type);
  T removeEnd();
private:
  class Node{
  public:
    T data;
    Node* next;
  };
  Node *head; //front
  Node *tail; //end
  string name;
public:
  int count;
  void init();
  string retrievename();
  void newName(string s);
  virtual void push(T type) = 0;
  virtual T pop() = 0;         //do not need to know type for pop
};

//Member Function Definitions
template <typename T>
void SimpleList<T>::init(){
  head = NULL;
  tail = NULL;
}
template <typename T>
void SimpleList<T>::newName(string s){
    name = s;
}
template <typename T>
void SimpleList<T>::insertStart(T type){
  Node *n = new Node;
  n->data = type;
  n->next = NULL;
  if(head == NULL){
    tail = n;
    head = n;
  } else{
    tail->next = n;
  }
  tail = n;
}
template <typename T>
void SimpleList<T>::insertEnd(T type){
  Node *n = new Node;
  n->data = type;
  n->next = head;
  head = n;
}
template <typename T>
T SimpleList<T>::removeEnd(){
  if(head == NULL){
    return NULL;
  } else{
    Node *n = head;
    head = head->next;
    T ret = n->data;
    delete n;
    return ret;
  }
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
    this->insertEnd(type);
  }
  T pop(){
    this->removeEnd();
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
    this->insertStart(type);
  }
  T pop(){
    this->removeEnd();
  }
};

int K = 1;

int main(){
  string S1;
  SimpleList<string> *qSLs;
  qSLs = new Stack<string>("test");
  cout << qSLs->retrievename() << "\n";
  string s = "test";
  qSLs->push(s);
  try{
    S1 = qSLs->pop();
  } catch(logic_error &e){
    cout << "PLEASE?\n";
    K = 0;
  }
  if(K == 1){
    cout << S1 << "\n";
  }


return 0;
}
