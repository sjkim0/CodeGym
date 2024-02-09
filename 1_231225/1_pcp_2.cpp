#include <string>
#include <vector>
#include <set>
#include <queue>
#include <iostream>

using namespace std;

// 석탄 덩어리 구조체 
struct Group{
    int count;
    set<int> possibleY;
};

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int height,width;
bool visited[500][500];
vector<vector<int>> map; // 맵
vector<Group> groups; // 석탄 덩어리 그룹

//반환하는 것은 석탄 덩어리
Group bfs(int sx, int sy){
    queue<pair<int,int>> q;
    set<int> possibleY;
    q.push({sx,sy});
    possibleY.insert(sy);
    visited[sx][sy] = true;
    int count = 1;
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= height || ny >= width 
               || map[nx][ny] == 0 || visited[nx][ny]) continue;
            visited[nx][ny] = true;
            q.push({nx,ny});
            count++;
            possibleY.insert(ny);
        }
    }
    return {count,possibleY};
}

void init(vector<vector<int>> land){
    map = land;
    height = land.size();
    width = land[0].size();
    
    for(int i = 0; i < land.size(); i++){
        for(int j = 0; j < land[i].size(); j++){
        	// 석유가 없거나, 이미 방문한 땅이면 패스
            if(visited[i][j] || land[i][j] == 0) continue;
            groups.push_back(bfs(i,j));
        }
    }
}

int solution(vector<vector<int>> land) {
    init(land);
    int answer[501] = {0};
    int maxNum = 0;
    for(int i = 0; i < groups.size(); i++){
        for(auto it : groups[i].possibleY){
            answer[it] += groups[i].count;
            maxNum = max(maxNum,answer[it]);
        }
    }
    return maxNum;
}

int main()
{
    vector<vector<int>> land = 
    {
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {1, 1, 0, 0, 0, 1, 1, 0},
        {1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 1, 1}
    };

    cout << solution(land);
}