#include <stdio.h>
#include <time.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

void print_eval_time()
{
    int whole_sec = time(NULL);
    whole_sec += 9 * 60 * 60; // �츮���� �ð����� ���(+ 9�ð�)

    int year = 1970;
    int month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int day, hour, minute, second;

    // �� ���
    while (1)
    {
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) // ������ ��
        {
            if (whole_sec >= 366 * 24 * 60 * 60) whole_sec -= 366 * 24 * 60 * 60;
            else break;
        }
        else
        {
            if (whole_sec >= 365 * 24 * 60 * 60) whole_sec -= 365 * 24 * 60 * 60;
            else break;
        }
        year++;
    }

    // �� ���
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) month[2] = 29; // �����̸� 2���� 29�Ϸ� �ٲ�

    int index = 1;
    while (whole_sec >= month[index] * 24 * 60 * 60)
    {
        whole_sec -= month[index] * 24 * 60 * 60;
        index++;
    }

    // ��, �ð�, ��, ��
    day = whole_sec / (24 * 60 * 60) + 1;
    whole_sec %= 24 * 60 * 60;

    hour = whole_sec / (60 * 60);
    whole_sec %= 60 * 60;

    minute = whole_sec / 60;
    whole_sec %= 60;

    second = whole_sec;

    printf("���� �ð��� %d�� %d�� %d�� %d�� %d�� %d�� �Դϴ�.\n", year, index, day, hour, minute, second);
}

int main(void)
{
    for (;;)
    {
        print_eval_time();
        Sleep(1000); // 1�� ���
    }
}