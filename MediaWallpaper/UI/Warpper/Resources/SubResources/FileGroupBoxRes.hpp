#pragma once
#include<QString>

namespace UI
{
	namespace css
	{
		const QString FileGroupPath = "resources\\css\\fileGroup\\";

		const QString FileGroupBox = FileGroupPath + "FileGroupBox.css";

		namespace fileGroup
		{
			//==========================================================================
			//PushButton

			const QString RefreshDisplay = FileGroupPath + "button\\RefreshDisplay.css";

			const QString OpenPlaylist = FileGroupPath + "button\\OpenPlaylist.css";

			const QString SelectFolder = FileGroupPath + "button\\SelectFolder.css";

			const QString ClearInfo = FileGroupPath + "button\\ClearInfo.css";

			//==========================================================================
			//Others

			const QString PlaymodeBox = FileGroupPath + "comboBox\\PlaymodeBox.css";

			const QString FolderPath = FileGroupPath + "lineEdit\\FolderPath.css";

			const QString PlaymodeLabel = FileGroupPath + "label\\PlaymodeLabel.css";

			const QString ClearInfoWarn = FileGroupPath + "messageBox\\ClearInfoWarn.css";
		}
	}
}