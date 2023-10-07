#pragma once
#include"UI/Basic/Font/Font.hpp"
#include<QLabel>

namespace UI
{
	class Label :public QLabel
	{
		Q_OBJECT

	public:
		inline explicit Label(QWidget* parent = nullptr,
			const QString& text = "")
			:QLabel(text, parent)
		{
			this->setFocusPolicy(Qt::NoFocus);
			this->setAlignment(Qt::AlignCenter);

			this->setFrameShape(QFrame::Panel);
			this->setFrameShadow(QFrame::Sunken);
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

		inline virtual ~Label() {}
	};
}