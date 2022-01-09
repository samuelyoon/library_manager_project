#include <stdio.h>
#include <Windows.h>
#include <string.h>

// ���� ����ü
typedef struct account{
	char ID[12];
	char PW[12];
	char name[12];
} ACCOUNT;

// å ����ü 
typedef struct book{
	char name[32];
	char author[32];
	char publisher[32];
	char date[32]; 
	int loan;
} BOOK;

// �Լ��� �ʿ��� �������� 
int key, i, x = 9;

// Ŀ�� ���� �Լ�
void gotoxy(int x, int y)
{
	COORD pos ={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// UI�� �������� �׸��� �Լ� 
void paint_frame(void)
{
	int y = 2;
	
	system("cls");
	gotoxy(10, 0);
	printf("��");
	for(i=0; i<50; i++){
		printf("��");
	}
	printf("��");
	
	for(i=0; i<20; i++){
		gotoxy(10, y-1);
		printf("��");
		y++;
	}
	y = 2;
	for(i=0; i<20; i++){
		gotoxy(61, y-1);
		printf("��");
		y++;
	}
	gotoxy(10, 21);
	printf("��");
	gotoxy(11, 21);
	for(i=0; i<50; i++){
		printf("��");
	}
	printf("��");
	gotoxy(11, 4);
	for(i=0; i<50; i++){
		printf("��");
	}
}

// ù��° ȭ�� 
void first_window(void)
{	
	paint_frame();
	
	gotoxy(33, 2);
	printf("�α���");
	
	gotoxy(25, 8); 
	printf("    ȸ�� �α���\n");
	gotoxy(25, 11);
	printf("    ������ �α���\n");
	gotoxy(25, 14);
	printf("    ȸ������\n");
	
	x = 25;
	int y = 8;
	gotoxy(x, y);
	printf("��");
	gotoxy(x, y);
	while(1){
		fflush(stdin);
		key = getch();
		
		if(key == 13){
			if(y == 8){
				log_in_window();
			}
			else if(y == 11){
				admin_log_window();
			} 
			else if(y == 14){
				sign_up_window();
			} 
		}
		else if(key == 72){
			if(y != 8){
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, y-=3);
				printf("��");
			}
		}
		else if(key == 80){
			if(y != 14){
				gotoxy(x, y);
				printf("  ");
				gotoxy(x, y+=3);
				printf("��");
			}
		}
	}
}

// ȸ������ �ܼ� �Լ� 
void sign_up_window(void)
{
	ACCOUNT sign;
	
	paint_frame();
	gotoxy(30, 2);
	printf("ȸ������");
	
	gotoxy(13, 8); 
	printf("    ���̵�(12�ڸ� �̳�): ");
	scanf("%s", sign.ID);
	gotoxy(13, 11);
	printf("  ��й�ȣ(12�ڸ� �̳�): ");
	scanf("%s", sign.PW);
	gotoxy(13, 14);
	printf("                   �̸�: ");
	scanf("%s", sign.name);
	
	sign_up(&sign);
}

// ȸ������ ���� �Լ� 
void sign_up(ACCOUNT *sign)
{
	FILE *fp = fopen("account.txt", "a+");
	
	if(fp == NULL){
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.\n");
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "%s\n%s\n%s\n", sign->ID, &sign->PW, sign->name);
	fclose(fp);
	gotoxy(55, 22);
	printf("ȸ������ �Ϸ�\n");
	gotoxy(50, 19);
	printf("    Ȩ����");
	gotoxy(50, 19);
	printf("��");
	fflush(stdin);
	if(getch() == 13){
		first_window();
		}
}

// �α��� �ܼ� �Լ� 
void log_in_window(void)
{
	ACCOUNT user;
	
	paint_frame();
	gotoxy(30, 2);
	printf("ȸ�� �α���");
	
	gotoxy(20, 10); 
	printf("      ���̵�: ");
	scanf("%s", user.ID);
	gotoxy(20, 13);
	printf("    ��й�ȣ: ");
	scanf("%s", user.PW);
	
	log_in(&user);
}

// �α��� ���μ��� �Լ� 
void log_in(ACCOUNT *user)
{
	ACCOUNT member;
	FILE *fp = fopen("account.txt", "r");
	int find = 0;
	
	if(fp == NULL){
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.\n");
		return 1;
	}
	fseek(fp, 0, SEEK_SET);
	while(!feof(fp)){
		fscanf(fp, "%s %s\n", &member.ID, &member.PW);
		if(strcmp(user->ID, member.ID) == 0){
			if(strcmp(user->PW, member.PW) == 0){
				main_library();
				find = 1;
				break;
			}
		}
	}
	if(find == 0){
		gotoxy(55, 22);
		printf("ID Ȥ�� PW�� Ʋ�Ƚ��ϴ�. �ٽ� Ȯ�����ּ���.\n");
		gotoxy(50, 19);
		printf("    ����");
		gotoxy(50, 19);
		printf("��");
		fflush(stdin);
		if(getch() == 13){
			first_window();
		}
	}
	fclose(fp);
}

// �α��� �� ���� ȭ�� �ܼ� �Լ� 
void main_library(void)
{	
	paint_frame();
	gotoxy(30, 2);
	printf("Main ������");
	gotoxy(25, 8); 
	printf("    ���� �ȳ�\n");
	gotoxy(25, 11);
	printf("    ����Ʈ����\n");
	gotoxy(25, 14);
	printf("    �����˻�\n");
	
	x = 25;
	int y = 8;
	gotoxy(x, y);
	printf("��");
	gotoxy(x, y);
	while(1){
		fflush(stdin);
		key = getch();
		
		if(key == 13){
			if(y == 8){
				new_book();
			}
			else if(y == 11){
				best_seller();
			}
			else if(y == 14){
				book_search_window(0);
			}
		}
		else if(key == 72){
			if(y != 8){
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, y-=3);
				printf("��");
			}
		}
		else if(key == 80){
			if(y!= 14){
				gotoxy(x, y);
				printf("  ");
				gotoxy(x, y+=3);
				printf("��");
			}
		}
	}
}

