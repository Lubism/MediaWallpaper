#pragma once
#include"UI/Basic/Font.hpp"
#include<QSlider>

namespace UI
{
	class Slider :public QSlider
	{
		Q_OBJECT

	public:
		inline explicit Slider(QWidget* parent = nullptr, int maxnum = 100)
			:QSlider(Qt::Horizontal, parent)
		{
			this->setMinimum(0);
			this->setMaximum(maxnum);
			this->setFocusPolicy(Qt::ClickFocus);
		}

		inline void setGeometry(const Converter& cvt,
			int x, int y, int width, int height)
		{
			QWidget::setGeometry(cvt.width(x), cvt.height(y),
				cvt.width(width), cvt.height(height));
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