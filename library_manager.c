#include <stdio.h>
#include <Windows.h>
#include <string.h>

// 계정 구조체
typedef struct account{
	char ID[12];
	char PW[12];
	char name[12];
} ACCOUNT;

// 책 구조체 
typedef struct book{
	char name[32];
	char author[32];
	char publisher[32];
	char date[32]; 
	int loan;
} BOOK;

// 함수에 필요한 전역변수 
int key, i, x = 9;

// 커서 제어 함수
void gotoxy(int x, int y)
{
	COORD pos ={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// UI의 프레임을 그리는 함수 
void paint_frame(void)
{
	int y = 2;
	
	system("cls");
	gotoxy(10, 0);
	printf("┌");
	for(i=0; i<50; i++){
		printf("─");
	}
	printf("┐");
	
	for(i=0; i<20; i++){
		gotoxy(10, y-1);
		printf("│");
		y++;
	}
	y = 2;
	for(i=0; i<20; i++){
		gotoxy(61, y-1);
		printf("│");
		y++;
	}
	gotoxy(10, 21);
	printf("└");
	gotoxy(11, 21);
	for(i=0; i<50; i++){
		printf("─");
	}
	printf("┘");
	gotoxy(11, 4);
	for(i=0; i<50; i++){
		printf("─");
	}
}

// 첫번째 화면 
void first_window(void)
{	
	paint_frame();
	
	gotoxy(33, 2);
	printf("로그인");
	
	gotoxy(25, 8); 
	printf("    회원 로그인\n");
	gotoxy(25, 11);
	printf("    관리자 로그인\n");
	gotoxy(25, 14);
	printf("    회원가입\n");
	
	x = 25;
	int y = 8;
	gotoxy(x, y);
	printf("▶");
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
				printf("▶");
			}
		}
		else if(key == 80){
			if(y != 14){
				gotoxy(x, y);
				printf("  ");
				gotoxy(x, y+=3);
				printf("▶");
			}
		}
	}
}

// 회원가입 콘솔 함수 
void sign_up_window(void)
{
	ACCOUNT sign;
	
	paint_frame();
	gotoxy(30, 2);
	printf("회원가입");
	
	gotoxy(13, 8); 
	printf("    아이디(12자리 이내): ");
	scanf("%s", sign.ID);
	gotoxy(13, 11);
	printf("  비밀번호(12자리 이내): ");
	scanf("%s", sign.PW);
	gotoxy(13, 14);
	printf("                   이름: ");
	scanf("%s", sign.name);
	
	sign_up(&sign);
}

// 회원가입 진행 함수 
void sign_up(ACCOUNT *sign)
{
	FILE *fp = fopen("account.txt", "a+");
	
	if(fp == NULL){
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.\n");
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "%s\n%s\n%s\n", sign->ID, &sign->PW, sign->name);
	fclose(fp);
	gotoxy(55, 22);
	printf("회원가입 완료\n");
	gotoxy(50, 19);
	printf("    홈으로");
	gotoxy(50, 19);
	printf("▶");
	fflush(stdin);
	if(getch() == 13){
		first_window();
		}
}

// 로그인 콘솔 함수 
void log_in_window(void)
{
	ACCOUNT user;
	
	paint_frame();
	gotoxy(30, 2);
	printf("회원 로그인");
	
	gotoxy(20, 10); 
	printf("      아이디: ");
	scanf("%s", user.ID);
	gotoxy(20, 13);
	printf("    비밀번호: ");
	scanf("%s", user.PW);
	
	log_in(&user);
}

// 로그인 프로세스 함수 
void log_in(ACCOUNT *user)
{
	ACCOUNT member;
	FILE *fp = fopen("account.txt", "r");
	int find = 0;
	
	if(fp == NULL){
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.\n");
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
		printf("ID 혹은 PW가 틀렸습니다. 다시 확인해주세요.\n");
		gotoxy(50, 19);
		printf("    이전");
		gotoxy(50, 19);
		printf("▶");
		fflush(stdin);
		if(getch() == 13){
			first_window();
		}
	}
	fclose(fp);
}

// 로그인 후 메인 화면 콘솔 함수 
void main_library(void)
{	
	paint_frame();
	gotoxy(30, 2);
	printf("Main 도서관");
	gotoxy(25, 8); 
	printf("    신작 안내\n");
	gotoxy(25, 11);
	printf("    베스트셀러\n");
	gotoxy(25, 14);
	printf("    도서검색\n");
	
	x = 25;
	int y = 8;
	gotoxy(x, y);
	printf("▶");
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
				printf("▶");
			}
		}
		else if(key == 80){
			if(y!= 14){
				gotoxy(x, y);
				printf("  ");
				gotoxy(x, y+=3);
				printf("▶");
			}
		}
	}
}

