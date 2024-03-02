#pragma once
#include<QWidget>

class QGridLayout;

namespace UI
{
	class DirInfoWidget;
	class MessageBox;
	class PushButton;
	class LineEdit;
	class ComboBox;
	class Label;

	class FileWidget :public QWidget
	{
		using Int = long long;
		Q_OBJECT

	public:
		inline explicit FileWidget(QWidget* parent = nullptr)
			:QWidget(parent)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}

		virtual ~FileWidget() {}
	private:
		void allocation();
		void connection();
		void initLayout();
		void initialization();
		void selectDirectory();
	public:
		void setDirectoryPath(const QString& data);
		void setPlaymode(Int index);
		void updateStyleSheet();
		void updateLanguage();
	signals:
		void directorySelected(const QString& path);
		void playmode(Int index);

		void refreshDisplay();
		void clearInfo();
	private:
		PushButton* SelectDirectory = nullptr;
		PushButton* RefreshDisplay = nullptr;
		PushButton* ClearInfo = nullptr;

		MessageBox* ClearInfoWarn = nullptr;
		DirInfoWidget* DirInfo = nullptr;

		LineEdit* DirectoryPath = nullptr;
		ComboBox* PlaymodeBox = nullptr;
		Label* PlaymodeLabel = nullptr;

		QGridLayout* Layout = nullptr;
	};
}
