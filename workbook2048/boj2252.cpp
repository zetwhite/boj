#include <stdio.h>
#include <vector>
#include <queue>

using namespace std; 
class Node {
public: 
	vector<int> myChildren; 
	int myParentCount;
	bool alreadyIn; 
	Node() {
		myParentCount = 0; 
	}; 
};

int main(void) {
	int studentNumber;
	int compareCount;
	queue<int> nominates; 
	scanf("%d %d", &studentNumber, &compareCount); 
	Node** nodeTree = new Node*[studentNumber]; 
	
	for (int i = 0; i < studentNumber; i++) {
		nodeTree[i] =  new Node(); 
	}

	for (int i = 0; i < compareCount; i++) {
		int parentNode, childNode; 
		scanf("%d %d", &parentNode, &childNode); 
		nodeTree[parentNode - 1]->myChildren.push_back(childNode - 1); 
		nodeTree[childNode - 1]->myParentCount++; 
	}


	for (int i = 0; i < studentNumber; i++) {
		if (nodeTree[i]->myParentCount == 0) {
			nominates.push(i); 
		}
	}

	while (true) {
			int NominatesSize = nominates.size();
			if (NominatesSize == 0)
				break; 
			for (int r = 0; r< NominatesSize; r++) {
				int i = nominates.front(); 
				nominates.pop(); 
				if (nodeTree[i]->myParentCount == 0) {
					printf("%d ", i + 1); 
					nodeTree[i]->myParentCount = -1; 
					int myChildSize = nodeTree[i]->myChildren.size(); 
					for (int k = 0; k < myChildSize; k++) {
						//printf("%d: child size %d\n", i + 1, nodeTree[i]->myChildren.size()); 
						int child = nodeTree[i]->myChildren.back(); 
						nodeTree[i]->myChildren.pop_back(); 
						nodeTree[child]->myParentCount--; 
						nominates.push(child); 
					}
				}
			}
	}
	return 0; 
}