// 신작 출력 함수 
void new_book(void)
{
	BOOK newb;
	FILE *fp = fopen("book.txt", "r");
	
	if(fp == NULL){
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.");
		return 0; 
	}
	fseek(fp, -54, SEEK_END);
	fscanf(fp, "%s\n%s\n%s\n%s\n%d\n", &newb.name, &newb.author, &newb.publisher, &newb.date, &newb.loan);
	fclose(fp);
	print_search(&newb, 0);
}

// 베스트셀러 출력 함수
void best_seller(void)
{
	BOOK best;
	FILE *fp = fopen("book.txt", "r");
	
	if(fp == NULL){
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.");
		return 0; 
	}
	fseek(fp, 0, SEEK_SET);
	fscanf(fp, "%s\n%s\n%s\n%s\n%d\n", &best.name, &best.author, &best.publisher, &best.date, &best.loan);
	fclose(fp);
	print_search(&best, 0);
 } 
// 책 검색 콘솔 함수 
void book_search_window(int m)
{
	BOOK books;
	int y = 2;
	int n = m;
	
	paint_frame();
	gotoxy(30, 2);
	printf("책 검색");
	gotoxy(20, 8);
	printf("    책 이름: ");
	scanf("%s", &books.name);
	
	book_search(&books, n);
}

// 책 검색 프로세스 함수 
void book_search(BOOK *books, int n)
{
	BOOK search;
	FILE *fp = fopen("book.txt", "r");
	int find = 0;
	int m = n;
	
	if(fp == NULL){
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.\n");
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
		printf("등록되지 않은 책입니다. 다시 확인해주세요.\n");
		gotoxy(50, 19);
		printf("    이전");
		gotoxy(50, 19);
		printf("▶");
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

// 검색결과 프린트 함수 
void print_search(BOOK *books, int m)
{
	BOOK loans = *books;
	paint_frame();
	
	gotoxy(30, 2);
	printf("찾기 결과");
	gotoxy(20, 5);
	printf("    책 이름: %s", books->name);
	gotoxy(20, 7);
	printf("       저자: %s", books->author);
	gotoxy(20, 9);
	printf("     출판사: %s", books->publisher);
	gotoxy(20, 11);
	printf("     출판일: %s", books->date);
	gotoxy(20, 13);
	printf("       재고: %d", books->loan);
	gotoxy(25, 15);
	printf("    대출하기");
	gotoxy(25, 17);
	printf("    반납하기"); 
	gotoxy(25, 19);
	printf("    이전");
	
	x = 25;
	int y = 15;
	gotoxy(x, y);
	printf("▶");
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
				printf("▶");
			}
		}
		else if(key == 80){
			if(y!= 19){
				gotoxy(x, y);
				printf("  ");
				gotoxy(x, y+=2);
				printf("▶");
			}
		}
	}
}

// 대출 함수
void loan_book(BOOK *books)
{
	BOOK read;
	FILE *fp = fopen("book.txt", "r");
	FILE *wfp = fopen("book1.txt", "w");
	
	paint_frame();
	gotoxy(30, 2);
	printf("책 추가");
	gotoxy(20, 8);
	printf("   책 이름: %s", books->name);
	gotoxy(20, 10);
	printf("      저자: %s", books->author);
	gotoxy(20, 12);
	printf("    출판사: %s", books->publisher);
	gotoxy(20, 14);
	printf("    출판일: %s", books->date);
	gotoxy(20, 16);
	printf("      재고: %d", books->loan);
	
	if(books->loan == 0){
		gotoxy(55, 22);
		printf("재고가 없는 책입니다. 다른 책을 선택해주세요.\n");
		gotoxy(50, 19);
		printf("    이전");
		gotoxy(50, 19);
		printf("▶");
		fflush(stdin);
		if(getch() == 13){
			main_library();
		}
	}
	
	if(fp == NULL || wfp == NULL){
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.\n");
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
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.\n");
		return 1;
	}
	
	while(!feof(wfp2)){
		fscanf(wfp2, "%s\n%s\n%s\n%s\n%d\n", &read.name, &read.author, &read.publisher, &read.date, &read.loan);
		fprintf(fp2, "%s\n%s\n%s\n%s\n%d\n", read.name, read.author, read.publisher, read.date, read.loan);
	}
	fclose(fp2);
	fclose(wfp2);
	
	gotoxy(55, 22);
	printf("대출되었습니다.\n");
	gotoxy(50, 19);
	printf("    홈으로");
	gotoxy(50, 19);
	printf("▶");
	fflush(stdin);
	if(getch() == 13){
		first_window();
		}
}

