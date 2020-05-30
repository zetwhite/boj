#include <iostream> 
#include <algorithm>
using namespace std; 

class Dist{
public: 
    int start; 
    int end; 
    int dist; 
    Dist(int _start, int _end, int _dist):
        start(_start), 
        end(_end), 
        dist(_dist){}
};

bool compare_dist(const Dist& left, const Dist& right){
    return (left.dist > right.dist); 
}

int main(){
    int n, k;
    vector<int> sensors;
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        int s; 
        cin >> s; 
        sensors.push_back(s); 
    }
    sort(sensors.begin(), sensors.end()); 
    vector<Dist> dists;
    for(int i = 0; i < sensors.size()-1; i++){
        if(sensors[i] != sensors[i+1]){
            dists.emplace_back(sensors[i], sensors[i+1], sensors[i+1] - sensors[i]); 
        }
    }
    sort(dists.begin(), dists.end(), compare_dist);
    int result; 
    if(k >= n || (k >= dists.size()+1)){
        result = 0;  
    }
    else{
        k--; 
        vector<int> res;
        res.push_back(sensors[0]); 
        res.push_back(sensors[sensors.size() - 1]); 
        int idx = 0; 
        for(int i = 0; i < k; i++){
            res.push_back(dists[idx].start); 
            res.push_back(dists[idx].end);
            idx++; 
        }
        sort(res.begin(), res.end()); 
        bool go = true; 
        result = 0; 
        for(int i = 0; i < res.size() -1; i++){
            if(go){
                result += (res[i+1] - res[i]);
            }
            go = !go;
        }
    }
    cout << result << endl;

    return 0; 
}