class Stack(list) : 
    #is empty(), push(), pop(), top()
    push = list.append 
    def is_empty(self) : 
        if not self : 
            return True 
        else : 
            return False 
    def top(self) : 
        return self[-1]


def getCode() : 
    refinedCode = ""
    braceStack = Stack([])
    braceMatch = {}
    while True : 
        tmpLine = input() 
        if(tmpLine == 'end') : 
            break 
        for i in range(len(tmpLine)) : 
            t = tmpLine[i]
            if(t == '%') : 
                break
            if (t not in '><+-.[]') : 
                continue
            refinedCode += t
            if(t == '[') :
                braceStack.push(len(refinedCode))
            elif(t == ']') : 
                if(braceStack.is_empty()) : 
                    return False, refinedCode
                braceMatch[braceStack.top()-1] = len(refinedCode)-1
                braceMatch[len(refinedCode)-1] = braceStack.top()-1
                braceStack.pop()


    if(braceStack.is_empty() == False) : 
        return False, None, None
    return True, refinedCode, braceMatch


def executeCode(code, braceInfo, stackSize = 32768) : 
    stack = [0] * stackSize
    EIP = 0
    pointer = 0
    while True : 
        if(EIP >= len(code)) : 
            break 
        if(code[EIP] == '>') : 
            pointer += 1
            pointer %= stackSize
        elif(code[EIP] == '<') : 
            pointer -= 1 
            if(pointer < 0) : 
                pointer = stackSize - 1 
        elif(code[EIP] == '+') : 
            stack[pointer] += 1 
            stack[pointer] %= 256
        elif(code[EIP] == '-') : 
            stack[pointer] -= 1 
            if(stack[pointer] < 0) : 
                stack[pointer] = 255 
        elif(code[EIP] == '.') :
            print(chr(stack[pointer]), end='') 
        elif(code[EIP] == '[') : 
            if(stack[pointer] == 0) : 
                EIP = braceInfo[EIP]
        elif(code[EIP] == ']') : 
            if(stack[pointer] != 0) : 
                EIP = braceInfo[EIP] - 1
        EIP = EIP + 1


if __name__ == '__main__' : 
    n = int(input()) 
    for i in range(n) : 
        print("PROGRAM #{}:".format(i+1))
        compileResult, code, braceInfo = getCode() 
        if(not compileResult ) : 
            print("COMPILE ERROR")
        else : 
            #print(code)
            #print(braceInfo)
            executeCode(code, braceInfo)
            print()
            