// 반납 함수
void return_book(BOOK *books)
{
	BOOK read;
	FILE *fp = fopen("book.txt", "r");
	FILE *wfp = fopen("book1.txt", "w");
	
	paint_frame();
	gotoxy(30, 2);
	printf("책 추가");
	gotoxy(20, 8);
	printf("   책 이름: %s", books->name);
	gotoxy(20, 10);
	printf("      저자: %s", books->author);
	gotoxy(20, 12);
	printf("    출판사: %s", books->publisher);
	gotoxy(20, 14);
	printf("    출판일: %s", books->date);
	gotoxy(20, 16);
	printf("      재고: %d", books->loan);
	
	if(books->loan == 1){
		gotoxy(55, 22);
		printf("대출되지 않은 책입니다. 다른 책을 선택해주세요.\n");
		gotoxy(50, 19);
		printf("    이전");
		gotoxy(50, 19);
		printf("▶");
		fflush(stdin);
		if(getch() == 13){
			main_library();
		}
	}
	
	if(fp == NULL || wfp == NULL){
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.\n");
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
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.\n");
		return 1;
	}
	
	while(!feof(wfp2)){
		fscanf(wfp2, "%s\n%s\n%s\n%s\n%d\n", &read.name, &read.author, &read.publisher, &read.date, &read.loan);
		fprintf(fp2, "%s\n%s\n%s\n%s\n%d\n", read.name, read.author, read.publisher, read.date, read.loan);
	}
	fclose(fp2);
	fclose(wfp2);
	
	gotoxy(55, 22);
	printf("반납되었습니다.\n");
	gotoxy(50, 19);
	printf("    이전");
	gotoxy(50, 19);
	printf("▶");
	fflush(stdin);
	if(getch() == 13){
		main_library();
		}
}

// 관리자 계정 로그인 콘솔 함수 
void admin_log_window(void)
{
	ACCOUNT admin;
	
	paint_frame();
	gotoxy(30, 2);
	printf("관리자 로그인");
	
	gotoxy(20, 10); 
	printf("    아이디: ");
	scanf("%s", admin.ID);
	gotoxy(18, 13);
	printf("    비밀번호: ");
	scanf("%s", admin.PW);
	
	admin_log_in(&admin);
}

// 관리자 계정 로그인 프로세스 함수 
void admin_log_in(ACCOUNT *admin)
{
	ACCOUNT ad_log;
	FILE *fp = fopen("admin.txt", "r");
	int find = 0;
	
	if(fp == NULL){
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.\n");
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
		printf("ID 혹은 PW가 틀렸습니다. 다시 확인해주세요.\n");
		gotoxy(50, 19);
		printf("    이전");
		gotoxy(50, 19);
		printf("▶");
		fflush(stdin);
		if(getch() == 13){
			first_window();
		}
	}
	fclose(fp);
}

// 관리자 메인 콘솔 함수 
void admin_window(void)
{	
	int y = 2;
	
	paint_frame();
	gotoxy(30, 2);
	printf("관리자 Main");
	
	gotoxy(25, 8); 
	printf("    도서 추가\n");
	gotoxy(25, 11);
	printf("    도서 삭제\n");
	gotoxy(25, 14);
	printf("    도서 검색\n");
	
	x = 25;
	y = 8;
	gotoxy(x, y);
	printf("▶");
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
				printf("▶");
			}
		}
		else if(key == 80){
			if(y!= 14){
				gotoxy(x, y);
				printf("  ");
				gotoxy(x, y+=3);
				printf("▶");
			}
		}
	}
}

// 도서 추가 콘솔 함수 
void add_book_window(void)
{
	BOOK books;
	
	paint_frame();
	gotoxy(30, 2);
	printf("책 추가");
	gotoxy(20, 8);
	printf("   책 이름: ");
	scanf("%s", books.name);
	gotoxy(20, 10);
	printf("      저자: ");
	scanf("%s", books.author);
	gotoxy(20, 12);
	printf("    출판사: ");
	scanf("%s", books.publisher);
	gotoxy(20, 14);
	printf("    출판일: ");
	scanf("%s", books.date);
	gotoxy(20, 16);
	printf("      재고: ");
	scanf("%d", &books.loan);
	add_book(&books);
}

// 도서 추가 프로세스 함수 
void add_book(BOOK *books)
{
	FILE *fp = fopen("book.txt", "a+");
	
	if(fp == NULL){
		printf("파일을 열 수 없습니다. 프로그램을 종료합니다.\n");
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "%s\n%s\n%s\n%s\n%d\n", books->name, books->author, books->publisher, books->date, books->loan);
	gotoxy(55, 22);
	printf("도서 추가 완료\n");
	gotoxy(50, 19);
	printf("    이전");
	gotoxy(50, 19);
	printf("▶");
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
