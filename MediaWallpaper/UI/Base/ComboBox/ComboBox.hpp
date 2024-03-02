#pragma once
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
					emit this->itemSelected(index);
				});

			this->setEditable(true);
			this->setMaxVisibleItems(10);
			this->setFocusPolicy(Qt::NoFocus);
			this->setSizeAdjustPolicy(QComboBox::AdjustToContents);
		}

		virtual ~ComboBox() {}
	protected:
		void wheelEvent(QWheelEvent* event) override;
	signals:
		void itemSelected(int index);
	};
}
