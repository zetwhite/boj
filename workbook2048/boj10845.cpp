//2019.02.01 roonm813 wrote.
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Queue{
private:
  int storedSize;
  struct node{
    struct node* after = nullptr;
    T value;
  };
  struct node* nodeLink_start;
  struct node* nodeLink_end;
public:
  Queue():storedSize(0){
    nodeLink_start = nullptr;
    nodeLink_end = nullptr;
  }
  int size(){return storedSize;}
  bool empty(){
    if(nodeLink_start == nullptr)
      return true;
    return false;
  }
  void push(T value);
  void pop();
  T front(){
    if(nodeLink_start)
      return nodeLink_start->value;
    else
      return -1;
  }
  T back(){
    if(nodeLink_start)
      return nodeLink_end->value;
    else
      return -1;
  }
};

template <typename T>
void Queue<T>::push(T value){
  struct node* newNode = new node();
  newNode->value = value;
  if(nodeLink_start == nullptr)
    nodeLink_start = newNode;
  else
    nodeLink_end->after = newNode;
  nodeLink_end = newNode;
  storedSize++;
}

template <typename T>
void Queue<T>::pop(){
  if(!nodeLink_start) return;
  struct node* tmp = nodeLink_start->after;
  delete nodeLink_start;
  nodeLink_start = tmp;
  storedSize--;
}

int main(void){
	int commandLine;
	cin >> commandLine;
  string command;

  Queue<int> q;
	for(int a = 0; a < commandLine; a++){
    cin >> command;
    if(command == "push"){
      int newInput;
      cin >> newInput;
      q.push(newInput);
    }
    else if(command == "front")
      cout << q.front() << endl;
    else if(command == "back")
      cout << q.back() << endl;
    else if(command == "size")
      cout << q.size() << endl;
    else if(command == "empty")
      cout << (int)q.empty() << endl;
    else if(command == "pop")
      if(q.empty()) cout << -1 << endl;
      else{
        cout << q.front() <<endl;
        q.pop();
      }
	}
	return 0;
}