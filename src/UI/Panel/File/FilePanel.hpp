#pragma once
#include"UI/Basic/PushButton.hpp"
#include"UI/Basic/ComboBox.hpp"
#include"UI/Basic/LineEdit.hpp"
#include"UI/Basic/Widget.hpp"

class QGridLayout;

namespace UI
{
	class PushButton;
	class MessageBox;
	class ComboBox;
	class LineEdit;
	class Label;

	class FilePanel :public Widget
	{
		Q_OBJECT

	public:
		inline explicit FilePanel(QWidget* parent = nullptr)
			:Widget(parent)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}
	private:
		void allocation();
		void connection();
		void initLayout();
		void initialization();
	public:
		inline void setDirectory(const QString& value);
		inline void setAtFullscreen(int value);
		inline void setPlaymode(int value);
		inline void setAtFocus(int value);

		void updateStyleSheet();
		void updateLanguage();
	signals:
		void directorySelected(const QString& path);
		void atFullscreen(int mode);
		void playmode(int mode);
		void atFocus(int mode);

		void updatePlaylist();
		void loadConfig();

		void clearInfo();
	private:
		PushButton* SelectDirectory = nullptr;
		PushButton* UpdatePlaylist = nullptr;
		PushButton* LoadConfig = nullptr;
		PushButton* ClearInfo = nullptr;

		MessageBox* ClearInfoWarn = nullptr;
		LineEdit* DirectoryPath = nullptr;

		ComboBox* AtFullscreenBox = nullptr;
		Label* AtFullscreenLabel = nullptr;

		ComboBox* PlaymodeBox = nullptr;
		Label* PlaymodeLabel = nullptr;

		ComboBox* AtFocusBox = nullptr;
		Label* AtFocusLabel = nullptr;

		QGridLayout* Layout = nullptr;
	};

	inline void FilePanel::setDirectory(const QString& value)
	{
		DirectoryPath->setText(value);
	}

	inline void FilePanel::setAtFullscreen(int value)
	{
		if (value < 0 || value == AtFullscreenBox->currentIndex())
			return;
		AtFullscreenBox->setCurrentIndex(value);
	}

	inline void FilePanel::setPlaymode(int value)
	{
		if (value < 0 || value == PlaymodeBox->currentIndex())
			return;
		PlaymodeBox->setCurrentIndex(value);
	}

	inline void FilePanel::setAtFocus(int value)
	{
		if (value < 0 || value == AtFocusBox->currentIndex())
			return;
		AtFocusBox->setCurrentIndex(value);
	}
}
