#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	wchar_t buf[20];
	_itow_s(GetCurrentProcessId(), buf, 10);
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, (LPCSTR)buf);
	printf("%lu\n", GetCurrentProcessId());
	while (true) 
	{
		Sleep(3000);
		for (int i = 0; i < wcslen(buf); i++)
		{
			printf("%c", buf[i]);
			Sleep(1);
		}
		cout << endl;

		if (WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0)
			return 0;
	}
}
