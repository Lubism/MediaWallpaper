#pragma once
#include<QWheelEvent>
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
			this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
			connect(this, static_cast<void (QComboBox::*)(int)>(
				&QComboBox::activated), this, [&](int index)
				{
					this->clearFocus();
					emit this->itemSelected(index);
				});

			this->setEditable(true);
			this->setMaxVisibleItems(10);
			this->setFocusPolicy(Qt::NoFocus);
			this->setSizeAdjustPolicy(QComboBox::AdjustToContents);
		}

		virtual ~ComboBox() {}
	protected:
        inline void wheelEvent(QWheelEvent* event) override
        {
            event->ignore();
        }
    signals:
		void itemSelected(int index);
	};
}
