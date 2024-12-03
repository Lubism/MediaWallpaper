#pragma once
#include<QGuiApplication>
#include<QScreen>

#include<vector>

namespace UI
{
	class ShellWindowCore
	{
	private:
		inline ShellWindowCore() = delete;
		inline ~ShellWindowCore() = delete;
	public:
		enum WindowState { None, Focused, Fullscreen };
	public:
		static inline QRect ScreenGeometry(int screenIndex);
		static inline void RefreshGeometry();
		static inline int ScreenCount();
	protected:
		static std::vector<QRect> RawGeometry;
	private:
		static std::vector<QRect> Geometry;
	};

	inline QRect ShellWindowCore::ScreenGeometry(int screenIndex)
	{
		if (screenIndex < 0 || screenIndex >= Geometry.size())
			return QRect();
		return Geometry.at(screenIndex);
	}

	inline void ShellWindowCore::RefreshGeometry()
	{
		auto screenList = QGuiApplication::screens();
		RawGeometry.reserve(1ULL << 3);
		Geometry.reserve(1ULL << 4);
		RawGeometry.clear();
		Geometry.clear();

		int width = 0, height = 0, storage = 0;
		for (auto& it : screenList)
		{
			RawGeometry.emplace_back(it->availableGeometry());

			storage = RawGeometry.back().x();
			if (storage < width) width = storage;

			storage = RawGeometry.back().y();
			if (storage < height) height = storage;
		}

		for (auto& it : RawGeometry)
		{
			Geometry.push_back(QRect(it.x() - width,
				it.y() - height, it.width(),
				it.height())
			);
		}
	}

	inline int ShellWindowCore::ScreenCount()
	{
		return Geometry.size();
	}
}

#ifdef _WIN32

#include<Windows.h>

namespace UI
{
	class ShellWindow :public ShellWindowCore
	{
	private:
		inline ShellWindow() = delete;
		inline ~ShellWindow() = delete;
	public:
		static inline void ImportHandle(size_t handleID) { ShellWindow::InsertProgman(handleID); }

		static inline void RefreshDisplay() { ShellWindow::RefreshProgman(); }

		static inline void Init() { ShellWindow::TimeoutProgman(); }

		static inline void AddExcludeHandle(const QString& name)
		{
			ExcludeHandle.push_back(name);
		}

		static std::pair<int, WindowState> AcqiureState();
	private:
		static HWND WorkerW();

		static inline size_t TimeoutProgman()
		{
			auto target = FindWindowW(L"Progman", L"Program Manager");
			size_t result = 0;

			SendMessageTimeoutW(target, 0x052c, 0, 0, SMTO_NORMAL,
				0x3e8, reinterpret_cast<PDWORD_PTR>(&result));
			return result;
		}

		static inline QPoint RawPoint()
		{
			QPoint result;
			static POINT temp;

			if (GetCursorPos(&temp))
			{
				result.setX(temp.x);
				result.setY(temp.y);
			}

			return result;
		}

		static inline int RefreshProgman()
		{
			auto target = GetShellWindow();
			return PostMessageW(target,
				WM_USER + 300,
				0x0D, TRUE);
		}

		static inline void InsertProgman(size_t windowID)
		{
			auto workerW = WorkerW();

			SetParent(reinterpret_cast<HWND>(windowID), workerW);
		}

		static inline bool IsExcluded(HWND& hwnd)
		{
			return false;
		}

		static bool IsDesktop(HWND target);
	private:
		static std::vector<QString> ExcludeHandle;
	};
}

#endif // For Windows

#ifdef __linux__

namespace UI
{
	class ShellWindow
	{
	public:
		static inline void ImportHandle(size_t handleID) { }

		static inline void RefreshDisplay() { }

		static inline void Init() { }

		static std::pair<int, WindowState> AcqiureState();
	private:
		inline ShellWIndow() = delete;
		inline ~ShellWindow() = delete;
	};
}

#endif // For Linux
