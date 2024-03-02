#pragma once
#include"UI/Base/LineEdit/LineEdit.hpp"
#include"UI/Base/Button/PushButton.hpp"
#include"UI/Base/Slider/Slider.hpp"
#include"UI/Base/Label.hpp"
#include<QWidget>

class QGridLayout;

namespace UI
{
	class PushButton;
	class LineEdit;
	class Slider;
	class Label;

	class BasicWidget :public QWidget
	{
		using Int = long long;
		Q_OBJECT

	public:
		inline BasicWidget(QWidget* parent = nullptr, const Int& desktopID = 0)
			:QWidget(parent), ScreenIndex(desktopID)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}

		virtual ~BasicWidget() {}
	private:
		void allocation();
		void connection();
		void initLayout();
		void initialization();
		void connection_button();
		void connection_lineEdit();
		inline QString translateTime(Int num, Int den);
	public:
		inline void setVolume(double data) { VolumeDisplay->setText(QString::number(data)); }
		inline void setSpeed(double data) { SpeedDisplay->setText(QString::number(data)); }
		inline void setFileName(const QString& data) { FileName->setText(data); }
		inline void setPosition(double num, double den);

		inline void setSubVisibility(bool data) { Subtitle->setChecked(!data); }
		inline void setPause(bool data) { Pause->setChecked(data); }
		inline void setMute(bool data) { Mute->setChecked(data); }
		void updateStyleSheet();
		void updateLanguage();
	signals:
		void position(double data);
		void volume(double data);
		void speed(double data);

		void subVisibility(bool data);
		void pause(bool data);
		void mute(bool data);

		void last();
		void next();
		void stop();
	private:
		LineEdit* VolumeDisplay = nullptr;
		LineEdit* SpeedDisplay = nullptr;
		LineEdit* TimeDisplay = nullptr;
		LineEdit* FileName = nullptr;

		PushButton* Subtitle = nullptr;
		PushButton* Pause = nullptr;
		PushButton* Mute = nullptr;
		PushButton* Last = nullptr;
		PushButton* Next = nullptr;
		PushButton* Stop = nullptr;

		Slider* TimeSlider = nullptr;

		Label* VolumeLabel = nullptr;
		Label* SpeedLabel = nullptr;
		Label* DesktopID = nullptr;

		QGridLayout* Layout = nullptr;
		Int ScreenIndex = 0;
		Int Position = 0;
		Int Duration = 0;
	};

	inline QString BasicWidget::translateTime(Int num, Int den)
	{
		Int hh = 0, mm = 0, ss = 0;
		Position = num;
		Duration = den;

		auto number = [](Int& value)
		{
			return ((value < 10) ? "0" : "") + QString::number(value);
		};

		auto split = [&](Int& value)
		{
			hh = value / 3600;
			mm = (value - hh * 3600) / 60;
			ss = value - hh * 3600 - mm * 60;
			return number(hh) + ":" + number(mm) + ":" + number(ss);
		};

		return split(num) + " / " + split(den);
	}

	inline void BasicWidget::setPosition(double num, double den)
	{
		TimeDisplay->setText(this->translateTime(num, den));
		TimeSlider->setMaximum(den);
		TimeSlider->setValue(num);
	}
}
