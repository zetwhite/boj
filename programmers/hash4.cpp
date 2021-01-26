#include <string>
#include <unordered_map> 
#include <vector>
#include <iostream> 
#include <algorithm> 
using namespace std;

typedef pair<int ,int> coo; 

bool cmp (pair<string,int>& c1, pair<string, int>& c2){
  return c1.second > c2.second; 
}

bool cmp2 (coo& c1, coo& c2){
  if(c1.second == c2.second)
    return c1.first < c2.first; 
  return c1.second > c2.second; 
}

vector<int> solution(vector<string> genres, vector<int> plays) {
  unordered_map<string, int> genre_plays; 
  for(int i = 0; i < genres.size(); i++){
    if(genre_plays.find(genres[i]) == genre_plays.end())
      genre_plays[genres[i]] = plays[i]; 
    else
      genre_plays[genres[i]] += plays[i]; 
  }

  unordered_map<string, vector<coo>> genre_songs; 
  for(int i = 0; i < genres.size(); i++){
    if(genre_songs.find(genres[i]) == genre_songs.end())
      genre_songs[genres[i]] = {{i, plays[i]}}; 
    else
      genre_songs[genres[i]].emplace_back(i, plays[i]); 
  }

  vector<pair<string, int>> popGenres(genre_plays.begin(), genre_plays.end()); 
  sort(popGenres.begin(), popGenres.end(), cmp); 

  for(auto it = genre_songs.begin(); it != genre_songs.end(); it++){
    sort(it->second.begin(), it->second.end(), cmp2); 
  }

  vector<int> ans; 
  for(int i = 0; i < popGenres.size(); i++){
    string gen = popGenres[i].first; 
    auto genPlays = genre_songs[gen]; 
    ans.push_back(genPlays[0].first); 
    if(genPlays.size() > 1){
      ans.push_back(genPlays[1].first); 
    }
  }
  return ans; 
}