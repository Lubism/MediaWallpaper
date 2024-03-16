#include"DesktopInfo.hpp"
#include<QGuiApplication>
#include<QScreen>

std::vector<QRect> UI::DesktopInfo::Geometry = std::vector<QRect>();

using namespace UI;

QRect DesktopInfo::screenGeometry(long long screenIndex)
{
	DesktopInfo::refresh();
	return Geometry.at(screenIndex);
}

long long DesktopInfo::screenCount()
{
	DesktopInfo::refresh();
	return Geometry.size();
}

void DesktopInfo::refresh()
{
	auto screenList = QGuiApplication::screens();
	std::vector<QRect> result;

	int width = 0, height = 0, storage = 0;
	for (auto& it : screenList)
	{
		result.emplace_back(it->availableGeometry());

		storage = result.back().x();
		if (storage < width) width = storage;

		storage = result.back().y();
		if (storage < height) height = storage;
	}

	for (auto& it : result)
	{
		it =
		{
			it.x() - width,
			it.y() - height,
			it.width(),
			it.height()
		};
	}

	Geometry.swap(result);
}
