#include "Func.h"

/*
[평가항목 3] : 배열 사용
*/
struct vaccine V[500]; // 날짜별_백신당_접종횟수
char name[27][20]; // 데이터 이름 (백신명)
char commend[20]; // 명령어

void UseCommend(char com[]);
void PP(char name[]);
void help();
void list();
void print();
void graph();
void exitt();

/*
[평가항목 6] : 포인터 활용 
*/
void (*Function[5])(void) = { help, list, print, graph, exitt };
const char* comword1[] = { "/help","/list" ,"/print" ,"/graph","/exit" };
const char* comword2[] = { "0","1" ,"2" ,"3","4" };

/*
[평가항목 4] : 포인터 사용
*/
char* GNS(char* str, char delimiter, char* buf)
{
	while (*str != NULL && *str != delimiter) // NULL 또는 ' , ' 가 나올때까지 반복
		*buf++ = *str++; // str의 문자를 buf의 메모리에 복사
	if (*(buf - 1) == '\n') // 마지막 문자가 줄바꿈이라면, NULL로 교체
		*(buf - 1) = 0;
	else // 줄바꿈 아니어도 마지막 문자에 NULL 추가.
		*buf = 0;
	if (*str == delimiter) // str이 ' , '를 만나면 다음으로 건너뛴다.
		str++;

	return str; // NULL 이나 ' , ' 다음의 문자로 넘어간다.
}

/*
[평가항목 7] : 파일 입출력
*/
void FileRead()
{
	FILE* file = NULL;

	if (fopen_s(&file, "Data.csv", "rt") == 0) // Data.csv 파일 열기에 성공했다면
	{

		char Line[1000], str[32], * pos; // Line: 한줄 단위로 저장, str: 쉼표 사이 문자, pos: 위치


		if (fgets(Line, 1000, file) != NULL) // 가장 첫번째 라인: 백신명
		{
			pos = Line; 
			pos = GNS(pos, ',', str); // 첫번째 단위: 안씀
			for (int i = 0; *pos != NULL; i++) // 두번째 단위부터 백신명
			{
				pos = GNS(pos, ',', str); 
				strcpy_s(name[i], str);
			}
		}
		fgets(Line, 1000, file); // 두번째 라인 V[1]: 전체누적 데이터

		int a = 0;
		while (fgets(Line, 1000, file) != NULL) // 세번째 라인부터: 날짜별 데이터
		{
			pos = Line; // 처음부터 시작
			pos = GNS(pos, ',', str); // 가장 첫번째 단위는
			strcpy_s(V[a].time, str); // 접종날짜이다.
			for (int i = 0; *pos != NULL; i++) 
			{
				pos = GNS(pos, ',', str); // 한줄씩 받아서 ' , ' 단위로 끊어 str로 넘긴다.
				V[a].data[i] = atoi(str); // 백신당 접종횟수
			}
			a++;
		}
		fclose(file);
	}
}

void LoadMenu() // 메인 매뉴
{
	char s[] = "Covid-19  백신정보";
	PP(s);
	printf("  0 또는 /help : 명령어 도움말     \n\n");
	printf(": ");
	scanf_s("%s",commend, sizeof(commend));
	printf("\n");
	UseCommend(commend);
}

void UseCommend(char com[])
{
	if (strcmp(com, comword1[4]) == 0 || strcmp(com, comword2[4]) == 0)
	{
		Function[4]();
	}
	else if (strcmp(com, comword1[0]) == 0 || strcmp(com, comword2[0]) == 0)
	{
		Function[0]();
	}
	else if (strcmp(com, comword1[1]) == 0 || strcmp(com, comword2[1]) == 0)
	{
		Function[1]();
	}
	else if (strcmp(com, comword1[2]) == 0 || strcmp(com, comword2[2]) == 0)
	{
		Function[2]();
	}
	else if (strcmp(com, comword1[3]) == 0 || strcmp(com, comword2[3]) == 0)
	{
		Function[3]();
	}
	else
	{
		printf(" 잘못된 입력값입니다.\n\n");
		printf(" 명령어에는 '/'를 붙여주십시오.\n\n");
		printf(" 메인 매뉴로 돌아갑니다.\n\n");
	}
}

