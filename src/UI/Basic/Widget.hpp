#pragma once
#include<QWidget>

namespace UI
{
	class Widget :public QWidget
	{
	public:
		inline explicit Widget(QWidget* parent = nullptr,
			Qt::WindowFlags flags = Qt::Window)
			:QWidget(parent, flags)
		{
			this->setFocusPolicy(Qt::NoFocus);
		}
	public:
		inline virtual ~Widget() {}
	};
}
