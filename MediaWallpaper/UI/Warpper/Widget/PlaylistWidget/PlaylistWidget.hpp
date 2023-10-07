#pragma once
#include"UI/Basic/Widget/Widget.hpp"
#include<vector>

class QListWidgetItem;

namespace UI
{
	class ListWidget;

	class PlaylistWidget :public Widget
	{
		Q_OBJECT

	public:
		inline explicit PlaylistWidget(QWidget* parent = nullptr)
			:Widget(parent, Qt::Window)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}
	private:
		void allocation();
		void connection();
		void initialization();
	public:
		void importPlaylist(const std::vector<QString>& data);
		void setPlaylistIndex(int index);
		void clearPlaylist();
	protected:
		void resizeEvent(QResizeEvent* event) override;
		void closeEvent(QCloseEvent* event) override;
	signals:
		void fileSelected(int index, const QString& filename);
	private:
		QListWidgetItem* Item = nullptr;
		ListWidget* Display = nullptr;
		int CurrentIndex = 0;
	};
}
