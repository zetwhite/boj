//2018.01.13 roonm813 writes.
#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;

class Connection{
public:
    int computerNumber1;
    int computerNumber2;
    int expense;
    Connection(int _computerNumber1, int _computerNumber2, int _expense)
    : computerNumber1(_computerNumber1), computerNumber2(_computerNumber2), expense(_expense) {}
};


bool operator > (const Connection& connect1, const Connection& connect2){
    if(connect1.expense > connect2.expense)
        return true;
    return false;
}

inline int findGroup(vector<set<int>>& connectedComponent, int vertexNumber){
    int groupNumber = -1;
    for(int i = 0; i < connectedComponent.size(); i++){
        set<int>::iterator it = connectedComponent[i].find(vertexNumber);
        if(it != connectedComponent[i].end()){
            groupNumber = i;
            break;
        }
    }
    return groupNumber;
}

int main(void){
    int NumberOfComputer;
    int NumberOfConnection;
    int maxValue = 0;
   // cin >> NumberOfComputer;
   // cin >> NumberOfConnection;
    scanf("%d", &NumberOfComputer);
    scanf("%d", &NumberOfConnection);

    priority_queue<Connection, vector<Connection>, greater<Connection>> connections;
    int computerNumber1;
    int computerNumber2;
    int expense;
    for(int i = 0; i < NumberOfConnection; i++){
        scanf("%d %d %d", &computerNumber1, &computerNumber2, &expense);
      //  cin >> computerNumber1 >> computerNumber2 >> expense;
        if(computerNumber1 != computerNumber2)
        connections.emplace(computerNumber1, computerNumber2, expense);
    }

    vector<set<int>> connectedComponent;
    int connectedCount = 0;
    int totalExpense = 0;

    while(!connections.empty()){
        Connection connection = connections.top();
        connections.pop();
        int group1 = findGroup(connectedComponent, connection.computerNumber1);
        int group2 = findGroup(connectedComponent, connection.computerNumber2);
        if(group1 != -1 && group1 == group2)
          continue;
        if(group1 == -1 && group2 == -1){ //both are not visited
            set<int> newSet = {connection.computerNumber1, connection.computerNumber2};
            connectedComponent.push_back(newSet);
        }
        else if(group1 == -1 && group2 != -1){ //added existing group
            connectedComponent[group2].insert(connection.computerNumber1);
        }
        else if(group1 != -1 && group2 == -1){ //added existing group
            connectedComponent[group1].insert(connection.computerNumber2);
        }
        else if(group1 != -1 && group2 != -1 && group1 != group2){ //merge two group
            if(group1 < group2){
                int tmp = group1;
                group1 = group2;
                group2 = tmp;
            }
            connectedComponent[group2].insert(connectedComponent[group1].begin(), connectedComponent[group1].end());
            connectedComponent.erase(connectedComponent.begin()+group1);
        }
        else{
            continue;
        }
        connectedCount++;
        totalExpense += connection.expense;
        if(connectedCount >= NumberOfComputer-1){
            break;
        }
    }

    cout << totalExpense - maxValue<< endl;
	return 0;
}
