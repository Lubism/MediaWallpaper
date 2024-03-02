#pragma once

namespace UI
{
	class DesktopHandle
	{
		using Int = long long;
	public:
		static void InsertWindow(Int windowID);

		static void RefreshDesktop();
	};
}
