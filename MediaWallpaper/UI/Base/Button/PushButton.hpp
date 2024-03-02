#pragma once
#include<QPushButton>

namespace UI
{
	class PushButton :public QPushButton
	{
	public:
		inline explicit PushButton(QWidget* parent = nullptr, const QString& text = "")
			:QPushButton(text, parent)
		{
			this->setFocusPolicy(Qt::NoFocus);
			this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		}

		inline virtual ~PushButton() {}
	};
}
