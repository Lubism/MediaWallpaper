#pragma once
#include"UI/Basic/Font.hpp"
#include<QRadioButton>

namespace UI
{
	class RadioButton :public QRadioButton
	{
		Q_OBJECT

	public:
		inline explicit RadioButton(QWidget* parent = nullptr, const QString& text = "")
			:QRadioButton(text, parent)
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

		inline virtual ~RadioButton() {}
	};
}