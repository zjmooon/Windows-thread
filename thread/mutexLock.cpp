#include <iostream>
#include <string>
#include <stdio.h>
#include <Windows.h>
using namespace std;
//���������������������������ã���������������������


HANDLE g_hMutex = 0;
DWORD CALLBACK TestProc(LPVOID pParam) {
	char* Text = (char*)pParam;
	while (1) {
		/*cout << Text << endl;
		Sleep(500);*/
		//���ź�ʱ�����������ź�ʱ����
		WaitForSingleObject(g_hMutex, INFINITE);
		//�����źŵ�����£������˴����mutex��Ϊ���ź���
		for (int i = 0; i < strlen(Text); ++i) {
			printf("%c", Text[i]);//cout << Text[i];
			Sleep(100);
		}
		printf("\n");// cout << endl;
		//��ӡ���Ҫ�ͷŻ�����
		ReleaseMutex(g_hMutex);
	}
	return 0;
}

DWORD CALLBACK TestProc2(LPVOID pParam) {
	char* Text = (char*)pParam;
	while (1) {
		/*cout << Text << endl;
		Sleep(500);*/
		//���ź�ʱ�����������ź�ʱ����
		WaitForSingleObject(g_hMutex, INFINITE);
		for (int i = 0; i < strlen(Text); ++i) {
			printf("%c", Text[i]);//cout << Text[i];
			Sleep(100);
		}
		printf("\n");// cout << endl;
		//��ӡ���Ҫ�ͷŻ�����
		ReleaseMutex(g_hMutex);
	}
	return 0;
}
int main()
{
	//����������
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	//�����̴߳���mutex,�ڶ�������ΪFALSE,˵����ǰ�̣߳����̣߳���ӵ������
	//���κ��̶߳���ӵ�������Ǿ����źţ�Ϊ���߳���WaitForSingleObject()����׼��
	DWORD nID = 0;
	char* pszText = (char*)"hello";
	HANDLE hThd = CreateThread(NULL, 0, TestProc, pszText, 0, &nID);

	char* pszText2 = (char*)"World";
	HANDLE hTnd2 = CreateThread(NULL, 0, TestProc2, pszText2, 0, &nID);

	CloseHandle(g_hMutex);	//�ͷŻ��������ڴ��д�����Ӧ�����ͷ�
	getchar();
	return 0;
}