#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

DWORD CALLBACK TestProc(LPVOID pParam) {
	char* Text = (char*)pParam;
	while (1) {
		cout << Text << endl;
		Sleep(500);
	}
	return 0;
}

DWORD CALLBACK TestProc2(LPVOID pParam) {
	char* Text = (char*)pParam;
	while (1) {
		cout << Text << endl;
		Sleep(500);
	}
	return 0;
}
int main()
{
	DWORD nID = 0;
	char* pszText = (char*)"hello";
	HANDLE hThd = CreateThread(NULL, 0, TestProc, pszText, 0, &nID);
	
	char* pszText2 = (char*)"World";
	HANDLE hTnd2 = CreateThread(NULL, 0, TestProc2, pszText2, 
		CREATE_SUSPENDED, &nID);
	
	getchar();
	SuspendThread(hThd);	//挂起线程
	ResumeThread(hTnd2);	//唤醒线程
	getchar();
	return 0;
}