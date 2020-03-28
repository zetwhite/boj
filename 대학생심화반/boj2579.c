#include <stdio.h>
#include <stdlib.h>

int getMax(int value1, int value2) {
	int result; 
	if (value1 > value2)
		result = value1;
	else
		result = value2; 
	return result; 
}


int main(void) {
	int stairSize; 
	scanf("%d", &stairSize); 
	
	int* stairNumber =(int*)malloc(sizeof(int)*stairSize);
	for (int i = 0; i < stairSize; i++) {
		scanf("%d", stairNumber + i); 
	}

	int* stairSum = (int*)malloc(sizeof(int)* stairSize); 
	stairSum[0] = stairNumber[0]; 
	stairSum[1] = stairNumber[0] + stairNumber[1]; 
	stairSum[2] = getMax(stairNumber[0] + stairNumber[2], stairNumber[1] + stairNumber[2]); 
	for (int i = 3; i < stairSize; i++) {
		stairSum[i] = getMax(stairNumber[i] + stairSum[i - 2], stairNumber[i] + stairNumber[i - 1] + stairSum[i - 3]); 
	}

	printf("%d", stairSum[stairSize - 1]); 
	
	return 0; 
}