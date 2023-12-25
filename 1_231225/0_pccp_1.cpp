/*
 * 붕대감기
 * t초동안 1초마다 x만큼 체력 회복
 * t초 연속 붕대를 감는데 성공한다면 y만큼 추가 회복
 * 최대 체력이 존재, 현재 체력이 최대체력보다 커지는것을 불가
 * 공격당하면 체력회복 불가
 * 끝나면 붕대감기 다시 사용
 * 연속 성공시간 0으로 초기화
 * 붕대감기 기술정보, 캐릭터 최대체력, 공격패턴이 주어질때
 * 생존할 수 있는지 궁금
 * 남은 체력 리턴 죽으면 return -1
 */


#include <iostream>
#include <vector>
using namespace std;

int solution(vector<int> bandage, int health, vector<vector<int>> attacks) 
{
    int answer = 0;

    int t = bandage[0];  // 시전 시간
    int x = bandage[1];  // 초당 회복량
    int y = bandage[2];  // 추가 회복량
    int continue_tick = 0;

    int health_buff = health; 

    int last_tick = attacks[attacks.size() - 1][0];

    for(int i = 1; i <= last_tick; i++)
    {
        // 0. Check attack occured;
        // 1. Healing;

        // 0. Check attack occured;
        vector<int> attack_buff = attacks[0];
        int attack_time_buff = attack_buff[0];
        int dealing = attack_buff[1];

        if(attack_time_buff == i)
        {
            attacks.erase(attacks.begin());

            continue_tick = 0;
            health_buff -= dealing;

            if(health_buff <= 0)
            {
                return -1;
            }
        }
        else  // 1. Healing;
        {
            health_buff += x;
            continue_tick += 1;

            if(continue_tick == t)
            {
                continue_tick = 0;
                health_buff += y;   
            }
            if(health_buff > health)
            {
                health_buff = health;
            }
        }
        int a = 0;
    }

    answer = health_buff;
    
    return answer;
}

int main()
{
    vector<int> bandage = {3, 2, 7};
    int health = 20;
    vector<vector<int>> attacks = 
    {
        {1, 15},
        {5, 16},
        {8, 6},
    };

    int my_result = solution(bandage, health, attacks);

    cout << my_result;

    return 0;
}