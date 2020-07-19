from queue import PriorityQueue 

class Pair : 
    def __init__(self, Deadline, CupRamen) : 
        self.Deadline = Deadline 
        self.CupRamen = CupRamen
    def __lt__(self, other) : 
        if(self.Deadline < other.Dealine) : 
            return True 
        elif (self.Deadline == other.Deadline) : 
            return self.CupRamen > other.CupRamen
        return False
    def __repr__(self) : 
        return '<Pair Dealine={self.Dealine} CupRamen={self.CupRamen}>'

if __name__ == "__main__" : 
    pq = PriorityQueue() 
    n = input() 
    for i in range(n) : 
        a, b = input()
        print(a, b)