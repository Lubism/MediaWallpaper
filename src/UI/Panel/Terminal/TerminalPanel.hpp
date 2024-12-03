#pragma once
#include"UI/Basic/Widget.hpp"

class QGridLayout;

namespace UI
{
	class PushButton;
	class ComboBox;
	class Label;

	class TerminalPanel :public Widget
	{
		Q_OBJECT

	public:
		inline explicit TerminalPanel(QWidget* parent = nullptr)
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
		void doUpdateStyleSheet();
		void doUpdateLanguage();

		void setMonitor(int index);
		void readInfo();
	signals:
		void selectMonitor(int index);

		void updateStyleSheet();
		void updateLanguage();

		void updatePlaylist();
		void loadAllConfig();
	private:
		PushButton* UpdateStyleSheet = nullptr;
		PushButton* UpdatePlaylist = nullptr;
		PushButton* LoadAllConfig = nullptr;
		PushButton* AboutQt = nullptr;

		ComboBox* FontsizeComboBox = nullptr;
		ComboBox* StartupComboBox = nullptr;
		ComboBox* MonitorComboBox = nullptr;
		ComboBox* LangComboBox = nullptr;
		ComboBox* FontComboBox = nullptr;

		Label* FontsizeLabel = nullptr;
		Label* StartupLabel = nullptr;
		Label* MonitorLabel = nullptr;
		Label* LangLabel = nullptr;
		Label* FontLabel = nullptr;

		QGridLayout* Layout = nullptr;
	};
}
