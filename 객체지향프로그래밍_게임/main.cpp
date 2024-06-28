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
        : xpos(xpos), ypos(ypos), hp(hp), mp(mp), damage(damage), armor(armor) {} // ������

    void xmove(int value) { // x �̵�
        xpos += value;
    }

    void ymove(int value) { // y �̵�
        ypos += value;
    }

    double distance(const person& other) const { // �� ��ü �� �Ÿ� ���
        return sqrt(pow(xpos - other.xpos, 2) + pow(ypos - other.ypos, 2));
    }

    void attack(person& target) { // ���� �Լ�
        if (distance(target) <= 1) 
        {
            int effective_damage = damage - target.armor;
            if (effective_damage < 0) effective_damage = 0; // ������ ���ݷº��� Ŭ ��� �ּ� �������� 0
            target.hp -= effective_damage;
            cout << "���� ����! ������ ü��: " << target.hp << endl;
        }
        else 
        {
            cout << "������ �����Ÿ� �ۿ� �ֽ��ϴ�. �� ������ �̵��Ͻʽÿ�." << endl;
        }
    }

    void displayStatus() const { // ���� ǥ�� �Լ�
        cout << "��ġ: (" << xpos << ", " << ypos << "), ü��: " << hp << ", ����: " << mp << endl;
    }

    // ü�� Ȯ���� ���� getter
    int getHp() const {
        return hp;
    }
};

void playerTurn(person& player, person& opponent) {
    int choice;
    cout << "�÷��̾��� ���Դϴ�. �ൿ�� �����Ͻʽÿ�:\n";
    cout << "1. �̵�\n";
    cout << "2. ����\n";
    cin >> choice;

    if (choice == 1) {
        int x, y;
        bool validMove = false;
        while (!validMove) {
            cout << "x�� y �̵� ���� �Է��Ͻʽÿ� (-1, 0, 1 �� �ϳ�): ";
            cin >> x >> y;
            if ((abs(x) <= 1 && abs(y) <= 1) && (abs(x) + abs(y) <= 1)) 
            {
                player.xmove(x);
                player.ymove(y);
                validMove = true;
            }
            else {
                cout << "�߸��� �̵��Դϴ�. �� ���� �� ĭ�� �̵��� �� �ֽ��ϴ�.\n";
            }
        }
    }
    else if (choice == 2) 
    {
        player.attack(opponent);
    }
    else {
        cout << "�߸��� �����Դϴ�. ���� �ǳʶݴϴ�.\n";
    }
}

int main(void) 
{
    person player1(0, 0); // �÷��̾� 1 ����
    person player2(1, 1); // �÷��̾� 2 ����

    while (player1.getHp() > 0 && player2.getHp() > 0) {
        player1.displayStatus();
        player2.displayStatus();

        playerTurn(player1, player2); // �÷��̾� 1 ����

        if (player2.getHp() <= 0) break; // �÷��̾� 2�� ü���� 0 �����̸� ���� ����

        playerTurn(player2, player1); // �÷��̾� 2 ����
    }

    if (player1.getHp() > 0) {
        cout << "�÷��̾� 1 �¸�!" << endl;
    }
    else {
        cout << "�÷��̾� 2 �¸�!" << endl;
    }

    return 0;
}