void PP(char name[]) // 예쁘게 출력하기 위해, 줄 자동 조절
{
	// 줄 길이는 50
	int L = strlen(name);
	printf("--------------------------------------------------\n");
	for (int i = 0; i < (50 - L) / 2 - 2; i++)
		printf("-");
	printf("  %s  ", name);
	for (int i = 0; i < (50 - L) / 2 - 2; i++)
		printf("-");
	printf("\n");
	printf("--------------------------------------------------\n\n");
}

void help() 
{
	char s[] = "명령어  도움말";
	PP(s);
	printf("· 1 또는 /list : 데이터 목록 출력\n\n");
	printf("· 2 또는 /print : 백신 데이터를 텍스트로 출력\n\n");
	printf("· 3 또는 /graph: 백신 데이터를 그래프로 출력\n\n");
	printf("· 4 또는 /exit : 프로그램 종료\n\n");
	printf("--------------------------------------------------\n\n");
	printf(": ");
	scanf_s("%s", commend, sizeof(commend));
	printf("\n");
	UseCommend(commend);
}

void list()
{
	int i, d;
	char s[] = "데이터  리스트";
	PP(s);
	for (int i = 0; i < 27; i++)
		printf("· %d번째 데이터 : %s\n", i, name[i]);
	printf("\n--------------------------------------------------\n\n");
	printf(" 2022-06-01 부터 2021-02-26 까지, 각 461일치 존재\n\n");
	printf(" 총 27개 백신 데이터 출력 완료 \n");
	printf("\n");
}

void print() 
{
	int i, d;
	char s[] = "백신 정보 출력";
	PP(s);
	printf(" i 번째 데이터를 가장 최근부터 d 일치 만큼 출력\n\n");
	printf(" 숫자 두개를 차례대로 입력하시오. (ex. 0 10)\n\n");
	printf("--------------------------------------------------\n\n");
	printf(": ");
	scanf_s("%d%d", &i, &d, sizeof(i), sizeof(d));
	printf("\n");

	if ((i >= 0 && i < 27) && (d > 0 && d <= 461)) // 데이터 범위 밖의 입력 감지
	{
		PP(name[i]);
		for (int ii = 0; ii < d; ii++)
			printf("· %s : %d\n", V[ii].time, V[ii].data[i]);
		printf("\n--------------------------------------------------\n\n");
		printf(" %s, %d일치 출력 완료\n", name[i], d);
		printf("\n");
	}
	else
	{
		printf(" 잘못된 입력값입니다.\n\n");
		printf(" i: 0 ~ 26, d: 1 ~ 461\n");
		printf("\n");
	}
}

void graph() 
{
	int i, d;
	char s[] = "백신 정보 출력";
	PP(s);
	printf(" i 번째 데이터를 가장 최근부터 d 일치 만큼 출력\n\n");
	printf(" 숫자 두개를 차례대로 입력하시오. (ex. 0 10)\n\n");
	printf("--------------------------------------------------\n\n");
	printf(": ");
	scanf_s("%d%d", &i, &d, sizeof(i), sizeof(d));
	printf("\n");

	if ((i >= 0 && i < 27) && (d > 0 && d <= 461)) // 데이터 범위 밖의 입력 감지
	{
		PP(name[i]);

		int pp[500] = {};
		int big = 0;

		for (int x = 0; x < d; x++) // 범위 내 데이터중 최대값 찾기 (big)
		{
			if (V[x].data[i] > big)
				big = V[x].data[i];
		}
		for (int x = 0; x < d; x++)
		{
			pp[x] = round(float(V[x].data[i]) / big * 39);
		}
		for (int i = 0; i < d; i++)
		{
			printf("%s|", V[i].time);
			for (int x = 0; x < pp[i]; x++)
				printf("*");
			printf("\n");
		}
		printf("\n--------------------------------------------------\n\n");
		printf(" %s, %d일치 출력 완료\n", name[i], d);
		printf("\n");
	}
	else
	{
		printf(" 잘못된 입력값입니다.\n\n");
		printf(" i: 0 ~ 26, d: 1 ~ 461\n");
		printf("\n");
	}
}

void exitt() 
{
	exit(0);
}