#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	STARTUPINFO si = { sizeof(si) };
	ZeroMemory(&si, sizeof(si));
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));
	TCHAR cmdLine[] = "Project1.exe";
	vector<HANDLE*> vecEvent;
	char choice = 0;
	int count = 0;
	while (true)
	{
		fflush(stdin);
		switch (choice = getchar()) 
		{
		case '+':
		{
			if (count >= 10) 
			{
				cout << "Bufer is full" << endl;
				break;
			}
			count++;
			if (CreateProcess(NULL, cmdLine, NULL, NULL, FALSE,0, NULL, NULL, &si, &pi) == TRUE) 
			{
				wchar_t buf[20];
				_itow_s(pi.dwProcessId, buf, 10);
				HANDLE temp = CreateEventA(
					NULL,//тип защиты		
					FALSE,//тип сброса-автоматический
					FALSE,//начальное состояние несигнальное
					(LPCSTR)buf//имя объекта
				);
				vecEvent.push_back(new HANDLE(temp));
				CloseHandle(pi.hThread);
				CloseHandle(pi.hProcess);
				break;
			}
			printf("Error #%lu\n", GetLastError());
			break;
		}
		case '-':
		{
			if (vecEvent.empty())
			{
				cout << "No existing process!" << endl;
				break;
			}
			SetEvent(*vecEvent.back());
			CloseHandle(*vecEvent.back());
			delete vecEvent.back();
			vecEvent.pop_back();
			count--;
			break;
		}
		case 'q':
			return 0;
		}
	}
}
