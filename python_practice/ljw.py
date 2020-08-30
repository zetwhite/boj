if __name__ == "__main__" :
    
    firstPoint = input().split()
    secondPoint = input().split()
    thirdPoint = input().split()

    firstX = int(firstPoint[0])
    firstY = int(firstPoint[1])

    secondX = int(secondPoint[0])
    secondY = int(secondPoint[1])

    thirdX = int(thirdPoint[0])
    thirdY = int(thirdPoint[1])

    triArea = (secondX - firstX) * (thirdY - firstY) - (secondY - firstY) * (thirdX - firstX)

    if triArea > 0 :
        print(1)
    if triArea < 0 :
        print(-1)
    if triArea == 0 :
        print(0)