// ���� ��� �Լ� 
void new_book(void)
{
	BOOK newb;
	FILE *fp = fopen("book.txt", "r");
	
	if(fp == NULL){
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.");
		return 0; 
	}
	fseek(fp, -54, SEEK_END);
	fscanf(fp, "%s\n%s\n%s\n%s\n%d\n", &newb.name, &newb.author, &newb.publisher, &newb.date, &newb.loan);
	fclose(fp);
	print_search(&newb, 0);
}

// ����Ʈ���� ��� �Լ�
void best_seller(void)
{
	BOOK best;
	FILE *fp = fopen("book.txt", "r");
	
	if(fp == NULL){
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.");
		return 0; 
	}
	fseek(fp, 0, SEEK_SET);
	fscanf(fp, "%s\n%s\n%s\n%s\n%d\n", &best.name, &best.author, &best.publisher, &best.date, &best.loan);
	fclose(fp);
	print_search(&best, 0);
 } 
// å �˻� �ܼ� �Լ� 
void book_search_window(int m)
{
	BOOK books;
	int y = 2;
	int n = m;
	
	paint_frame();
	gotoxy(30, 2);
	printf("å �˻�");
	gotoxy(20, 8);
	printf("    å �̸�: ");
	scanf("%s", &books.name);
	
	book_search(&books, n);
}

