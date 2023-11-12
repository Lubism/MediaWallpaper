#pragma once
#include<Windows.h>

// 寻找需要插入的窗口句柄
static HWND WorkerW()
{
	HWND workerw = nullptr;

	/*桌面的窗口, 包含应用程序的图标*/
	HWND DefView = FindWindowExW(NULL, NULL,
		L"SHELLDLL_DefView", NULL);

	/*实际要嵌入的窗口*/
	workerw = FindWindowExW(NULL, workerw,
		L"WorkerW", NULL);

	/*因为系统中存在多个WorkerW窗口, 因此需要遍历查找*/
	while ((!DefView) && workerw)
	{
		DefView = FindWindowExW(workerw, NULL,
			L"SHELLDLL_DefView", NULL);

		workerw = FindWindowExW(NULL, workerw,
			L"WorkerW", NULL);
	}

	/*嵌入的窗口默认是隐藏的, 需要手动拉起*/
	if (workerw) ShowWindow(workerw, SW_SHOW);

	return workerw;
}

// 从 Program Manager 中分离出两个 WorkerW 窗口
static size_t TimeoutProgman()
{
	/*查找目标窗口*/
	auto target = FindWindowW(L"Progman",
		L"Program Manager");
	size_t result = 0;

	/*对目标窗口发送信息, 使其分离出所需的两个 WorkerW 窗口*/
	SendMessageTimeoutW(target, 0x052c, 0, 0, SMTO_NORMAL,
		0x3e8, reinterpret_cast<PDWORD_PTR>(&result));
	return result;
}

/*
* 向目标窗口插入自己的窗口
* 
* @param windowID 自己的窗口句柄
* @param workerW 找到的目标窗口
*/
static void InsertProgman(size_t windowID, HWND& workerW)
{
	SetParent(reinterpret_cast<HWND>(windowID), workerW);
}