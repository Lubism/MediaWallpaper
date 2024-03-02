#pragma once
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

		inline void showup()
		{
			if (this->isMinimized())
			{
				if (this->isMaximized())
				{
					this->showMaximized();
				}
				else
				{
					this->showNormal();
				}
			}

			this->show();
		}

		inline virtual ~Widget() {}
	};
}
