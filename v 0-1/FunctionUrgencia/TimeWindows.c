#include <Windows.h>
#include <stdio.h>

void main()
{
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	printf("Year:%d\nMonth:%d\nDate:%d\nHour:%d\nMin:%d\nSecond:% d\n"
	,str_t.wYear,str_t.wMonth,str_t.wDay
	,str_t.wHour,str_t.wMinute,str_t.wSecond);

}
