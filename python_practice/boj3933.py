MAX = 32768

dp = [0] * (MAX + 1)


if __name__ == '__main__' : 
    for i in range(1, 182) : 
        i2 = i*i
        dp[i2] += 1

        for j in range(i, 182) :
            j2 = i2 + j*j 
            if(j2 <= MAX) : 
                dp[j2] += 1 
            else : 
                break 
                
            for k in range(j, 182) : 
                k2 = j2 + k*k 
                if(k2 <= MAX) : 
                    dp[k2] += 1
                else : 
                    break 

                for l in range(k , 182) : 
                    l2 = k2 + l*l 
                    if(l2 <= MAX) : 
                        dp[l2] += 1
                    else : 
                        break
    
    while True : 
        n = int(input())
        if(n == 0) : 
            break
        else : 
            print(dp[n])

