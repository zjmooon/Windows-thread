#include <iostream>
#include <string>
#include <stdio.h>
#include <Windows.h>
using namespace std;
//！！！！！！！！！！不起作用？？？？？？？？？互斥


HANDLE g_hMutex = 0;
DWORD CALLBACK TestProc(LPVOID pParam) {
	char* Text = (char*)pParam;
	while (1) {
		/*cout << Text << endl;
		Sleep(500);*/
		//无信号时不阻塞，有信号时阻塞
		WaitForSingleObject(g_hMutex, INFINITE);
		//在无信号的情况下，经过此代码后，mutex变为有信号了
		for (int i = 0; i < strlen(Text); ++i) {
			printf("%c", Text[i]);//cout << Text[i];
			Sleep(100);
		}
		printf("\n");// cout << endl;
		//打印完后要释放互斥量
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

DWORD CALLBACK TestProc2(LPVOID pParam) {
	char* Text = (char*)pParam;
	while (1) {
		/*cout << Text << endl;
		Sleep(500);*/
		//无信号时不阻塞，有信号时阻塞
		WaitForSingleObject(g_hMutex, INFINITE);
		for (int i = 0; i < strlen(Text); ++i) {
			printf("%c", Text[i]);//cout << Text[i];
			Sleep(100);
		}
		printf("\n");// cout << endl;
		//打印完后要释放互斥量
		ReleaseMutex(g_hMutex);
	}
	return 0;
}
int main()
{
	//创建互斥量
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	//在主线程创建mutex,第二参数设为FALSE,说明当前线程（主线程）不拥有它。
	//则任何线程都不拥有它，那就有信号，为子线程中WaitForSingleObject()做好准备
	DWORD nID = 0;
	char* pszText = (char*)"hello";
	HANDLE hThd = CreateThread(NULL, 0, TestProc, pszText, 0, &nID);

	char* pszText2 = (char*)"World";
	HANDLE hTnd2 = CreateThread(NULL, 0, TestProc2, pszText2, 0, &nID);

	CloseHandle(g_hMutex);	//释放互斥量，内存有创建就应该有释放
	getchar();
	return 0;
}