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
    return(this->removeEnd());
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
    return(this->removeEnd());
  }
};

int Z = 0, W = 0, X = 0, Q = 0, out = 0, n = 0, K = 0;
double D = 0, outd = 0;

int main(){

    std::string inputfile;
    std::string outputfile;
    std::vector<string> vect;
    ifstream infile;                    //infile stream
    ofstream outfile;                   //outfile stream

    list<SimpleList<int> *> listSLi;    //all integers stacks and queues
    list<SimpleList<double> *> listSLd; //all double stacks and queues
    list<SimpleList<string> *> listSLs; //all string stacks and queues

    list<SimpleList <int> *>::iterator it;    //iterator for int list
    list<SimpleList <double> *>::iterator dt; //iterator for double list
    list<SimpleList <string> *>::iterator st; //iterator for string list

    string pushbuf;
    string S;
    string S1;
    string outs;
    const static string teststring;

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
    string linebuf;
    while(!infile.eof()){
      Z = 0;
      W = 0;
      Q = 0;
      K = 0;
      getline(infile, linebuf);
      tokenize(linebuf, vect);
      if(vect[0] == "create"){
        outfile << "PROCESSING COMMAND: " << linebuf << "\n";
        if(vect[1][0] == 'i'){
          for(it = listSLi.begin(); it != listSLi.end(); ++it){
            if((*it)->retrievename() == vect[1]){
              Z = 1;
              break;
            }
          }
        }
        if(vect[1][0] == 'd'){
          for(dt = listSLd.begin(); dt != listSLd.end(); ++dt){
            if((*dt)->retrievename() == vect[1]){
              Z = 1;
              break;
            }
          }
        }
        if(vect[1][0] == 's'){
          for(st = listSLs.begin(); st != listSLs.end(); ++st){
            if((*st)->retrievename() == vect[1]){
              Z = 1;
              break;
            }
          }
        }

        if(Z){
          outfile << "ERROR: This name already exists!\n";
        } else if(vect[1][0] == 'i' && vect[2] == "stack"){
          SimpleList<int> *pSLi;
          pSLi = new Stack<int>(vect[1]);
          listSLi.push_front(pSLi);
        } else if(vect[1][0] == 'd' && vect[2] == "stack"){
          SimpleList<double> *pSLd;
          pSLd = new Stack<double>(vect[1]);
          listSLd.push_front(pSLd);
        } else if(vect[1][0] == 's' && vect[2] == "stack"){
          SimpleList<string> *pSLs;
          pSLs = new Stack<string>(vect[1]);
          listSLs.push_front(pSLs);
        } else if(vect[1][0] == 'i' && vect[2] == "queue"){
          SimpleList<int> *qSLi;
          qSLi = new Queue<int>(vect[1]);
          listSLi.push_front(qSLi);
        } else if(vect[1][0] == 'd' && vect[2] == "queue"){
          SimpleList<double> *qSLd;
          qSLd = new Queue<double>(vect[1]);
          listSLd.push_front(qSLd);
        } else if(vect[1][0] == 's' && vect[2] == "queue"){
          SimpleList<string> *qSLs;
          qSLs = new Queue<string>(vect[1]);
          listSLs.push_front(qSLs);
        } else{
          outfile << "ERROR: Invalid List Type!\n";
        }
      } else if(vect[0] == "push"){
        outfile << "PROCESSING COMMAND: " << linebuf << "\n";

        if(vect[1][0] == 'i'){
          for(it = listSLi.begin(); it != listSLi.end(); ++it){
            if((*it)->retrievename() == vect[1]){
              pushbuf = vect[2];
              stringstream buf(pushbuf);
              buf >> X;
              (*it)->push(X);
              W = 1;
              break;
            } else{
              W = 0;
            }
          }
          if(W == 0){
            outfile << "ERROR: This name does not exist!\n";
          }
        } else if(vect[1][0] == 'd'){
          for(dt = listSLd.begin(); dt != listSLd.end(); ++dt){
            if((*dt)->retrievename() == vect[1]){
              pushbuf = vect[2];
              stringstream buf(pushbuf);
              buf >> D;
              (*dt)->push(D);
              W = 1;
              break;
            } else {
              W = 0;
            }
          }
          if(W == 0){
            outfile << "ERROR: This name does not exist!\n";
          }
        } else if(vect[1][0] == 's'){
          for(st = listSLs.begin(); st != listSLs.end(); ++st){
              if((*st)->retrievename() == vect[1]){
                pushbuf = vect[2];
                stringstream buf(pushbuf);
                buf >> S;
                (*st)->push(S);
                W = 1;
                break;
              }
          }
            if(W == 0){
            outfile << "ERROR: This name does not exist!\n";
          }
        } else{
          outfile << "ERROR: Invalid List Name!\n";
        }

      } else if(vect[0] == "pop"){
        outfile << "PROCESSING COMMAND: " << linebuf << "\n";

        if(vect[1][0] == 'i'){
          for(it = listSLi.begin(); it != listSLi.end(); ++it){
            if((*it)->retrievename() == vect[1]){
              out = (*it)->pop();
              if(out == NULL){
                outfile << "ERROR: This list is empty!\n";
              } else{
                outfile << "Value popped: " << out << "\n";
              }
              Q = 1;
              break;
            }
          }
          if(Q == 0){
            outfile << "ERROR: This name does not exist!\n";
          }
        } else if(vect[1][0] == 'd'){
          for(dt = listSLd.begin(); dt != listSLd.end(); ++dt){
            if((*dt)->retrievename() == vect[1]){
              outd = (*dt)->pop();
              if(outd == NULL){
                outfile << "ERROR: This list is empty!\n";
              } else{
                outfile << "Value popped: " << outd << "\n";
              }
              Q = 1;
              break;
            }
          }
          if(Q == 0){
            outfile << "ERROR: This name does not exist!\n";
          }
        } else if(vect[1][0] == 's'){
          for(st = listSLs.begin(); st != listSLs.end(); ++st){
            if((*st)->retrievename() == vect[1]){
              try{
                string teststring1 = (*st)->pop();
                stringstream buf(teststring1);
                buf >> S1;
              } catch(logic_error &e){
                outfile << "ERROR: This list is empty!\n";
                K = 1;
                Q = 1;
                break;
              }
              if(K == 0){
                outfile << "Value popped: " << S1 << "\n";
                Q = 1;
                break;
              }
              break;
            }
          }
          if(Q == 0){
            outfile << "ERROR: This name does not exist!\n";
          }
        }

      } else if(vect[0] == "\0" || vect[0] == "\n"){

      } else{
        outfile << "ERROR: Invalid Command!\n";
      }
      vect.clear();
    }

    return 0;
}
