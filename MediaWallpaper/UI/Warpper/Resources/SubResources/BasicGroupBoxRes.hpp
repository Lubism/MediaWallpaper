#pragma once
#include<QString>

namespace UI
{
	namespace css
	{
		const QString BasicGroupPath = "resources\\css\\basicGroup\\";

		const QString BasicGroupBox = BasicGroupPath + "BasicGroupBox.css";

		namespace basicGroup
		{
			//==========================================================================
			//Slider

			const QString PositionSlider = BasicGroupPath + "slider\\PositionSlider.css";

			const QString VolumeSlider = BasicGroupPath + "slider\\VolumeSlider.css";

			const QString SpeedSlider = BasicGroupPath + "slider\\SpeedSlider.css";

			//==========================================================================
			//LineEdit

			const QString VolumeDisplay = BasicGroupPath + "lineEdit\\VolumeDisplay.css";

			const QString SpeedDisplay = BasicGroupPath + "lineEdit\\SpeedDisplay.css";

			const QString TimeDisplay = BasicGroupPath + "lineEdit\\TimeDisplay.css";

			const QString FileName = BasicGroupPath + "lineEdit\\FileName.css";

			//==========================================================================
			//PushButton

			const QString Subtitle = BasicGroupPath + "button\\Subtitle.css";

			const QString Pause = BasicGroupPath + "button\\Pause.css";

			const QString Mute = BasicGroupPath + "button\\Mute.css";

			const QString Last = BasicGroupPath + "button\\Last.css";

			const QString Next = BasicGroupPath + "button\\Next.css";

			const QString Stop = BasicGroupPath + "button\\Stop.css";

			//==========================================================================
			//Label

			const QString VolumeLabel = BasicGroupPath + "label\\VolumeLabel.css";

			const QString SpeedLabel = BasicGroupPath + "label\\SpeedLabel.css";

			const QString DesktopID = BasicGroupPath + "label\\DesktopID.css";
		}
	}
}