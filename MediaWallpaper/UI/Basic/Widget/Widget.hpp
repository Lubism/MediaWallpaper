#pragma once
#include"UI/Basic/Font/Font.hpp"
#include<QWidget>

namespace UI
{
	class Widget :public QWidget
	{
		Q_OBJECT

	public:
		inline explicit Widget(QWidget* parent = nullptr,
			Qt::WindowFlags flags = 0)
			:QWidget(parent, flags)
		{
			this->setFocusPolicy(Qt::NoFocus);
		}

		inline void setGeometry(const Converter& cvt,
			int x, int y, int width, int height)
		{
			QWidget::setGeometry(cvt.width(x), cvt.height(y),
				cvt.width(width), cvt.height(height));
		}

		inline void setFont(const Converter& cvt,
			double num)
		{
			QWidget::setFont(Font(cvt, num,
				this->height()));
		}

		inline virtual ~Widget() {}
	};
}