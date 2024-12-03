#pragma once
#include"UI/Basic/PushButton.hpp"
#include"UI/Basic/LineEdit.hpp"
#include"UI/Basic/Slider.hpp"
#include"UI/Basic/Widget.hpp"
#include"UI/Basic/Label.hpp"

class QGridLayout;
class QValidator;

namespace UI
{
	class PushButton;
	class LineEdit;
	class Slider;
	class Label;

	class BasicPanel : public Widget
	{
		Q_OBJECT

	public:
		inline explicit BasicPanel(QWidget* parent = nullptr)
			:Widget(parent)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}
	private:
		void allocation();
		void connection();
		void buttonConnection();
		void lineEditConnection();

		void initLayout();
		void initialization();
	public:
		inline void setTime(double duration, double position);

		inline void setMonitorID(const QString& value);
		inline void setFileName(const QString& value);
		inline void setVolume(double value);
		inline void setSpeed(double value);

		inline void setSubtitle(bool value);
		inline void setPause(bool value);
		inline void setMute(bool value);

		void updateStyleSheet();
		void updateLanguage();
	signals:
		void volume(double value);
		void speed(double value);
		void time(double value);

		void subtitle(bool value);
		void pause(bool value);
		void mute(bool value);

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
		Label* MonitorID = nullptr;

		QValidator* Validator = nullptr;
		QGridLayout* Layout = nullptr;
		QString DesktopPrefix = "";
	};

	inline void BasicPanel::setTime(double duration, double position)
	{
		auto preprocess = [](double& data) {return data < 0.0 ? 0.0 : data; };

		unsigned long long den = static_cast<unsigned long long>(preprocess(duration));
		unsigned long long num = static_cast<unsigned long long>(preprocess(position));

		auto cvt = [](unsigned long long& value)
			{
				QString ret;

				auto hh = value / 3600;
				auto mm = (value - hh * 3600) / 60;
				auto ss = value - hh * 3600 - mm * 60;

				auto h = (hh < 10 ? "0" : "") + QString::number(hh);
				auto m = (mm < 10 ? "0" : "") + QString::number(mm);
				auto s = (ss < 10 ? "0" : "") + QString::number(ss);

				ret = h + ":" + m + ":" + s;
				return ret;
			};

		TimeDisplay->setText(cvt(num) + " / " + cvt(den));
		TimeSlider->setMaximum(den);
		TimeSlider->setValue(num);
	}

	inline void BasicPanel::setMonitorID(const QString& value)
	{
		MonitorID->setText(DesktopPrefix + value);
	}

	inline void BasicPanel::setFileName(const QString& value)
	{
		FileName->setText(value);
	}
	inline void BasicPanel::setVolume(double value)
	{
		value = value < 0.0 ? 0.0 : value;
		VolumeDisplay->setText(QString::number(value));
	}
	inline void BasicPanel::setSpeed(double value)
	{
		value = value < 0.0 ? 0.0 : value;
		SpeedDisplay->setText(QString::number(value));
	}

	inline void BasicPanel::setSubtitle(bool value)
	{
		if (value == !Subtitle->isChecked())
			return;
		Subtitle->setChecked(!value);
	}
	inline void BasicPanel::setPause(bool value)
	{
		if (value == Pause->isChecked())
			return;
		Pause->setChecked(value);
	}
	inline void BasicPanel::setMute(bool value)
	{
		if (value == Mute->isChecked())
			return;
		Mute->setChecked(value);
	}
}
