#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char name[100];
    char author[30];
    char publisher[30];
    int isBorrow;
} Book;

typedef struct
{
    char name[30];
    char phone_num[14];
} Member;

typedef struct
{
    Book *book;
    Member member;
    char borrow_date[10];
    char return_date[10];
    int isReturn;
} BorrowInfor;

void printBooks(Book book_array[100], int book_num)
{
    for (int i = 0; i < book_num; i++)
    {
        printf("- %s %s %s ", book_array[i].name, book_array[i].author, book_array[i].publisher);
        if (book_array[i].isBorrow == 0)
            printf("(����)\n");
        else if (book_array[i].isBorrow == 1)
            printf("(������)\n");
    }

    printf("\n");
}
void Borrow(Book *book, Member member, char borrow_date[10], BorrowInfor *borrow)
{
    book->isBorrow = 1;
    borrow->book = book;
    borrow->member = member;
    borrow->isReturn = 0;
    strcpy(borrow->borrow_date, borrow_date);
    strcpy(borrow->return_date, "0");
}
void Return(BorrowInfor *borrow, char return_date[10])
{
    strcpy(borrow->return_date, return_date);
    borrow->book->isBorrow = 0;
    borrow->isReturn = 1;
}
void printBorrows(BorrowInfor borrow_list[1000], int borrow_num)
{
    for (int i = borrow_num - 1; i >= 0; i--)
    {
        printf("- %s %s(%s) %s ", borrow_list[i].book->name, borrow_list[i].member.name, borrow_list[i].member.phone_num, borrow_list[i].borrow_date);
        if (strcmp(borrow_list[i].return_date, "0") == 0)
            printf("(������)\n");
        else
            printf("%s\n", borrow_list[i].return_date);
    }
    printf("\n");
}

int main(void)
{
    char t_book_name[100], t_mem_name[30]; // temp ������
    char t_borrow_date[10], t_return_date[10];
    Member temp_member;

    int op;
    int book_num = 5;
    int borrow_num = 0;
    int member_num = 5;

    Member mem_array[100] = {{"�Ǳ⿵", "010-9586-5112"}, {"ȫ�浿", "010-1234-5678"}, {"�̼���", "010-4444-5555"}, {"���󿡸�", "010-3333-8888"}, {"�����", "010-3434-3434"}};
    Book book_array[100] = {{"���̽����α׷���", "ȫ�浿", "A���ǻ�", 0}, {"���� C���α׷���", "�̱浿", "B���ǻ�", 0}, {"���ο� �ڷᱸ��", "���浿", "C���ǻ�", 0}, {"���� C++���α׷���", "��浿", "D���ǻ�", 0}, {"���� ��ǻ�ͱ���", "��浿", "E���ǻ�", 0}};
    BorrowInfor borrow_list[1000];

    while (1)
    {
        printf("1. å ��� ǥ���ϱ�\n");
        printf("2. ���� ����ϱ�\n");
        printf("3. �ݳ� �ϱ�\n");
        printf("4. ���� ��� ǥ���ϱ�\n");
        printf("5. ����\n");

        scanf("%d", &op);
        getchar();

        if (op == 5)
            return 0;

        switch (op)
        {
        case 1:
            printBooks(book_array, book_num);
            break;
        case 2:
            printf("ȸ�� �̸�: ");
            fgets(t_mem_name, 30, stdin);
            t_mem_name[strlen(t_mem_name) - 1] = '\0';

            printf("���� ������: ");
            fgets(t_book_name, 100, stdin);
            t_book_name[strlen(t_book_name) - 1] = '\0';

            printf("���� ��¥: ");
            fgets(t_borrow_date, 10, stdin);
            t_borrow_date[strlen(t_borrow_date) - 1] = '\0';

            for (int i = 0; i < member_num; i++)
                if (strcmp(mem_array[i].name, t_mem_name) == 0)
                    temp_member = mem_array[i];
            for (int i = 0; i < book_num; i++)
                if (strcmp(book_array[i].name, t_book_name) == 0)
                {
                    Borrow(&book_array[i], temp_member, t_borrow_date, &borrow_list[borrow_num++]);
                    break;
                }
            break;
        case 3:
            printf("�ݳ� ������: ");
            fgets(t_book_name, 100, stdin);
            t_book_name[strlen(t_book_name) - 1] = '\0';

            printf("�ݳ� ��¥: ");
            fgets(t_return_date, 10, stdin);
            t_return_date[strlen(t_return_date) - 1] = '\0';

            for (int i = 0; i < borrow_num; i++)
                if (strcmp(borrow_list[i].book->name, t_book_name) == 0 && borrow_list[i].isReturn == 0)
                {
                    Return(&borrow_list[i], t_return_date);
                    break;
                }
            break;
        case 4:
            printBorrows(borrow_list, borrow_num);
            break;
        default:
            break;
        }
    }
}
