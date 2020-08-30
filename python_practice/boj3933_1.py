MAX = 32768

dp = [0] * (MAX + 1)

one = set() 
two = set() 
three = set() 
four = set() 

if __name__ == '__main__' : 
    for i in range(1, 182) : 
        one.add(i*i)
        dp[i*i] += 1 
    print("done one!")
    
    for i in one : 
        print(i)
    for val1 in one : 
        for val2 in one : 
            if(val1 < val2 and val1 + val2 <= MAX) : 
                two.add(val1 + val2) 
                dp[val1 + val2] += (dp[val1] * dp[val2])
    print("done two!")
    for val1 in two : 
        for val2 in one : 
            if(val1 + val2 <= MAX) : 
                three.add(val1 + val2)
                dp[val1 + val2] += ((dp[val1] * dp[val2])/2)
    print("done three!")
    for val1 in two : 
        for val2 in two : 
            if(val1 < val2 and val1 + val2 <= MAX) : 
                dp[val1 + val2] += ((dp[val1] * dp[val2])/2)
    print("done four!")
    
    while True : 
        print("input : ")
        n = int(input())
        if(n == 0) : 
            break
        print(dp[n])