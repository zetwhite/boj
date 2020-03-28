#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define MAX_CO 40000

typedef struct Point {
	long long x; 
	long long y; 
	double angle; 
}Point;

Point* makePoint(long long x, long long y) {
	Point* newPoint = (Point*)malloc(sizeof(Point)); 
	newPoint->x = x; 
	newPoint->y = y; 
	return newPoint; 
}

typedef struct stack {
	int using_size;
	int index_here;
	Point** stackStorage;
}Stack;

void initStack(int stackSize, Stack* st) {
	st->stackStorage = (Point**)malloc(sizeof(Point*)*stackSize);
	st->index_here = -1;
	st->using_size = 0;
	return;
}

inline void push(Stack* st, Point * p) {
	st->index_here++;
	st->stackStorage[st->index_here] = p;
	st->using_size++;
	return;
}

Point* pop(Stack* st) {
	Point* p = st->stackStorage[st->index_here];
	st->index_here--;
	st->using_size--;
	return p;
}

Point* top(Stack const* st) {
	return st->stackStorage[st->index_here];
}

Point* underneathTop(Stack const* st) {
	int index = st->index_here - 1; 
	return st->stackStorage[index]; 
}

long long outerP(const Point* vector1, const Point* vector2) {
	return vector1->x*vector2->y - vector1->y*vector2->x;
}

long long getDistance1(const Point* a, const Point* b) {
	return (a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y);
}

Point* gLowest_p; 

int compare(const void* a, const void* b) {
	Point** first = (Point**)a;
	Point** second = (Point**)b;
	if ((*first)->angle >= (*second)->angle) 
			return 1;
	else
		return -1;
}

void sortByDistance(Point** pointStorage, int PointSize) {
	for (int i = 0; i < PointSize - 1; i++) {
		if (pointStorage[i]->angle == pointStorage[i + 1]->angle) {
			if (getDistance1(gLowest_p, pointStorage[i]) >= getDistance1(gLowest_p, pointStorage[i + 1])) {
				Point* tmp = pointStorage[i];
				pointStorage[i] = pointStorage[i + 1];
				pointStorage[i + 1] = tmp;
			}
		}
	}
}

void memoryFree(Point** pointStorage, int PointSize) {
	for (int i = 0; i < PointSize; i++) {
		free(pointStorage[i]); 
	}
	free(pointStorage); 
}

int main(void) {
	int PointNumber;
	scanf("%d", &PointNumber);
	Point** pointStorage = (Point**)malloc((sizeof(Point*)*PointNumber+1));
	long long lowest_coY = MAX_CO;
	long long lowest_coX = MAX_CO;

	for (int i = 0; i < PointNumber; i++) {
		long long x, y;
		scanf("%lld %lld", &x, &y);
		pointStorage[i] = makePoint(x, y);
		if (lowest_coY > y) {
			lowest_coY = y;
			lowest_coX = x;
			gLowest_p = pointStorage[i];
		}
		else if (lowest_coY == y && lowest_coX > x) {
			lowest_coX = x;
			gLowest_p = pointStorage[i];
		}
	}

	if (PointNumber == 1)
		return 1;

	for (int i = 0; i < PointNumber; i++) {
		if (pointStorage[i] == gLowest_p) {
			pointStorage[i]->angle = -DBL_MAX;
		}
		else {		
			long long dif_x = pointStorage[i]->x - gLowest_p->x;
			long long dif_y = pointStorage[i]->y - gLowest_p->y;
			pointStorage[i]->angle = atan2(dif_y, dif_x); 
		}
	}
	
	qsort(pointStorage, PointNumber, sizeof(Point*), compare);
	sortByDistance(pointStorage, PointNumber); 
	
	Stack convexHull;
	initStack(PointNumber, &convexHull);
	push(&convexHull, pointStorage[0]);
	push(&convexHull, pointStorage[1]);
	
	Point* lastPushed = top(&convexHull);
	Point* vectorOld = makePoint(lastPushed->x - pointStorage[0]->x, lastPushed->y - pointStorage[0]->y);
	Point* vectorYoung;

	for (int i = 2; i < PointNumber; ) {
		vectorYoung = makePoint(pointStorage[i]->x - lastPushed->x, pointStorage[i]->y - lastPushed->y);
		if (outerP(vectorOld, vectorYoung) <= 0) {
			pop(&convexHull);
			if (convexHull.using_size == 1) {
				push(&convexHull, pointStorage[i]);
				i++;
			}
			lastPushed = top(&convexHull);
			vectorOld = makePoint(lastPushed->x - underneathTop(&convexHull)->x, lastPushed->y - underneathTop(&convexHull)->y);
		}
		else {
			push(&convexHull, pointStorage[i]);
			lastPushed = top(&convexHull);
			vectorOld = vectorYoung;
			i++;
		}
	}
	printf("%d", convexHull.using_size);
	memoryFree(pointStorage, PointNumber); 
	return 0;
}