#include "Func.h"

/*
[���׸� 3] : �迭 ���
*/
struct vaccine V[500]; // ��¥��_��Ŵ�_����Ƚ��
char name[27][20]; // ������ �̸� (��Ÿ�)
char commend[20]; // ��ɾ�

void UseCommend(char com[]);
void PP(char name[]);
void help();
void list();
void print();
void graph();
void exitt();

/*
[���׸� 6] : ������ Ȱ�� 
*/
void (*Function[5])(void) = { help, list, print, graph, exitt };
const char* comword1[] = { "/help","/list" ,"/print" ,"/graph","/exit" };
const char* comword2[] = { "0","1" ,"2" ,"3","4" };

/*
[���׸� 4] : ������ ���
*/
char* GNS(char* str, char delimiter, char* buf)
{
	while (*str != NULL && *str != delimiter) // NULL �Ǵ� ' , ' �� ���ö����� �ݺ�
		*buf++ = *str++; // str�� ���ڸ� buf�� �޸𸮿� ����
	if (*(buf - 1) == '\n') // ������ ���ڰ� �ٹٲ��̶��, NULL�� ��ü
		*(buf - 1) = 0;
	else // �ٹٲ� �ƴϾ ������ ���ڿ� NULL �߰�.
		*buf = 0;
	if (*str == delimiter) // str�� ' , '�� ������ �������� �ǳʶڴ�.
		str++;

	return str; // NULL �̳� ' , ' ������ ���ڷ� �Ѿ��.
}

/*
[���׸� 7] : ���� �����
*/
void FileRead()
{
	FILE* file = NULL;

	if (fopen_s(&file, "Data.csv", "rt") == 0) // Data.csv ���� ���⿡ �����ߴٸ�
	{

		char Line[1000], str[32], * pos; // Line: ���� ������ ����, str: ��ǥ ���� ����, pos: ��ġ


		if (fgets(Line, 1000, file) != NULL) // ���� ù��° ����: ��Ÿ�
		{
			pos = Line; 
			pos = GNS(pos, ',', str); // ù��° ����: �Ⱦ�
			for (int i = 0; *pos != NULL; i++) // �ι�° �������� ��Ÿ�
			{
				pos = GNS(pos, ',', str); 
				strcpy_s(name[i], str);
			}
		}
		fgets(Line, 1000, file); // �ι�° ���� V[1]: ��ü���� ������

		int a = 0;
		while (fgets(Line, 1000, file) != NULL) // ����° ���κ���: ��¥�� ������
		{
			pos = Line; // ó������ ����
			pos = GNS(pos, ',', str); // ���� ù��° ������
			strcpy_s(V[a].time, str); // ������¥�̴�.
			for (int i = 0; *pos != NULL; i++) 
			{
				pos = GNS(pos, ',', str); // ���پ� �޾Ƽ� ' , ' ������ ���� str�� �ѱ��.
				V[a].data[i] = atoi(str); // ��Ŵ� ����Ƚ��
			}
			a++;
		}
		fclose(file);
	}
}

void LoadMenu() // ���� �Ŵ�
{
	char s[] = "Covid-19  �������";
	PP(s);
	printf("  0 �Ǵ� /help : ��ɾ� ����     \n\n");
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
		printf(" �߸��� �Է°��Դϴ�.\n\n");
		printf(" ��ɾ�� '/'�� �ٿ��ֽʽÿ�.\n\n");
		printf(" ���� �Ŵ��� ���ư��ϴ�.\n\n");
	}
}

void PP(char name[]) // ���ڰ� ����ϱ� ����, �� �ڵ� ����
{
	// �� ���̴� 50
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
	char s[] = "��ɾ�  ����";
	PP(s);
	printf("�� 1 �Ǵ� /list : ������ ��� ���\n\n");
	printf("�� 2 �Ǵ� /print : ��� �����͸� �ؽ�Ʈ�� ���\n\n");
	printf("�� 3 �Ǵ� /graph: ��� �����͸� �׷����� ���\n\n");
	printf("�� 4 �Ǵ� /exit : ���α׷� ����\n\n");
	printf("--------------------------------------------------\n\n");
	printf(": ");
	scanf_s("%s", commend, sizeof(commend));
	printf("\n");
	UseCommend(commend);
}

void list()
{
	int i, d;
	char s[] = "������  ����Ʈ";
	PP(s);
	for (int i = 0; i < 27; i++)
		printf("�� %d��° ������ : %s\n", i, name[i]);
	printf("\n--------------------------------------------------\n\n");
	printf(" 2022-06-01 ���� 2021-02-26 ����, �� 461��ġ ����\n\n");
	printf(" �� 27�� ��� ������ ��� �Ϸ� \n");
	printf("\n");
}

void print() 
{
	int i, d;
	char s[] = "��� ���� ���";
	PP(s);
	printf(" i ��° �����͸� ���� �ֱٺ��� d ��ġ ��ŭ ���\n\n");
	printf(" ���� �ΰ��� ���ʴ�� �Է��Ͻÿ�. (ex. 0 10)\n\n");
	printf("--------------------------------------------------\n\n");
	printf(": ");
	scanf_s("%d%d", &i, &d, sizeof(i), sizeof(d));
	printf("\n");

	if ((i >= 0 && i < 27) && (d > 0 && d <= 461)) // ������ ���� ���� �Է� ����
	{
		PP(name[i]);
		for (int ii = 0; ii < d; ii++)
			printf("�� %s : %d\n", V[ii].time, V[ii].data[i]);
		printf("\n--------------------------------------------------\n\n");
		printf(" %s, %d��ġ ��� �Ϸ�\n", name[i], d);
		printf("\n");
	}
	else
	{
		printf(" �߸��� �Է°��Դϴ�.\n\n");
		printf(" i: 0 ~ 26, d: 1 ~ 461\n");
		printf("\n");
	}
}

void graph() 
{
	int i, d;
	char s[] = "��� ���� ���";
	PP(s);
	printf(" i ��° �����͸� ���� �ֱٺ��� d ��ġ ��ŭ ���\n\n");
	printf(" ���� �ΰ��� ���ʴ�� �Է��Ͻÿ�. (ex. 0 10)\n\n");
	printf("--------------------------------------------------\n\n");
	printf(": ");
	scanf_s("%d%d", &i, &d, sizeof(i), sizeof(d));
	printf("\n");

	if ((i >= 0 && i < 27) && (d > 0 && d <= 461)) // ������ ���� ���� �Է� ����
	{
		PP(name[i]);

		int pp[500] = {};
		int big = 0;

		for (int x = 0; x < d; x++) // ���� �� �������� �ִ밪 ã�� (big)
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
		printf(" %s, %d��ġ ��� �Ϸ�\n", name[i], d);
		printf("\n");
	}
	else
	{
		printf(" �߸��� �Է°��Դϴ�.\n\n");
		printf(" i: 0 ~ 26, d: 1 ~ 461\n");
		printf("\n");
	}
}

void exitt() 
{
	exit(0);
}