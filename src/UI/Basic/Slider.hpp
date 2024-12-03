#pragma once
#include<QMouseEvent>
#include<QWheelEvent>
#include<QKeyEvent>
#include<QSlider>

namespace UI
{
	class Slider :public QSlider
	{
		Q_OBJECT

	public:
		inline explicit Slider(QWidget* parent = nullptr, int maximum = 100,
			Qt::Orientation orientation = Qt::Horizontal)
			:QSlider(orientation, parent)
		{
			this->setMinimum(0);
			this->setMaximum(maximum);
			this->setFocusPolicy(Qt::NoFocus);
			this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		}
	protected:
		inline void mouseReleaseEvent(QMouseEvent* event) override
		{
			this->mouseTriggerEvent(event);
			OnFocus = false;
		}

		inline void mousePressEvent(QMouseEvent* event) override
		{
			event->ignore();
			OnFocus = true;
		}

		inline void mouseMoveEvent(QMouseEvent* event) override
		{
			this->mouseTriggerEvent(event);
		}

		inline void keyReleaseEvent(QKeyEvent* event) override
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

		inline void keyPressEvent(QKeyEvent* event) override
		{
			event->ignore();
		}

		inline void wheelEvent(QWheelEvent* event) override
		{
			auto delta = event->angleDelta().y();
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
	private:
		inline void mouseTriggerEvent(QMouseEvent*& event)
		{
			if (!OnFocus) return;
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

			auto val = static_cast<int>((max - min) * per) + min;

			this->setValue(val);
			emit this->sliderTriggered(val);
		}
	signals:
		void sliderTriggered(int value);
	public:
		inline virtual ~Slider() {}
	private:
		bool OnFocus = false;
	};
}
