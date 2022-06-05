#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <math.h>
#include <windows.h>

/*
[평가항목 5] : 구조체 사용
*/
struct vaccine {
	char time[20];
	int data[27];
};

/*
[평가항목 2] : 함수 사용
Func.cpp에 그 외 다양한 함수들 사용.
*/
char* GNS(char* str, char delimiter, char* buf);
void FileRead();
void LoadMenu();