// å �˻� ���μ��� �Լ� 
void book_search(BOOK *books, int n)
{
	BOOK search;
	FILE *fp = fopen("book.txt", "r");
	int find = 0;
	int m = n;
	
	if(fp == NULL){
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.\n");
		return 1;
	}
	fseek(fp, 0, SEEK_SET);
	while(!feof(fp)){
		fscanf(fp, "%s\n%s\n%s\n%s\n%d\n", &search.name, &search.author, &search.publisher, &search.date, &search.loan);
		if(strstr(search.name, books->name) != NULL){
			print_search(&search, m);
			find = 1;
			break;
		}
	}
	if(find == 0){
		gotoxy(55, 22);
		printf("��ϵ��� ���� å�Դϴ�. �ٽ� Ȯ�����ּ���.\n");
		gotoxy(50, 19);
		printf("    ����");
		gotoxy(50, 19);
		printf("��");
		fflush(stdin);
		if(getch() == 13){
			if(m == 0){
				first_window();
			}
			else if(m == 1){
				admin_window();
			}
		}
	}
	fclose(fp);
}

// �˻���� ����Ʈ �Լ� 
void print_search(BOOK *books, int m)
{
	BOOK loans = *books;
	paint_frame();
	
	gotoxy(30, 2);
	printf("ã�� ���");
	gotoxy(20, 5);
	printf("    å �̸�: %s", books->name);
	gotoxy(20, 7);
	printf("       ����: %s", books->author);
	gotoxy(20, 9);
	printf("     ���ǻ�: %s", books->publisher);
	gotoxy(20, 11);
	printf("     ������: %s", books->date);
	gotoxy(20, 13);
	printf("       ���: %d", books->loan);
	gotoxy(25, 15);
	printf("    �����ϱ�");
	gotoxy(25, 17);
	printf("    �ݳ��ϱ�"); 
	gotoxy(25, 19);
	printf("    ����");
	
	x = 25;
	int y = 15;
	gotoxy(x, y);
	printf("��");
	gotoxy(x, y);
	while(1){
		fflush(stdin);
		key = getch();
		
		if(key == 13){
			if(y == 15){
				loan_book(&loans);
			}
			else if(y == 17){
				return_book(&loans);
			 } 
			else if(y == 19){
				if(m == 0){
					main_library();
				}
				else if(m == 1){
					admin_window();
				}
			}
		}
		else if(key == 72){
			if(y != 15){
				gotoxy(x, y);
				printf("  ");
				gotoxy(x, y-=2);
				printf("��");
			}
		}
		else if(key == 80){
			if(y!= 19){
				gotoxy(x, y);
				printf("  ");
				gotoxy(x, y+=2);
				printf("��");
			}
		}
	}
}

// ���� �Լ�
void loan_book(BOOK *books)
{
	BOOK read;
	FILE *fp = fopen("book.txt", "r");
	FILE *wfp = fopen("book1.txt", "w");
	
	paint_frame();
	gotoxy(30, 2);
	printf("å �߰�");
	gotoxy(20, 8);
	printf("   å �̸�: %s", books->name);
	gotoxy(20, 10);
	printf("      ����: %s", books->author);
	gotoxy(20, 12);
	printf("    ���ǻ�: %s", books->publisher);
	gotoxy(20, 14);
	printf("    ������: %s", books->date);
	gotoxy(20, 16);
	printf("      ���: %d", books->loan);
	
	if(books->loan == 0){
		gotoxy(55, 22);
		printf("��� ���� å�Դϴ�. �ٸ� å�� �������ּ���.\n");
		gotoxy(50, 19);
		printf("    ����");
		gotoxy(50, 19);
		printf("��");
		fflush(stdin);
		if(getch() == 13){
			main_library();
		}
	}
	
	if(fp == NULL || wfp == NULL){
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.\n");
		return 1;
	}
	
	fseek(fp, 0, SEEK_SET);
	fseek(wfp, 0, SEEK_SET);
	while(!feof(fp)){
		fscanf(fp, "%s\n%s\n%s\n%s\n%d\n", &read.name, &read.author, &read.publisher, &read.date, &read.loan);
		if(strcmp(read.name, books->name) == 0){
			read.loan = 0;
		}
		fprintf(wfp, "%s\n%s\n%s\n%s\n%d\n", read.name, read.author, read.publisher, read.date, read.loan);
	}
	fclose(fp);
	fclose(wfp);
	
	FILE *fp2 = fopen("book.txt", "w");
	FILE *wfp2 = fopen("book1.txt", "r");
	
	if(fp2 == NULL || wfp2 == NULL)
	{
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.\n");
		return 1;
	}
	
	while(!feof(wfp2)){
		fscanf(wfp2, "%s\n%s\n%s\n%s\n%d\n", &read.name, &read.author, &read.publisher, &read.date, &read.loan);
		fprintf(fp2, "%s\n%s\n%s\n%s\n%d\n", read.name, read.author, read.publisher, read.date, read.loan);
	}
	fclose(fp2);
	fclose(wfp2);
	
	gotoxy(55, 22);
	printf("����Ǿ����ϴ�.\n");
	gotoxy(50, 19);
	printf("    Ȩ����");
	gotoxy(50, 19);
	printf("��");
	fflush(stdin);
	if(getch() == 13){
		first_window();
		}
}

