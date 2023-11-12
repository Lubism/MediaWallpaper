#pragma once
#include<Windows.h>

// Ѱ����Ҫ����Ĵ��ھ��
static HWND WorkerW()
{
	HWND workerw = nullptr;

	/*����Ĵ���, ����Ӧ�ó����ͼ��*/
	HWND DefView = FindWindowExW(NULL, NULL,
		L"SHELLDLL_DefView", NULL);

	/*ʵ��ҪǶ��Ĵ���*/
	workerw = FindWindowExW(NULL, workerw,
		L"WorkerW", NULL);

	/*��Ϊϵͳ�д��ڶ��WorkerW����, �����Ҫ��������*/
	while ((!DefView) && workerw)
	{
		DefView = FindWindowExW(workerw, NULL,
			L"SHELLDLL_DefView", NULL);

		workerw = FindWindowExW(NULL, workerw,
			L"WorkerW", NULL);
	}

	/*Ƕ��Ĵ���Ĭ�������ص�, ��Ҫ�ֶ�����*/
	if (workerw) ShowWindow(workerw, SW_SHOW);

	return workerw;
}

// �� Program Manager �з�������� WorkerW ����
static size_t TimeoutProgman()
{
	/*����Ŀ�괰��*/
	auto target = FindWindowW(L"Progman",
		L"Program Manager");
	size_t result = 0;

	/*��Ŀ�괰�ڷ�����Ϣ, ʹ��������������� WorkerW ����*/
	SendMessageTimeoutW(target, 0x052c, 0, 0, SMTO_NORMAL,
		0x3e8, reinterpret_cast<PDWORD_PTR>(&result));
	return result;
}

/*
* ��Ŀ�괰�ڲ����Լ��Ĵ���
* 
* @param windowID �Լ��Ĵ��ھ��
* @param workerW �ҵ���Ŀ�괰��
*/
static void InsertProgman(size_t windowID, HWND& workerW)
{
	SetParent(reinterpret_cast<HWND>(windowID), workerW);
}