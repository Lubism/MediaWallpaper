#include"ComboBox.hpp"
#include<QWheelEvent>

using namespace UI;

void ComboBox::wheelEvent(QWheelEvent* event)
{
	event->ignore();
}
