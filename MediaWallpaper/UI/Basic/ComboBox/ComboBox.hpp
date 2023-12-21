#pragma once
#include"UI/Basic/Font.hpp"
#include<QComboBox>

namespace UI
{
	class ComboBox :public QComboBox
	{
		Q_OBJECT

	public:
		inline explicit ComboBox(QWidget* parent = nullptr)
			:QComboBox(parent)
		{
			connect(this, static_cast<void (QComboBox::*)(int)>(
				&QComboBox::activated), this, [&](int index)
				{
					emit this->itemSelected(index);
				});
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
	protected:
		void wheelEvent(QWheelEvent* event) override;
	signals:
		void itemSelected(int index);
	};
}