// �ݳ� �Լ�
void return_book(BOOK *books)
{
	BOOK read;
	FILE *fp = fopen("book.txt", "r");
	FILE *wfp = fopen("book1.txt", "w");
	
	paint_frame();
	gotoxy(30, 2);
	printf("å �߰�");
	gotoxy(20, 8);
	printf("   å �̸�: %s", books->name);
	gotoxy(20, 10);
	printf("      ����: %s", books->author);
	gotoxy(20, 12);
	printf("    ���ǻ�: %s", books->publisher);
	gotoxy(20, 14);
	printf("    ������: %s", books->date);
	gotoxy(20, 16);
	printf("      ���: %d", books->loan);
	
	if(books->loan == 1){
		gotoxy(55, 22);
		printf("������� ���� å�Դϴ�. �ٸ� å�� �������ּ���.\n");
		gotoxy(50, 19);
		printf("    ����");
		gotoxy(50, 19);
		printf("��");
		fflush(stdin);
		if(getch() == 13){
			main_library();
		}
	}
	
	if(fp == NULL || wfp == NULL){
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.\n");
		return 1;
	}
	
	fseek(fp, 0, SEEK_SET);
	fseek(wfp, 0, SEEK_SET);
	while(!feof(fp)){
		fscanf(fp, "%s\n%s\n%s\n%s\n%d\n", &read.name, &read.author, &read.publisher, &read.date, &read.loan);
		if(strcmp(read.name, books->name) == 0){
			read.loan = 1;
		}
		fprintf(wfp, "%s\n%s\n%s\n%s\n%d\n", read.name, read.author, read.publisher, read.date, read.loan);
	}
	fclose(fp);
	fclose(wfp);
	
	FILE *fp2 = fopen("book.txt", "w");
	FILE *wfp2 = fopen("book1.txt", "r");
	
	if(fp2 == NULL || wfp2 == NULL)
	{
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.\n");
		return 1;
	}
	
	while(!feof(wfp2)){
		fscanf(wfp2, "%s\n%s\n%s\n%s\n%d\n", &read.name, &read.author, &read.publisher, &read.date, &read.loan);
		fprintf(fp2, "%s\n%s\n%s\n%s\n%d\n", read.name, read.author, read.publisher, read.date, read.loan);
	}
	fclose(fp2);
	fclose(wfp2);
	
	gotoxy(55, 22);
	printf("�ݳ��Ǿ����ϴ�.\n");
	gotoxy(50, 19);
	printf("    ����");
	gotoxy(50, 19);
	printf("��");
	fflush(stdin);
	if(getch() == 13){
		main_library();
		}
}

