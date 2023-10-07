#pragma once
#include<Windows.h>

namespace UI
{
	class DesktopHandle
	{
	public:
		static inline HWND WorkerW()
		{
			HWND workerw = nullptr;
			HWND DefView = FindWindowExW(NULL, NULL,
				L"SHELLDLL_DefView", NULL);

			workerw = FindWindowExW(NULL, workerw,
				L"WorkerW", NULL);
			while ((!DefView) && workerw)
			{
				DefView = FindWindowExW(workerw, NULL,
					L"SHELLDLL_DefView", NULL);

				workerw = FindWindowExW(NULL, workerw,
					L"WorkerW", NULL);
			}
			if (workerw) ShowWindow(workerw, SW_SHOW);
			return workerw;
		}

		static inline size_t TimeoutProgman()
		{
			auto target = FindWindowW(L"Progman",
				L"Program Manager");
			size_t result = 0;
			SendMessageTimeoutW(target, 0x052c, 0, 0, SMTO_NORMAL,
				0x3e8, reinterpret_cast<PDWORD_PTR>(&result));
			return result;
		}

		static inline int RefreshProgman()
		{
			auto target = GetShellWindow();
			return PostMessageW(target,
				WM_USER + 300,
				0x0D, TRUE);
		}

		static inline void InsertProgman(size_t windowID, HWND& workerW)
		{
			SetParent(reinterpret_cast<HWND>(windowID), workerW);
		}

		static inline void InsertProgman(size_t windowID)
		{
			TimeoutProgman();

			auto workerW = WorkerW();

			SetParent(reinterpret_cast<HWND>(windowID), workerW);
		}
	};
}