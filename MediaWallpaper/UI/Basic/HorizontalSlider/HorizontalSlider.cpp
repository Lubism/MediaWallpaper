#include"HorizontalSlider.hpp"
#include<QMouseEvent>
#include<QWheelEvent>
#include<QKeyEvent>

using namespace UI;

void HorizontalSlider::mouseReleaseEvent(QMouseEvent* event)
{
	this->mouseTriggerEvent(event);
}

void HorizontalSlider::mousePressEvent(QMouseEvent* event)
{
	event->ignore();
}

void HorizontalSlider::mouseMoveEvent(QMouseEvent* event)
{
	this->mouseTriggerEvent(event);
}

void HorizontalSlider::keyReleaseEvent(QKeyEvent* event)
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

void HorizontalSlider::keyPressEvent(QKeyEvent* event)
{
	event->ignore();
}

void HorizontalSlider::wheelEvent(QWheelEvent* event)
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

void HorizontalSlider::mouseTriggerEvent(QMouseEvent*& event)
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
