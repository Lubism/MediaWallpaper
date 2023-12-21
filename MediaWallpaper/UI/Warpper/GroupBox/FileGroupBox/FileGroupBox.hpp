#pragma once
#include"UI/Basic/GroupBox.hpp"

namespace UI
{
	class PlaylistWidget;
	class MessageBox;
	class PushButton;
	class ComboBox;
	class LineEdit;
	class Label;

	class FileGroupBox :public GroupBox
	{
		Q_OBJECT

	public:
		inline explicit FileGroupBox(QWidget* parent = nullptr)
			:GroupBox(parent, Converter::CH("нд╪Ч"))
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
		void playlistSize(int& width, int& height);

		void setPlaylistIndex(int index);
		void updateStyleSheet();

		void setPlaylistSize(const int& width, const int& height);
		void setFolderPath(const QString& path);
		void setPlaymode(int data);
	protected:
		void resizeEvent(QResizeEvent* event) override;
	signals:
		void fileSelected(int index, const QString& filename);
		void folderSelected(const QString& data);

		void playmodeSelected(int data);
		void refreshDisplay();
		void clearInfo();
	private:
		PushButton* RefreshDisplay = nullptr;
		PushButton* OpenPlaylist = nullptr;
		PushButton* SelectFolder = nullptr;
		PushButton* ClearInfo = nullptr;

		ComboBox* PlaymodeBox = nullptr;
		LineEdit* FolderPath = nullptr;
		Label* PlaymodeLabel = nullptr;

		MessageBox* ClearInfoWarn = nullptr;
		PlaylistWidget* Playlist = nullptr;
	};
}