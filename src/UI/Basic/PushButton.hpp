#pragma once
#include<QPushButton>

namespace UI
{
	class PushButton : public QPushButton
	{
	public:
		inline explicit PushButton(QWidget* parent = nullptr, const QString& text = "")
			:QPushButton(text, parent)
		{
			this->setSizePolicy(QSizePolicy::Preferred,
				QSizePolicy::Preferred);
			this->setFocusPolicy(Qt::NoFocus);
		}

		inline virtual ~PushButton() {}
	};
}