// ������ ���� �α��� �ܼ� �Լ� 
void admin_log_window(void)
{
	ACCOUNT admin;
	
	paint_frame();
	gotoxy(30, 2);
	printf("������ �α���");
	
	gotoxy(20, 10); 
	printf("    ���̵�: ");
	scanf("%s", admin.ID);
	gotoxy(18, 13);
	printf("    ��й�ȣ: ");
	scanf("%s", admin.PW);
	
	admin_log_in(&admin);
}

// ������ ���� �α��� ���μ��� �Լ� 
void admin_log_in(ACCOUNT *admin)
{
	ACCOUNT ad_log;
	FILE *fp = fopen("admin.txt", "r");
	int find = 0;
	
	if(fp == NULL){
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.\n");
		return 1;
	}
	fseek(fp, 0, SEEK_SET);
	while(!feof(fp)){
		fscanf(fp, "%s\n%s\n", &ad_log.ID, &ad_log.PW);
		if(strcmp(admin->ID, ad_log.ID) == 0){
			if(strcmp(admin->PW, ad_log.PW) == 0){
				admin_window();
				find = 1;
				break;
			}
		}
	}
	if(find == 0){
		gotoxy(55, 22);
		printf("ID Ȥ�� PW�� Ʋ�Ƚ��ϴ�. �ٽ� Ȯ�����ּ���.\n");
		gotoxy(50, 19);
		printf("    ����");
		gotoxy(50, 19);
		printf("��");
		fflush(stdin);
		if(getch() == 13){
			first_window();
		}
	}
	fclose(fp);
}

// ������ ���� �ܼ� �Լ� 
void admin_window(void)
{	
	int y = 2;
	
	paint_frame();
	gotoxy(30, 2);
	printf("������ Main");
	
	gotoxy(25, 8); 
	printf("    ���� �߰�\n");
	gotoxy(25, 11);
	printf("    ���� ����\n");
	gotoxy(25, 14);
	printf("    ���� �˻�\n");
	
	x = 25;
	y = 8;
	gotoxy(x, y);
	printf("��");
	gotoxy(x, y);
	while(1){
		fflush(stdin);
		key = getch();
		
		if(key == 13){
			if(y == 8){
				add_book_window();
			}
			else if(y == 14){
				book_search_window(1);
			}
		}
		else if(key == 72){
			if(y != 8){
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, y-=3);
				printf("��");
			}
		}
		else if(key == 80){
			if(y!= 14){
				gotoxy(x, y);
				printf("  ");
				gotoxy(x, y+=3);
				printf("��");
			}
		}
	}
}

// ���� �߰� �ܼ� �Լ� 
void add_book_window(void)
{
	BOOK books;
	
	paint_frame();
	gotoxy(30, 2);
	printf("å �߰�");
	gotoxy(20, 8);
	printf("   å �̸�: ");
	scanf("%s", books.name);
	gotoxy(20, 10);
	printf("      ����: ");
	scanf("%s", books.author);
	gotoxy(20, 12);
	printf("    ���ǻ�: ");
	scanf("%s", books.publisher);
	gotoxy(20, 14);
	printf("    ������: ");
	scanf("%s", books.date);
	gotoxy(20, 16);
	printf("      ���: ");
	scanf("%d", &books.loan);
	add_book(&books);
}

// ���� �߰� ���μ��� �Լ� 
void add_book(BOOK *books)
{
	FILE *fp = fopen("book.txt", "a+");
	
	if(fp == NULL){
		printf("������ �� �� �����ϴ�. ���α׷��� �����մϴ�.\n");
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "%s\n%s\n%s\n%s\n%d\n", books->name, books->author, books->publisher, books->date, books->loan);
	gotoxy(55, 22);
	printf("���� �߰� �Ϸ�\n");
	gotoxy(50, 19);
	printf("    ����");
	gotoxy(50, 19);
	printf("��");
	fflush(stdin);
	if(getch() == 13){
		admin_window();
		}
	fclose(fp);
}


int main(void)
{
	FILE *fp;
	
	first_window();
	
	return 0;
}
