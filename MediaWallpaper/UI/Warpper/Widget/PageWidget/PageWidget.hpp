#pragma once
#include<QTabWidget>

namespace UI
{
	class PlaylistWidget;
	class BasicWidget;
	class MediaWidget;
	class FileWidget;

	class PageWidget :public QTabWidget
	{
		using Int = long long;
		Q_OBJECT

	public:
		inline explicit PageWidget(QWidget* parent = nullptr, const Int& desktopID = 0)
			:QTabWidget(parent), DesktopID(desktopID)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}

		virtual ~PageWidget() {}
	private:
		void allocation();
		void connection();
		void initLayout();
		void initialization();

		void connection_file();
		void connection_basic();
		void connection_media();
		void connection_playlist();
	public:
		void updateStyleSheet();
		void updateLanguage();
		void refreshDisplay();
		void setMediaInfo();
		bool readInfo();
		void saveInfo();
	private:
		PlaylistWidget* Playlist = nullptr;
		BasicWidget* Basic = nullptr;
		MediaWidget* Media = nullptr;
		FileWidget* File = nullptr;
		bool InfoLoadState = false;
		Int DesktopID = 0;
	};
}
