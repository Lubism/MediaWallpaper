#pragma once
#include<QListWidget>
#include<QString>

#include<vector>

namespace UI
{
	class PlaylistPanel :public QListWidget
	{
		Q_OBJECT

	public:
		inline explicit PlaylistPanel(QWidget* parent = nullptr)
			:QListWidget(parent)
		{
			this->connection();
			this->initialization();
		}
	private:
		inline void connection();
		inline void initialization();
		inline void emitFileSelected(QListWidgetItem* item);
	public:
		void importList(const std::vector<QString>& playlist);
		void updateStyleSheet();

		inline void setCurrentIndex(int index);
		inline void clearInfo();
	protected:
		inline void showEvent(QShowEvent* event) override;
	signals:
		void fileSelected(int index);
	private:
		QListWidgetItem* Item = nullptr;
		int CurrentIndex = 0;
		size_t FileCount = 0;
	};

	inline void PlaylistPanel::connection()
	{
		connect(this, &QListWidget::itemDoubleClicked, this,
			&PlaylistPanel::emitFileSelected);
	}
	
	inline void PlaylistPanel::initialization()
	{
		this->setFocusPolicy(Qt::NoFocus);
		this->setWindowTitle("Playlist");
	}

	inline void PlaylistPanel::emitFileSelected(QListWidgetItem* item)
	{
		Item = item;
		CurrentIndex = this->row(item);
		emit this->fileSelected(CurrentIndex);
	}

	inline void PlaylistPanel::setCurrentIndex(int index)
	{
		if (index < 0 || index >= FileCount) {
			CurrentIndex = -1;
			Item = nullptr;
			return;
		}

		CurrentIndex = index;
		Item = this->item(index);
	}

	inline void PlaylistPanel::clearInfo()
	{
		CurrentIndex = FileCount = 0;
		Item = nullptr;

		this->clearSelection();
		this->clear();
	}

	inline void PlaylistPanel::showEvent(QShowEvent* event)
	{
		this->clearSelection();

		if (Item && CurrentIndex > -1)
		{
			this->scrollToBottom();
			this->scrollToItem(Item);

#if QT_VERSION == QT_VERSION_CHECK(5, 15, 5)
			this->setItemSelected(Item, true);
#else
			this->setCurrentItem(Item, QItemSelectionModel::Select);
#endif
		}

		QWidget::showEvent(event);
	}
}
