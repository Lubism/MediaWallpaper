#pragma once
#include"UI/Base/Widget/Widget.hpp"

class QGridLayout;

namespace UI
{
	class PushButton;
	class ComboBox;
	class Label;

	class TerminalWidget :public Widget
	{
		using Int = long long;
		Q_OBJECT

	public:
		inline explicit TerminalWidget(QWidget* parent = nullptr, const Int& screenCount = 1)
			:Widget(parent, Qt::Window), ScreenCount(screenCount)
		{
			this->allocation();
			this->connection();
			this->initialzation();
		}

		virtual ~TerminalWidget() {}
	private:
		void allocation();
		void connection();
		void initLayout();
		void setFontInfo();
		void initialzation();
		void setAutobootFile(bool data);
	public:
		void setFont(QString& type, Int size);
		void setAutoboot(bool state);
		void updateLanguage();
		void readInfo();
		void saveInfo();
		void quit();
	protected:
		void closeEvent(QCloseEvent* event) override;
	signals:
		void refreshDisplay();
		void selectLanguage();
		void updateStyleSheet();
		void selectPanel(Int index);
	private:
		Int ScreenCount = 1;
		bool QuitState = false;
		QGridLayout* Layout = nullptr;
		
		Label* FontLabel = nullptr;
		Label* LangLabel = nullptr;
		Label* PanelLabel = nullptr;
		Label* AutobootLabel = nullptr;
		Label* FontsizeLabel = nullptr;

		ComboBox* FontComboBox = nullptr;
		ComboBox* LangComboBox = nullptr;
		ComboBox* PanelComboBox = nullptr;
		ComboBox* FontsizeComboBox = nullptr;
		ComboBox* AutobootComboBox = nullptr;

		PushButton* RefreshDisplay = nullptr;
		PushButton* UpdateStyleSheet = nullptr;
	};
}
