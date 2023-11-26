#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct city
{
    int owner; // 0: �������, 1: player1, 2: player2, 3: START
    int place;
    char name[20];
} City;

typedef struct player
{
    int money;
    int place;
    int num;
} Player;

// �ֻ����� ������ �÷��̾ �̵���Ŵ
int roleDice(Player *player)
{
    int dice = rand() % 6 + 1;
    if (player->place + dice > 9)
        player->place += -9 + dice;
    else
        player->place += dice;

    return dice;
}

// ���ÿ� ������ �÷��̾ ������ ���¿� ���� �ൿ
// owner = 0 && money >= 300 -> ���ø� ���
// ������ �ִµ� �ڽ��� �ƴ� -> money -= 600
void Action(Player *cur_player, Player *other_player, City *city, int dice)
{
    printf("player %d�� �ֻ��� : %d\n", cur_player->num, dice);
    printf("%s ", city->name);
    if (city->owner == 0)
        printf("(���� ����)\n");
    else if (city->owner == 1 || city->owner == 2)
        printf("(%d)\n", city->owner);

    switch (city->owner)
    {
    case 0: // ���� ����
        if (cur_player->money >= 300)
        {
            cur_player->money -= 300;
            city->owner = cur_player->num;
            printf("player %d�� %s ����\n", cur_player->num, city->name);
            printf("player %d�� �ܰ� %d\n", cur_player->num, cur_player->money);
        }
        else
        {
            printf("%s�� ������ �� ����", city->name);
            printf("player %d�� �ܰ� %d\n", cur_player->num, cur_player->money);
        }
        break;
    case 3: // start ����
        printf("player %d�� �ܰ� %d\n", cur_player->num, cur_player->money);
        break;
    default: // ���� ����
        if (city->owner == other_player->num)
        {
            cur_player->money -= 600;
            other_player->money += 600;

            printf("player %d�� player %d�� ���ø� �湮, ����� ����\n", cur_player->num, other_player->num);
            if (cur_player->money >= 0)
                printf("player %d�� �ܰ� %d\n", cur_player->num, cur_player->money);
            else
                printf("player %d�� �ܰ� 0\n", cur_player->num);
        }
        else
        {
            printf("player %d�� �ڽ��� ���� �湮\n", cur_player->num);
            printf("player %d�� �ܰ� %d\n", cur_player->num, cur_player->money);
        }
        break;
    }
    printf("\n");
}

void playTurn(City cities[10], Player *player1, Player *player2, int *turn)
{
    int dice;
    printf("<turn %d>\n", *turn);

    dice = roleDice(player1);
    Action(player1, player2, &cities[player1->place], dice);
    if (player1->money < 0)
        return;

    dice = roleDice(player2);
    Action(player2, player1, &cities[player2->place], dice);

    (*turn)++;
}

int isEnd(int turn, Player player1, Player player2)
{
    if (turn > 30 || player1.money < 0 || player2.money < 0)
        return 1;
    else
        return 0;
}

void printBoard(City cities[10], int turn)
{
    // 6 ~ 10 ��° ���� ���
    for (int i = 5; i <= 9; i++)
        printf("--------------------  ");
    printf("\n");

    for (int i = 5; i <= 9; i++)
        printf("|                  |  ");
    printf("\n");

    for (int i = 5; i <= 9; i++)
    {
        char str[21] = "|                  |";
        int start = (20 - strlen(cities[i].name)) / 2;

        for (int k = 0; cities[i].name[k] != '\0'; k++)
            str[start + k] = cities[i].name[k];

        printf("%s  ", str);
    }
    printf("\n");

    for (int i = 5; i <= 9; i++)
    {
        if (cities[i].owner == 1)
            printf("|        (1)       |  ");
        else if (cities[i].owner == 2)
            printf("|        (2)       |  ");
        else
            printf("|                  |  ");
    }
    printf("\n");

    for (int i = 5; i <= 9; i++)
        printf("|                  |  ");
    printf("\n");

    for (int i = 5; i <= 9; i++)
        printf("--------------------  ");
    printf("\n");

    for (int i = 0; i < 51; i++)
        printf(" ");
    printf("----->\n");
    printf("\n\n");
    for (int i = 0; i < 51; i++)
        printf(" ");
    printf("<-----\n");

    // 1 ~ 5 ��° ���� ���
    for (int i = 4; i >= 0; i--)
        printf("--------------------  ");
    printf("\n");

    for (int i = 4; i >= 0; i--)
        printf("|                  |  ");
    printf("\n");

    for (int i = 4; i >= 0; i--)
    {
        char str[21] = "|                  |";
        int start = (20 - strlen(cities[i].name)) / 2 + 1;

        for (int k = 0; cities[i].name[k] != '\0'; k++)
            str[start + k] = cities[i].name[k];

        printf("%s  ", str);
    }
    printf("\n");

    for (int i = 4; i >= 0; i--)
    {
        if (cities[i].owner == 1)
            printf("|        (1)       |  ");
        else if (cities[i].owner == 2)
            printf("|        (2)       |  ");
        else
            printf("|                  |  ");
    }
    printf("\n");

    for (int i = 4; i >= 0; i--)
        printf("|                  |  ");
    printf("\n");

    for (int i = 4; i >= 0; i--)
        printf("--------------------  ");
    printf("\n\n");
}

int main(void)
{
    srand(time(NULL));
    City cities[10] = {{3, 0, "START"}, {0, 1, "Seoul"}, {0, 2, "Tokyo"}, {0, 3, "Sydney"}, {0, 4, "LA"}, {0, 5, "Cairo"}, {0, 6, "Phuket"}, {0, 7, "New delhi"}, {0, 8, "Hanoi"}, {0, 9, "Paris"}};
    Player player1 = {5000, 0, 1}, player2 = {5000, 0, 2};

    int turn = 1;
    while (1)
    {
        playTurn(cities, &player1, &player2, &turn);
        printBoard(cities, turn);
        if (isEnd(turn, player1, player2) == 1)
            break;

        Sleep(1000);
    }

    printf("������ ����Ǿ����ϴ�. ");
    if (player1.money > player2.money)
        printf("player 1 �¸�!\n");
    else if (player1.money < player2.money)
        printf("player 2 �¸�!\n");
    else
        printf("���º�!\n");

    return 0;
}