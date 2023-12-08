#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Word
{
    int length;
    int gather;
    char spell[100];
    char meaning[100];
} Word;

int compareByLength(const void *a, const void *b)
{
    return (((Word *)b)->length - ((Word *)a)->length);
}

int compareByGather(const void *a, const void *b)
{
    return (((Word *)b)->gather - ((Word *)a)->gather);
}

Word Dict[60000];
int dict_len = 0;

void storeWords()
{
    FILE *fp;
    char temp_string[200];
    char t_spell[100];
    char t_meaning[100];

    fp = fopen("dict_test.TXT", "r");
    if (fp == NULL)
    {
        printf("FILE OPEN ERROR\n");
        exit(1);
    }

    for (int i = 0; fgets(temp_string, 200, fp) != NULL; i++)
    {
        int j = 0;
        int k = 0;

        for (; temp_string[j] != ':'; j++) // ���ڿ� �Ľ�
            t_spell[j] = temp_string[j];
        t_spell[j - 1] = '\0';
        for (; temp_string[j] != '\n'; j++,k++)
            t_meaning[k] = temp_string[j];
        t_meaning[k] = '\0';
     
        Dict[i].length = strlen(t_spell); // ����
        strcpy(Dict[i].spell, t_spell); // ���� �ܾ�
        strcpy(Dict[i].meaning, t_meaning); // �ѱ� ��

        Dict[i].gather = 0; // ���� ����
        for (int k = 0; t_spell[k] != '\0'; k++)
        {
            char ch = t_spell[k];
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
                Dict[i].gather++;
        }

        dict_len++;
    }

    if (fgets(temp_string, 100, fp) == NULL)
        printf("ALL STORED\n");
    else
        printf("NOT ALL STORED\n");

    fclose(fp);

    return;
}
void searchWords()
{
    char t_spell[100];
    while (1)
    {
        printf("�ܾ�?(���͸� �Է��ϸ� ����) ");
        fgets(t_spell, 100, stdin);
        if (strcmp(t_spell, "\n") == 0) break; // ���͸� �Է��ϸ� exit

        t_spell[strlen(t_spell) - 1] = '\0'; // ���� ����
        for (int i = 0; i <= dict_len; i++) // �´� �ܾ� ã��
        {
            if (i == dict_len)
                printf("�ܾ ã�� �� �����ϴ�.\n");
            else if (strcmp(Dict[i].spell, t_spell) == 0)
            {
                printf("%s %s\n", Dict[i].spell, Dict[i].meaning);
                break;
            }
        }

    }
    
    printf("\n");
    return ;
}
void concludingRemarks()
{
    int idx = (rand() % dict_len);
    int score = 0;
    char last_alpha, first_alpha;
    char first_spell[100];
    char second_spell[100];
    char visited[10][100];
    int visit_index = 0;
    char isVisit = 0;
    char isStored = 0;
    int life = 3;
    strcpy(first_spell, Dict[idx].spell);
    printf("��ǻ�� : %s\n", first_spell);

    for (int i = 0; i < 10; i++)
    {
        last_alpha = first_spell[strlen(first_spell) - 1];
        printf("�����ձ� �ܾ� : ");
        fgets(second_spell, 100, stdin);
        second_spell[strlen(second_spell) - 1] = '\0';

        first_alpha = second_spell[0];

        for (int j = 0; j < dict_len; j++)
        {
            if (strcmp(Dict[j].spell, second_spell) == 0)
            {
                isStored = 1;
                break;
            }
        }

        for (int j = 0; j <= visit_index; j++)
        {
            if (strcmp(second_spell, visited[j]) == 0)
            {
                printf("�̹� ���� �ܾ��Դϴ�.\n");
                life--;
                isVisit = 1;
                break;
            }               
        }


        if (strlen(second_spell) > 10 || strlen(second_spell) < 3)
        {
            printf("�ܾ��� ���̰� 3�̻� 10 ���ϰ� �ƴմϴ�.\n");
            life--;
        }
        else if (isStored == 0)
        {
            printf("�ܾ������ ���� �ܾ��Դϴ�\n");
            life--;
        }           
        else if (last_alpha != first_alpha)
        {
            printf("�� ���ڿ� ù ���ڰ� �ٸ��ϴ�.\n");
            life--;
        }
        else if (last_alpha == first_alpha && isVisit == 0 && isStored == 1)
        {
            score++;
            strcpy(visited[visit_index++], second_spell);
            strcpy(first_spell, second_spell);
        } 
        
        if (life == 0)
        {
            printf("��� ��ȸ�� �����߽��ϴ�.\n");
            break;
        }

        printf("���� ���� %d��\n\n", score); 

        isVisit = 0;
        isStored = 0;
    }

    printf("�����ձ� ����. �� ������ %d��\n\n", score);

    return ;
}
void wordAnalyze()
{

    qsort(Dict, dict_len, sizeof(Dict[0]), compareByLength);
    for (int i = 0; i < 10; i++)
        printf("���� �� : %d, %s %s\n", Dict[i].length, Dict[i].spell, Dict[i].meaning);
    printf("\n");

    qsort(Dict, dict_len, sizeof(Dict[0]), compareByGather);
    for (int i = 0; i < 10; i++)
        printf("���� ����: %d, %s %s\n", Dict[i].gather, Dict[i].spell, Dict[i].meaning);
    printf("\n");
    return ;
}
void executeProgram()
{
    srand(time(NULL));
    storeWords();

    int op = 0;
    while (1)
    {
        printf("1 : �ܾ� ã��, 2 : ���� �ձ�, 3 : �ܾ� �м�, 4 : ����\n>> ");
        scanf("%d", &op);
        getchar();
        
        if (op == 1)
        {
            searchWords();
        }
        else if (op == 2)
        {
            concludingRemarks();
        }
        else if (op == 3)
        {
            wordAnalyze();
        }
        else if (op == 4)
        {
            break;
        }
        else
            printf("�߸��� �Է�\n");
    }

    printf("���α׷� ����\n");
    return;
}
int main(void)
{
    executeProgram();

    return 0;
}