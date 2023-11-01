#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

int my_board[5][5];
int his_board[5][5];
int possible_bingo[5][5] = { {3, 2, 2, 2, 3}, {2, 3, 2, 3, 2}, {2, 2, 4, 2, 2}, {2, 3, 2, 3, 2}, {3, 2, 2, 2, 3} };

void initialize_board() // ���� 2�� �ʱ�ȭ
{
	srand(time(NULL));

	int my_visited[26] = { 0, };
	int his_visited[26] = { 0, };

	for (int i = 0; i < 25; i++)
	{
		int temp = (rand() % 25) + 1;
		if (my_visited[temp] == 0)
		{
			my_board[i / 5][i % 5] = temp;
			my_visited[temp] = 1;
		}
		else
			i--;
	}

	for (int i = 0; i < 25; i++)
	{
		int temp = (rand() % 25) + 1;
		if (his_visited[temp] == 0)
		{
			his_board[i / 5][i % 5] = temp;
			his_visited[temp] = 1;
		}
		else
			i--;
	}
}

void print_board() // ���� 2�� ���
{
	printf("       <my board>                    <his_board>\n");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (my_board[i][j] > 0 && my_board[i][j] < 10) printf("  %d  ", my_board[i][j]);
			else if (my_board[i][j] >= 10) printf(" %d  ", my_board[i][j]);
			else if (my_board[i][j] < 0 && my_board[i][j] > -10) printf(" (%d) ", -my_board[i][j]);
			else printf("(%d) ", -my_board[i][j]);
		}

		printf("  |  ");

		for (int j = 0; j < 5; j++)
		{
			if (his_board[i][j] > 0) printf("  -  ");
			else if (his_board[i][j] < 0 && his_board[i][j] > -10) printf(" (%d) ", -his_board[i][j]);
			else printf("(%d) ", -his_board[i][j]);
		}
		printf("\n");
	}

	printf(" ������ �� : %d                 ������ �� : %d\n\n", num_of_bingo(my_board), num_of_bingo(his_board));
}

int num_of_bingo(int board[5][5]) // ���� �� ������ ��ȯ
{
	int count = 0;

	for (int i = 0; i < 5; i++)
		if (board[i][0] < 0 && board[i][1] < 0 && board[i][2] < 0 && board[i][3] < 0 && board[i][4] < 0) // ���η� ���� ����
			count++;

	for (int i = 0; i < 5; i++)
		if (board[0][i] < 0 && board[1][i] < 0 && board[2][i] < 0 && board[3][i] < 0 && board[4][i] < 0) //	���η� ���� ����
			count++;

	if (board[0][0] < 0 && board[1][1] < 0 && board[2][2] < 0 && board[3][3] < 0 && board[4][4] < 0) count++; // �밢�� ����
	if (board[0][4] < 0 && board[1][3] < 0 && board[2][2] < 0 && board[3][1] < 0 && board[4][0] < 0) count++;

	return count;
}

int is_bingo(int board[5][5]) // ���� 5�� �̻����� Ȯ��
{
	if (num_of_bingo(board) >= 5) return 1;
	else return 0;
}

void do_game_with_stupid()
{
	int visited[26] = { 0, };
	int my_choice;
	int his_choice;
	int turn = 1;

	print_board();

	while (is_bingo(my_board) == 0 && is_bingo(his_board) == 0)
	{
		// ���� ����
		printf("#%d. ����� �����Դϴ�. �� ���� �����ұ��? >> ", turn++);
		scanf("%d", &my_choice);
		visited[my_choice] = 1;

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
			{
				if (my_board[i][j] == my_choice) my_board[i][j] *= -1;
				if (his_board[i][j] == my_choice) his_board[i][j] *= -1;
			}
		print_board();


		if (is_bingo(my_board) == 1 || is_bingo(his_board) == 1) break;

		Sleep(1000);

		// ��ǻ�Ͱ� ����
		while (1)
		{
			his_choice = (rand() % 25) + 1;
			if (visited[his_choice] == 0)
			{
				visited[his_choice] = 1;
				break;
			}
		}
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
			{
				if (my_board[i][j] == his_choice) my_board[i][j] *= -1;
				if (his_board[i][j] == his_choice) his_board[i][j] *= -1;
			}

		printf("#%d. ��ǻ���� �����Դϴ�. %d���� �����߽��ϴ�.\n", turn++, his_choice);
		print_board();
	}

	if (is_bingo(my_board) == 1 && is_bingo(his_board) == 0) printf("����� �̰���ϴ�!!!!!!!!!!!\n");
	else if (is_bingo(my_board) == 0 && is_bingo(his_board) == 1) printf("��ǻ�Ͱ� �̰���ϴ�!!!!!!!!!!!\n");
	else printf("�����ϴ�!!!!!!!!!!!\n");
}

int num_of_increase_bingo(int r, int c)
{
	int original = num_of_bingo(his_board);

	his_board[r][c] *= -1;
	int next = num_of_bingo(his_board);
	his_board[r][c] *= -1;

	return (next - original);
}

