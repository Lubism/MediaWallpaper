#pragma once
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
			this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		}

		inline virtual ~Label() {}
	};
}