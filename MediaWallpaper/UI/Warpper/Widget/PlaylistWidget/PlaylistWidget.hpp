#pragma once
#include<QListWidget>
#include<QWidget>

class QGridLayout;
class QListWidget;

namespace UI
{
	class PlaylistWidget :public QListWidget
	{
		using Int = long long;
		Q_OBJECT

	public:
		inline explicit PlaylistWidget(QWidget* parent = nullptr)
			:QListWidget(parent)
		{
			connect(this, &QListWidget::itemDoubleClicked, this,
				[&](QListWidgetItem* item)
				{
					CurrentIndex = this->row(item);
					emit this->fileSelected(CurrentIndex);
				},
				Qt::DirectConnection);

			this->setFocusPolicy(Qt::NoFocus);
		}

		virtual ~PlaylistWidget() {}
	public:
		inline void importList(const std::vector<QString>& data);
		inline void setCurrentIndex(Int index);
		inline void resetSelected();
		void updateStyleSheet();
		void updateLanguage();
	signals:
		void fileSelected(Int index);
	private:
		int CurrentIndex = 0;
		QListWidgetItem* Item = nullptr;
	};

	inline void PlaylistWidget::importList(const std::vector<QString>& data)
	{
		this->clear();
		Item = nullptr;
		for (auto& it : data)
		{
			this->addItem(it);
		}
	}

	inline void PlaylistWidget::setCurrentIndex(Int index)
	{
		CurrentIndex = index;
		Item = this->item(index);
	}

	inline void PlaylistWidget::resetSelected()
	{
		this->scrollToBottom();
		this->scrollToItem(Item);
		this->setCurrentRow(CurrentIndex);
	}
}
