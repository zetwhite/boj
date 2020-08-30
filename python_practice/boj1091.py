
def getNext(nextPosition, thisPosition) : 
    tmp = [None] * len(thisPosition) 
    for i in range(len(thisPosition)) : 
        tmp[i] = nextPosition[thisPosition[i]]
    return tmp


def getWhoHave(thisPosition) : 
    left = [None] * len(thisPosition)
    for i in range(len(thisPosition)) : 
        left[i] = thisPosition[i] % 3
    return left 


if __name__ == '__main__' : 
    n = int(input())
    whoHave = list(map(int, input().split()))
    nextPosition = list(map(int, input().split()))
    
    thisPosition = list(range(n))
    start = list(range(n))
    fail = False
    count = 0bo
        left = getWhoHave(thisPosition) 
        if(whoHave == left) : 
            break
        thisPosition = getNext(nextPosition, thisPosition)
        count = count + 1
        if(thisPosition == start) : 
            fail = True 
            break

    if(fail) : 
        print(-1)
    else : 
        print(count)



