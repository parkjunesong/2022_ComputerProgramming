#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <math.h>
#include <windows.h>

/*
[���׸� 5] : ����ü ���
*/
struct vaccine {
	char time[20];
	int data[27];
};

/*
[���׸� 2] : �Լ� ���
Func.cpp�� �� �� �پ��� �Լ��� ���.
*/
char* GNS(char* str, char delimiter, char* buf);
void FileRead();
void LoadMenu();