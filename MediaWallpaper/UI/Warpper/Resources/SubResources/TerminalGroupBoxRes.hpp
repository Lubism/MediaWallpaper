#pragma once
#include<QString>

namespace UI
{
	namespace css
	{
		const QString TerminalGroupPath = "resources\\css\\terminalGroup\\";

		const QString TerminalGroupBox = TerminalGroupPath + "TerminalGroupBox.css";

		namespace terminalGroup
		{
			const QString AutobootBox = TerminalGroupPath + "comboBox\\AutobootBox.css";
			const QString PanelBox = TerminalGroupPath + "comboBox\\PanelBox.css";

			const QString AutobootLabel = TerminalGroupPath + "label\\AutobootLabel.css";
			const QString PanelLabel = TerminalGroupPath + "label\\PanelLabel.css";

			const QString UpdatePanelButton = TerminalGroupPath + "button\\UpdatePanelButton.css";
			const QString UpdatePanelLabel = TerminalGroupPath + "label\\UpdatePanelLabel.css";
		}
	}
}