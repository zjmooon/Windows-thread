#include <Windows.h>
#include <iostream>
using namespace std;

/*
**	���̶߳�ͬһ����Դ�ģ��漰����ࡢѹջ����ջ���Ĵ�����CPUʱ��Ƭ
**	��������ԭ�����ǣ�ֻ����һ�����̶Դ���Դ���в���
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

	//����
	WaitForMultipleObjects(2, hd, TRUE, INFINITE);

	cout << g_value << endl;
	return 0;
}