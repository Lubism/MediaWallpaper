#pragma once
#include<QFileInfo>
#include<QFrame>
#include<vector>

class QGridLayout;
class QListWidget;

namespace UI
{
	class PushButton;
	class Label;

	class DirInfoWidget :public QFrame
	{
		Q_OBJECT

	public:
		inline DirInfoWidget(QWidget* parent = nullptr)
			:QFrame(parent)
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
		void importDirList(const QFileInfoList& dirList);
	public:
		void importDirectory(const QString& path);
		void updateStyleSheet();
		void updateLanguage();
	private:
		QGridLayout* Layout = nullptr;
		QListWidget* List = nullptr;
		PushButton* Back = nullptr;
		Label* Name = nullptr;

		std::vector<QString> DirStack;
		QString CurrentDir = "";
	};
}
