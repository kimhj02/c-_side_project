#include <iostream>
#include <cmath> // for std::abs

#pragma warning(disable : 4996)
using namespace std;

class person 
{
private:
    int xpos;
    int ypos;
    int hp;
    int mp;
    int damage;
    int armor;

public:
    person(int xpos = 0, int ypos = 0, int hp = 100, int mp = 50, int damage = 10, int armor = 5)
        : xpos(xpos), ypos(ypos), hp(hp), mp(mp), damage(damage), armor(armor) {} // 생성자

    void xmove(int value) { // x 이동
        xpos += value;
    }

    void ymove(int value) { // y 이동
        ypos += value;
    }

    double distance(const person& other) const { // 두 객체 간 거리 계산
        return sqrt(pow(xpos - other.xpos, 2) + pow(ypos - other.ypos, 2));
    }

    void attack(person& target) { // 공격 함수
        if (distance(target) <= 1) 
        {
            int effective_damage = damage - target.armor;
            if (effective_damage < 0) effective_damage = 0; // 방어력이 공격력보다 클 경우 최소 데미지는 0
            target.hp -= effective_damage;
            cout << "공격 성공! 상대방의 체력: " << target.hp << endl;
        }
        else 
        {
            cout << "상대방이 사정거리 밖에 있습니다. 더 가까이 이동하십시오." << endl;
        }
    }

    void displayStatus() const { // 상태 표시 함수
        cout << "위치: (" << xpos << ", " << ypos << "), 체력: " << hp << ", 마나: " << mp << endl;
    }

    // 체력 확인을 위한 getter
    int getHp() const {
        return hp;
    }
};

void playerTurn(person& player, person& opponent) {
    int choice;
    cout << "플레이어의 턴입니다. 행동을 선택하십시오:\n";
    cout << "1. 이동\n";
    cout << "2. 공격\n";
    cin >> choice;

    if (choice == 1) {
        int x, y;
        bool validMove = false;
        while (!validMove) {
            cout << "x와 y 이동 값을 입력하십시오 (-1, 0, 1 중 하나): ";
            cin >> x >> y;
            if ((abs(x) <= 1 && abs(y) <= 1) && (abs(x) + abs(y) <= 1)) 
            {
                player.xmove(x);
                player.ymove(y);
                validMove = true;
            }
            else {
                cout << "잘못된 이동입니다. 한 번에 한 칸만 이동할 수 있습니다.\n";
            }
        }
    }
    else if (choice == 2) 
    {
        player.attack(opponent);
    }
    else {
        cout << "잘못된 선택입니다. 턴을 건너뜁니다.\n";
    }
}

int main(void) 
{
    person player1(0, 0); // 플레이어 1 생성
    person player2(1, 1); // 플레이어 2 생성

    while (player1.getHp() > 0 && player2.getHp() > 0) {
        player1.displayStatus();
        player2.displayStatus();

        playerTurn(player1, player2); // 플레이어 1 차례

        if (player2.getHp() <= 0) break; // 플레이어 2의 체력이 0 이하이면 게임 종료

        playerTurn(player2, player1); // 플레이어 2 차례
    }

    if (player1.getHp() > 0) {
        cout << "플레이어 1 승리!" << endl;
    }
    else {
        cout << "플레이어 2 승리!" << endl;
    }

    return 0;
}
