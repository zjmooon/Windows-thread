#include <Windows.h>
#include <iostream>
using namespace std;

/*
**	多线程对同一个资源改，涉及到汇编、压栈、弹栈、寄存器、CPU时间片
**	当对数据原子锁是，只能有一个进程对此资源进行操作
*/
long g_value = 0;

DWORD CALLBACK thProc1(LPVOID pParam) {
	for (int i = 0; i < 10000000; ++i) {
		g_value++;
		//InterlockedIncrement(&g_value);
	}
	return 0;
}

DWORD CALLBACK thProc2(LPVOID pParam) {
	for (int i = 0; i < 10000000; ++i) {
		g_value++;
		//InterlockedIncrement(&g_value);
	}
	return 0;
}

int main()
{
	DWORD nID = 0;
	HANDLE hd[2];

	hd[0] = CreateThread(NULL, 0, thProc1, NULL, 0, &nID);
	hd[1] = CreateThread(NULL, 0, thProc2, NULL, 0, &nID);

	//阻塞
	WaitForMultipleObjects(2, hd, TRUE, INFINITE);

	cout << g_value << endl;
	return 0;
}