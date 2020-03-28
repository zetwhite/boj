//2019.01.21 roonm813 wrote.
#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;
#define INF 20000000
typedef pair<int, int> intPair;

class Vertex{
public:
  vector<intPair> nextVisit; //(expense, nextVertex)
  int totalExpense;
  Vertex():totalExpense(INF){}
};

int main(void){
	int numberOfVertex;
	int numberOfEdge;
	int start;
	scanf("%d %d", &numberOfVertex, &numberOfEdge);
	scanf("%d", &start);

	Vertex* vertexs = new Vertex[numberOfVertex+1];

  for(int a = 0; a < numberOfEdge; a++){
    int vertex1, vertex2, expense;
    scanf("%d %d %d", &vertex1, &vertex2, &expense);
    vertexs[vertex1].nextVisit.push_back(make_pair(expense, vertex2));
  }

  priority_queue<intPair, vector<intPair>, greater<intPair>> updates; //(new expense, vertexNumber)
  vertexs[start].totalExpense = 0;
  updates.emplace(0, start);
 
  while(!updates.empty()){
    intPair update = updates.top();
    int verNum = update.second;
    int newExp = update.first;
    updates.pop();

    for(int i = 0; i < vertexs[verNum].nextVisit.size(); i++){
      int _verNum = vertexs[verNum].nextVisit[i].second;
      int _newExp = vertexs[verNum].nextVisit[i].first + newExp;
      if(vertexs[_verNum].totalExpense > _newExp){
        vertexs[_verNum].totalExpense = _newExp;
        updates.emplace(_newExp, _verNum);
      }
    }
  }

  for(int a = 1; a < numberOfVertex + 1; a++){
    int result = vertexs[a].totalExpense;
    if(result == INF)
      printf("INF\n");
    else
      printf("%d\n", vertexs[a].totalExpense);
  }
	return 0;
}