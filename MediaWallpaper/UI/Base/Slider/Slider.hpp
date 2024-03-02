#pragma once
#include<QSlider>

namespace UI
{
	class Slider :public QSlider
	{
		Q_OBJECT

	public:
		inline Slider(QWidget* parent = nullptr, int maximum = 100,
			Qt::Orientation orientation = Qt::Horizontal)
			:QSlider(orientation, parent)
		{
			this->setMinimum(0);
			this->setMaximum(maximum);
			this->setFocusPolicy(Qt::ClickFocus);
			this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		}
	protected:
		void mouseReleaseEvent(QMouseEvent* event) override;
		void mousePressEvent(QMouseEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;

		void keyReleaseEvent(QKeyEvent* event) override;
		void keyPressEvent(QKeyEvent* event) override;
		void wheelEvent(QWheelEvent* event) override;
	private:
		void mouseTriggerEvent(QMouseEvent*& event);
	signals:
		void sliderTriggered(int value);
	public:
		inline virtual ~Slider() {}
	};
}
