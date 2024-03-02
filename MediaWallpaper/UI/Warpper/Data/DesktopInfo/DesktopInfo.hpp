#pragma once
#include<QDesktopWidget>
#include<memory>

namespace UI
{
	class DesktopInfo
	{
		using ptr = std::unique_ptr<QDesktopWidget>;
	public:
		static inline QRect screenGeometry(long long screenIndex);
		static long long screenCount();
		static inline void refresh();
	private:
		inline DesktopInfo() {}
		static ptr Pointer;
	};

	inline QRect DesktopInfo::screenGeometry(long long screenIndex)
	{
		if (!Pointer) refresh();
		return Pointer->screenGeometry(static_cast<int>(screenIndex));
	}

	inline long long DesktopInfo::screenCount()
	{
		if (!Pointer) refresh();
		return Pointer->screenCount();
	}

	void DesktopInfo::refresh()
	{
		Pointer.reset(new QDesktopWidget);
	}
}
