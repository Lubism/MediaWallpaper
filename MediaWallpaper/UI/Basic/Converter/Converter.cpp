#include"Converter.hpp"
#include<QResizeEvent>

using namespace UI;

void Converter::importData(int width, int height,
	QResizeEvent*& event)
{
	if (event == nullptr)
		return;

	FixWidth = width;
	FixHeight = height;
	CurrentWidth = event->size().width();
	CurrentHeight = event->size().height();
}
