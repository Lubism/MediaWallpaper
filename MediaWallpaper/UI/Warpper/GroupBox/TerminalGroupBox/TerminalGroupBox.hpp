#pragma once
#include"UI/Basic/GroupBox/GroupBox.hpp"

namespace UI
{
	class PushButton;
	class ComboBox;
	class Label;

	class TerminalGroupBox :public GroupBox
	{
		Q_OBJECT

	public:
		inline explicit TerminalGroupBox(QWidget* parent = nullptr, const int& screenCount = 1)
			:GroupBox(parent, Converter::CH("жу╤к"))
		{
			this->allocation();
			this->connection();
			this->initialization(screenCount);
		}
	private:
		void allocation();
		void connection();
		void initialization(const int& screenCount);
	public:
		void setAutoboot(bool data);
		void updateStyleSheet();
	protected:
		void resizeEvent(QResizeEvent* event) override;
	signals:
		void selectPanel(int index);
		void autoboot(bool data);
		void updatePanel();
	private:
		ComboBox* AutobootBox = nullptr;
		ComboBox* PanelBox = nullptr;

		Label* AutobootLabel = nullptr;
		Label* PanelLabel = nullptr;

		PushButton* UpdatePanelButton = nullptr;
		Label* UpdatePanelLabel = nullptr;
	};
}