int count_selected(int r, int c)
{
	int count = 0;

	for (int k = 0; k < 5; k++) // ���ο� ���ؼ�
		if (his_board[r][k] < 0 && k != c) count++;

	for (int k = 0; k < 5; k++) // ���ο� ���ؼ�
		if (his_board[k][c] < 0 && k != r) count++;


	if (r == c) // ���� �� -> ������ �Ʒ��� ���� �밢���� ���ؼ� (\)
		for (int k = 0; k < 5; k++)
			if (his_board[k][k] < 0 && k != r) count++;

	if (c == 4 - r) // ������ �� -> ���� �Ʒ��� ���� �밢���� ���ؼ� (/)
		for (int k = 0; k < 5; k++)
			if (his_board[k][4 - k] < 0 && k != r) count++;

	return count;
}

void do_rule1(int rule1_arr[5][5]) // �������� �� �ö󰡴� ���� ������ ���� ���� ĭ�� ���ϴ� �Լ�
{
	int temp;
	int max = 0;
	int increase_bingo[5][5];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			if (his_board[i][j] > 0)
			{
				temp = num_of_increase_bingo(i, j);
				increase_bingo[i][j] = temp;
				if (temp > max) max = temp;
			}
		}

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (his_board[i][j] > 0 && increase_bingo[i][j] == max) rule1_arr[i][j] = 1;
}

void do_rule2(int rule1_arr[5][5], int rule2_arr[5][5]) // ���� �ٿ���, �̹� ���õ� ĭ�� ������ �ִ밡 �Ǵ� ĭ�� ���Ѵ�
{
	int max = 0;
	int num_of_selected[5][5] = { 0, };

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (rule1_arr[i][j] == 1) // rule1���� max���� ����鿡 ���ؼ�
			{
				int count = count_selected(i, j);

				if (max < count) max = count;
				num_of_selected[i][j] = count;
			}

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (rule1_arr[i][j] == 1 && num_of_selected[i][j] == max) rule2_arr[i][j] = 1;
}

void do_rule3(int rule2_arr[5][5], int rule3_arr[5][5]) // ������ ���� ���� ���� ���� ĭ ���ϱ�
{
	int max = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (rule2_arr[i][j] == 1)
				if (possible_bingo[i][j] > max) max = possible_bingo[i][j];

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (rule2_arr[i][j] == 1 && possible_bingo[i][j] == max) rule3_arr[i][j] = 1;
}

void clear_rule_arrs(int rule1_arr[5][5], int rule2_arr[5][5], int rule3_arr[5][5])
{
	for (int i = 0; i < 25; i++)
	{
		rule1_arr[i / 5][i % 5] = 0;
		rule2_arr[i / 5][i % 5] = 0;
		rule3_arr[i / 5][i % 5] = 0;
	}
}

void do_game_with_smart()
{
	int visited[26] = { 0, };
	int my_choice;
	int his_choice;
	int turn = 1;

	int rule1_arr[5][5] = { 0, };
	int rule2_arr[5][5] = { 0, };
	int rule3_arr[5][5] = { 0, };

	print_board();

	while (is_bingo(my_board) == 0 && is_bingo(his_board) == 0)
	{
		// ���� ����
		printf("#%d. ����� �����Դϴ�. �� ���� �����ұ��? >> ", turn++);
		scanf("%d", &my_choice);
		visited[my_choice] = 1;

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
			{
				if (my_board[i][j] == my_choice) my_board[i][j] *= -1;
				if (his_board[i][j] == my_choice) his_board[i][j] *= -1;
			}
		print_board();


		if (is_bingo(my_board) == 1 || is_bingo(his_board) == 1) break;

		Sleep(1000);

		do_rule1(rule1_arr);
		do_rule2(rule1_arr, rule2_arr);
		do_rule3(rule2_arr, rule3_arr);

		for (int i = 0; i < 25; i++)
			if (rule3_arr[i / 5][i % 5] == 1)
			{
				his_choice = his_board[i / 5][i % 5];
				break;
			}

		visited[his_choice] = 1;

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
			{
				if (my_board[i][j] == his_choice) my_board[i][j] *= -1;
				if (his_board[i][j] == his_choice) his_board[i][j] *= -1;
			}

		printf("#%d. ��ǻ���� �����Դϴ�. %d���� �����߽��ϴ�.\n", turn++, his_choice);
		print_board();

		clear_rule_arrs(rule1_arr, rule2_arr, rule3_arr);
	}

	if (is_bingo(my_board) == 1 && is_bingo(his_board) == 0) printf("����� �̰���ϴ�!!!!!!!!!!!\n");
	else if (is_bingo(my_board) == 0 && is_bingo(his_board) == 1) printf("��ǻ�Ͱ� �̰���ϴ�!!!!!!!!!!!\n");
	else printf("�����ϴ�!!!!!!!!!!!\n");
}

int main(void)
{
	initialize_board();

	int op;
	printf("����� ��ǻ�͸� �����ϼ���(�ٺ� : 1 �ȶ��� : 2) >> ");
	scanf("%d", &op);
	printf("\n\n");

	if (op == 1) do_game_with_stupid();
	else if (op == 2) do_game_with_smart();

	return 0;
}