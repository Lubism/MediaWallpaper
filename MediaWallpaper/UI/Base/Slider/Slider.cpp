#include<QMouseEvent>
#include<QWheelEvent>
#include<QKeyEvent>

#include"Slider.hpp"

using namespace UI;

void Slider::mouseReleaseEvent(QMouseEvent* event)
{
	this->mouseTriggerEvent(event);
}

void Slider::mousePressEvent(QMouseEvent* event)
{
	event->ignore();
}

void Slider::mouseMoveEvent(QMouseEvent* event)
{
	this->mouseTriggerEvent(event);
}

void Slider::keyReleaseEvent(QKeyEvent* event)
{
	auto val = this->value();

	switch (event->key())
	{
	case Qt::Key::Key_Left:
		if (val > this->minimum())
			--val;
		break;
	case Qt::Key_Right:
		if (val < this->maximum())
			++val;
		break;
	default:
		break;
	}

	this->setValue(val);
	emit this->sliderTriggered(val);
}

void Slider::keyPressEvent(QKeyEvent* event)
{
	event->ignore();
}

void Slider::wheelEvent(QWheelEvent* event)
{
	auto delta = event->delta();
	auto step = static_cast<int>(delta / 120.00);
	auto max = this->maximum();
	auto cur = this->value();
	auto val = cur + step;

	if (step > 0)
		this->setValue(val < max ? val : max);
	else
		this->setValue(val < 0 ? 0 : val);

	emit this->sliderTriggered(this->value());
}

void Slider::mouseTriggerEvent(QMouseEvent*& event)
{
	auto toDouble = [](int val)
		{
			return static_cast<double>(val);
		};

	auto pos = toDouble(event->pos().x());
	auto per = pos / toDouble(this->width());

	if (per > 1.0 || per < 0.0)
		return;

	auto max = toDouble(this->maximum());
	auto min = toDouble(this->minimum());

	auto val = static_cast<int>((max - min) * per);

	this->setValue(val);
	emit this->sliderTriggered(val);
}
