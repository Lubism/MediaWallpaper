#pragma once
#include"UI/Basic/GroupBox/GroupBox.hpp"

namespace UI
{
	class HorizontalSlider;
	class PushButton;
	class LineEdit;
	class Label;

	class BasicGroupBox :public GroupBox
	{
		Q_OBJECT

	public:
		inline explicit BasicGroupBox(QWidget* parent = nullptr, const int& screenIndex = 0)
			:GroupBox(parent, Converter::CH("»ù±¾"))
		{
			this->allocation();
			this->connection();
			this->initialization(screenIndex);
		}
	private:
		void allocation();
		void connection();
		void connection_slider();
		void connection_button();
		void connection_lineEdit();
		void initialization(const int& screenIndex);
		inline QString translateTime(long long num, long long den);
	public:
		void setPosition(double _position_, double _duration_);
		void setFileName(const QString& filename);
		void setVolume(double data);
		void setSpeed(double data);

		void setSubVisibility(bool data);
		void setPause(bool data);
		void setMute(bool data);
		void updateStyleSheet();
		inline void clearInfo();
	protected:
		void resizeEvent(QResizeEvent* event) override;
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
		HorizontalSlider* PositionSlider = nullptr;
		HorizontalSlider* VolumeSlider = nullptr;
		HorizontalSlider* SpeedSlider = nullptr;

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

		Label* VolumeLabel = nullptr;
		Label* SpeedLabel = nullptr;
		Label* DesktopID = nullptr;

		bool TimeFocused = false;
		double Position = 0.0;
	};

	inline QString BasicGroupBox::translateTime(long long num, long long den)
	{
		long long hh = 0, mm = 0, ss = 0;

		auto number = [](long long& value)
		{
			return ((value < 10) ? "0" : "") + QString::number(value);
		};

		auto split = [&](long long& value)
		{
			hh = value / 3600;
			mm = (value - hh * 3600) / 60;
			ss = value - hh * 3600 - mm * 60;
			return number(hh) + ":" + number(mm) + ":" + number(ss);
		};

		return split(num) + " / " + split(den);
	}

	inline void BasicGroupBox::clearInfo()
	{
		this->setPosition(0.0, 1.0);
		this->setVolume(100.0);
		this->setSpeed(1.0);

		this->setSubVisibility(true);
		this->setPause(false);
		this->setMute(false);

		this->setFileName("");
	}
}