#pragma once
#include"UI/Basic/Font/Font.hpp"
#include<QStackedWidget>

namespace UI
{
	class StackedWidget :public QStackedWidget
	{
		Q_OBJECT

	public:
		inline explicit StackedWidget(QWidget* parent = nullptr)
			:QStackedWidget(parent)
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

		inline virtual ~StackedWidget() {}
	};
}