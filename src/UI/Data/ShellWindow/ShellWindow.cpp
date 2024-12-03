#include"ShellWindow.hpp"

#ifdef _DEBUG

#include<iostream>

using namespace std;

#endif // _DEBUG

#ifdef _WIN32

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "Psapi.lib")

#include<dwmapi.h>
#include<Psapi.h>

#endif // _WIN32

#ifdef __linux__

#endif // __linux__

namespace UI
{

#ifdef _WIN32

	static inline void ForegroundGeometry(HWND& hwnd, QRect& rect)
	{
		static RECT temp{};
		hwnd = GetForegroundWindow();
		DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &temp, sizeof(RECT));

		rect.setRect(temp.left, temp.top,
			temp.right - temp.left,
			temp.bottom - temp.top
		);
	}

	static inline QString GetProcessName(HWND& hwnd)
	{
		static DWORD pid = 0;

		if (GetWindowThreadProcessId(hwnd, &pid))
		{
			static HANDLE handle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
			if (handle == NULL) return QString();
			WCHAR temp[1024] = { 0 };

			if (!K32GetModuleFileNameExW(handle, 0, temp, 1024))
				return QString();

			return QString::fromWCharArray(temp);
		}

		return QString();
	}

#endif // _WIN32

#ifdef __linux__

#endif // __linux__

}

using namespace UI;

std::vector<QRect> ShellWindowCore::RawGeometry = std::vector<QRect>();

std::vector<QRect> ShellWindowCore::Geometry = std::vector<QRect>();

#ifdef _WIN32

std::vector<QString> ShellWindow::ExcludeHandle = std::vector<QString>();

std::pair<int, ShellWindow::WindowState> ShellWindow::AcqiureState()
{
	auto ret = std::pair<int, WindowState>(-1, WindowState::None);
	return ret;

	HWND hwnd = NULL, target = NULL;
	QRect rect;

	ForegroundGeometry(hwnd, rect);

	if (!ExcludeHandle.empty()) /*Testing: self-exclude*/
		target = FindWindowW(L"Qt5152dQWindowIcon", ExcludeHandle.back().toStdWString().data());

	for (auto it = RawGeometry.begin(); it != RawGeometry.end(); ++it)
	{
		ret.first = std::distance(RawGeometry.begin(), it);

		if (ShellWindow::IsDesktop(hwnd) || target == hwnd)
		{
			if (it->contains(ShellWindow::RawPoint()))
			{
				ret.second = WindowState::None;
				break;
			}
		}
		else
		{
			if (*it == rect)
			{
				ret.second = WindowState::Fullscreen;
				break;
			}

			if (it->contains(rect.center()))
			{
				ret.second = WindowState::Focused;
				break;
			}
		}
	}

	return ret;
}

HWND ShellWindow::WorkerW()
{
	HWND workerw = nullptr;
	HWND defView = FindWindowExW(NULL, NULL, L"SHELLDLL_DefView", NULL);

	workerw = FindWindowExW(NULL, workerw, L"WorkerW", NULL);
	while ((!defView) && workerw)
	{
		defView = FindWindowExW(workerw, NULL, L"SHELLDLL_DefView", NULL);

		workerw = FindWindowExW(NULL, workerw, L"WorkerW", NULL);
	}
	if (workerw) ShowWindow(workerw, SW_SHOW);

	return workerw;
}

bool ShellWindow::IsDesktop(HWND target)
{
	HWND workerw = nullptr, defView = nullptr;
	workerw = FindWindowExW(NULL, workerw, L"WorkerW", NULL);
	defView = FindWindowExW(NULL, NULL, L"SHELLDLL_DefView", NULL);

	while (true)
	{
		defView = FindWindowExW(workerw, NULL, L"SHELLDLL_DefView", NULL);

		if (defView != nullptr)
		{
			if (workerw == target)
				return true;
			else
				break;
		}

		workerw = FindWindowExW(NULL, workerw, L"WorkerW", NULL);
	}

	return false;
}

#endif // _WIN32

#ifdef __linux__

std::pair<int, ShellWindow::WindowState> ShellWindow::AcqiureState()
{
	return std::pair<int, ShellWindow::WindowState>(-1, WindowState::None);
}

#endif // __linux__
