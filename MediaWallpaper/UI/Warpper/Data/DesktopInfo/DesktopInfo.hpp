#pragma once
#include<vector>
#include<QRect>

namespace UI
{
	class DesktopInfo
	{
	public:
		static QRect screenGeometry(long long screenIndex);

		static long long screenCount();
	private:
		static void refresh();
	private:
		static std::vector<QRect> Geometry;
		inline DesktopInfo() {}
	};
}
