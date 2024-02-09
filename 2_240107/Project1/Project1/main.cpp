#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;


struct Point
{
    int x;
    int y;
};


bool visit[500][500] = { false, };
vector<vector<int>> ground;
int hjkl[4][2] = { {0, -1}, {-1, 0}, {1, 0}, {0, 1} };
int n, m;


void initGround(void);
int solution(vector<vector<int>> land);
void clearVisit(void);
void myBfs(vector<vector<int>> land, int i, int j, int* answer_buff);
vector<vector<int>> land_buff;
map<int, int> id_store;

int id_header = 2;

int main()
{
    initGround();

    cout << solution(ground);

    return 0;
}


void initGround(void)
{
    vector<int> row;
    row = { 0, 0, 0, 1, 1, 1, 0, 0 };
    ground.push_back(row);
    row = { 0, 0, 0, 0, 1, 1, 0, 0 };
    ground.push_back(row);
    row = { 1, 1, 0, 0, 0, 1, 1, 0 };
    ground.push_back(row);
    row = { 1, 1, 1, 0, 0, 0, 0, 0 };
    ground.push_back(row);
    row = { 1, 1, 1, 0, 0, 0, 1, 1 };
    ground.push_back(row);
}


int solution(vector<vector<int>> land)
{
    int answer = 0;

    n = (int)land.size();
    m = (int)land[0].size();

    clearVisit();

    land_buff = land;

    for (int j = 0; j < m; j++)
    {
        int answer_buff = 0;
        set<int> now_id_group;

        for (int i = 0; i < n; i++)
        {
            if (visit[i][j] != true && land[i][j] != 0)
            {
                int try_buff = 0;
                myBfs(land, i, j, &try_buff);
                id_store[id_header] = try_buff;
                answer_buff += try_buff;
                now_id_group.insert(land[i][j]);
                id_header += 1;
            }
            else if (visit[i][j] == true && land[i][j] != 0 && land_buff[i][j] < id_header)
            {
                if (now_id_group.size() == 0)
                {
                    answer_buff += id_store[land_buff[i][j]];
                    now_id_group.insert(land_buff[i][j]);
                }
                else if (now_id_group.find(land_buff[i][j]) == now_id_group.end())
                {
                    answer_buff += id_store[land_buff[i][j]];
                }
            }

            answer = max(answer, answer_buff);
        }
    }

    return answer;
}

void clearVisit(void)
{
    memset(visit, false, sizeof(visit));
}

void myBfs(vector<vector<int>> land, int i, int j, int *answer_buff)
{
    queue<Point> queue_point;
    Point start_point = { i, j };
    visit[i][j] = true;
    land_buff[i][j] = id_header;
    *answer_buff += 1;
    queue_point.push(start_point);

    while (queue_point.size() != 0)
    {
        Point point_buff = queue_point.front();

        queue_point.pop();
        if (land[point_buff.x][point_buff.y] != 0)
        {
            for (int k = 0; k < 4; k++)
            {
                int row = point_buff.x + hjkl[k][0];
                int column = point_buff.y + hjkl[k][1];

                if (row < 0 || column < 0 || row > n - 1 || column > m - 1)
                {
                    continue;
                }
                if (visit[row][column] == true)
                {
                    continue;
                }
                if (land[row][column] == 0)
                {
                    continue;
                }
                visit[row][column] = true;
                land_buff[row][column] = id_header;
                *answer_buff += 1;

                queue_point.push({ row, column });
            }
        }
    }
}