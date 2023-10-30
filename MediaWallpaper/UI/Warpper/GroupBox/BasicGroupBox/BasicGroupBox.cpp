#include"UI/Basic/HorizontalSlider/HorizontalSlider.hpp"
#include"UI/Warpper/Resources/Resources.hpp"
#include"UI/Basic/PushButton/PushButton.hpp"
#include"UI/Basic/LineEdit/LineEdit.hpp"
#include"UI/Basic/Label/Label.hpp"
#include"BasicGroupBox.hpp"
#include<QResizeEvent>

using namespace UI;

void BasicGroupBox::allocation()
{
	PositionSlider = new HorizontalSlider(this);
	VolumeSlider = new HorizontalSlider(this);
	SpeedSlider = new HorizontalSlider(this);

	VolumeDisplay = new LineEdit(this);
	SpeedDisplay = new LineEdit(this);
	TimeDisplay = new LineEdit(this);
	FileName = new LineEdit(this);

	Subtitle = new PushButton(this);
	Pause = new PushButton(this);
	Mute = new PushButton(this);
	Last = new PushButton(this);
	Next = new PushButton(this);
	Stop = new PushButton(this);

	VolumeLabel = new Label(this);
	SpeedLabel = new Label(this);
	DesktopID = new Label(this);
}

void BasicGroupBox::connection()
{
	this->connection_slider();

	this->connection_button();

	this->connection_lineEdit();
}

void BasicGroupBox::connection_slider()
{
	connect(PositionSlider, &HorizontalSlider::sliderTriggered, this,
		[&](int value) {emit this->position(value); });
	connect(VolumeSlider, &HorizontalSlider::sliderTriggered, this,
		[&](int value)
		{
			VolumeDisplay->setText(QString::number(value));
			emit this->volume(value);
		});
	connect(SpeedSlider, &HorizontalSlider::sliderTriggered, this,
		[&](int value)
		{
			SpeedDisplay->setText(QString::number(value * 0.1));
			emit this->speed(value * 0.1);
		});
}

void BasicGroupBox::connection_button()
{
	connect(Subtitle, &PushButton::toggled, this,
		[&](bool checked)
		{
			emit this->subVisibility(!checked);
		});
	connect(Pause, &PushButton::toggled, this,
		[&](bool checked)
		{
			if (Pause->isChecked())
				Pause->setText(QString::fromUtf8("\342\226\266"));
			else
				Pause->setText("II");

			emit this->pause(checked);
		});
	connect(Mute, &PushButton::toggled, this,
		[&](bool checked)
		{
			emit this->mute(checked);
		});
	connect(Last, &PushButton::clicked, this,
		[&]()
		{
			emit this->last();
		});
	connect(Next, &PushButton::clicked, this,
		[&]()
		{
			emit this->next();
		});
	connect(Stop, &PushButton::clicked, this,
		[&]()
		{
			emit this->stop();
		});
}

void BasicGroupBox::connection_lineEdit()
{
	connect(VolumeDisplay, &LineEdit::textChanged, this,
		[&](const QString& text)
		{
			if (text.isEmpty()) VolumeDisplay->setText("0");
		});
	connect(VolumeDisplay, &LineEdit::textModified, this,
		[&](const QString& text)
		{
			double value = text.toDouble();

			emit this->volume(value);
			VolumeSlider->setValue(value);
			VolumeDisplay->setText(QString::number(value));
		});
	connect(VolumeDisplay, &LineEdit::lostFocus,
		this, [&]()
		{
			VolumeDisplay->setText(QString::number(
				VolumeSlider->value()));
		});

	connect(SpeedDisplay, &LineEdit::textChanged, this,
		[&](const QString& text)
		{
			if (text.isEmpty()) SpeedDisplay->setText("0");
		});
	connect(SpeedDisplay, &LineEdit::textModified, this,
		[&](const QString& text)
		{
			double value = text.toDouble();

			emit this->speed(value);
			SpeedSlider->setValue(value * 10);
			SpeedDisplay->setText(QString::number(value));
		});
	connect(SpeedDisplay, &LineEdit::lostFocus,
		this, [&]()
		{
			SpeedDisplay->setText(QString::number(
				SpeedSlider->value() / 10.0));
		});

	connect(TimeDisplay, &LineEdit::mouseDoubleClicked,
		this, [&]()
		{
			TimeFocused = true;
			TimeDisplay->setText(QString::number(static_cast<long long>(Position)));
		});
	connect(TimeDisplay, &LineEdit::textChanged, this,
		[&](const QString& text)
		{
			if (text.isEmpty() == true && TimeFocused == false)
				TimeDisplay->setText("00:00:00 / 00:00:00");
		});
	connect(TimeDisplay, &LineEdit::textModified, this,
		[&](const QString& text)
		{
			emit this->position(text.toDouble());
			TimeFocused = false;
		});
	connect(TimeDisplay, &LineEdit::lostFocus, this,
		[&]() {TimeFocused = false; });

	connect(FileName, &LineEdit::textChanged, this,
		[&](const QString& text)
		{
			if (text.isEmpty() == true) FileName->setText(
				Converter::CH("当前没有播放"));
		});
}

void BasicGroupBox::initialization(const int& screenIndex)
{
	VolumeSlider->setValue(100);
	SpeedSlider->setValue(10);

	VolumeDisplay->setText(Converter::CH("100"));
	SpeedDisplay->setText(Converter::CH("1"));
	TimeDisplay->setText(Converter::CH(
		"00:00:00 / 00:00:00"));
	FileName->setText(Converter::CH(
		"当前无播放"));

	Subtitle->setText(Converter::CH("关闭字幕"));
	Pause->setText(Converter::CH("II"));
	Mute->setText(Converter::CH("关闭音频"));
	Last->setText(QString::fromUtf8("I\342\227\200"));
	Next->setText(QString::fromUtf8("\342\226\266I"));
	Stop->setText(QString::fromUtf8("\342\227\217"));

	VolumeLabel->setText(Converter::CH("音量"));
	SpeedLabel->setText(Converter::CH("速度"));
	DesktopID->setText(Converter::CH("显示器ID: ")
		+ QString::number(screenIndex));

	Subtitle->setCheckable(true);
	FileName->setNoFocus(true);
	Pause->setCheckable(true);
	Mute->setCheckable(true);

	this->updateStyleSheet();
}

void BasicGroupBox::setPosition(double _position_, double _duration_)
{
	QString str = this->translateTime(_position_, _duration_);
	PositionSlider->setMaximum(_duration_);
	PositionSlider->setValue(_position_);
	if (TimeFocused == true) return;
	TimeDisplay->setText(str);
	Position = _position_;
}

void BasicGroupBox::setFileName(const QString& filename)
{
	FileName->setText(filename);
}

void BasicGroupBox::setVolume(double data)
{
	VolumeDisplay->setText(QString::number(data));
	VolumeSlider->setValue(data);
}

void BasicGroupBox::setSpeed(double data)
{
	SpeedDisplay->setText(QString::number(data));
	SpeedSlider->setValue(data * 10.0);
}

void BasicGroupBox::setSubVisibility(bool data)
{
	Subtitle->setChecked(!data);
}

void BasicGroupBox::setPause(bool data)
{
	Pause->setChecked(data);
}

void BasicGroupBox::setMute(bool data)
{
	Mute->setChecked(data);
}

void BasicGroupBox::updateStyleSheet()
{
	css::Setter(css::basicGroup::PositionSlider, PositionSlider);
	css::Setter(css::basicGroup::VolumeSlider, VolumeSlider);
	css::Setter(css::basicGroup::SpeedSlider, SpeedSlider);

	css::Setter(css::basicGroup::VolumeDisplay, VolumeDisplay);
	css::Setter(css::basicGroup::SpeedDisplay, SpeedDisplay);
	css::Setter(css::basicGroup::TimeDisplay, TimeDisplay);
	css::Setter(css::basicGroup::FileName, FileName);

	css::Setter(css::basicGroup::Subtitle, Subtitle);
	css::Setter(css::basicGroup::Pause, Pause);
	css::Setter(css::basicGroup::Mute, Mute);
	css::Setter(css::basicGroup::Last, Last);
	css::Setter(css::basicGroup::Next, Next);
	css::Setter(css::basicGroup::Stop, Stop);

	css::Setter(css::basicGroup::VolumeLabel, VolumeLabel);
	css::Setter(css::basicGroup::SpeedLabel, SpeedLabel);
	css::Setter(css::basicGroup::DesktopID, DesktopID);

	css::Setter(css::BasicGroupBox, this);
}

void BasicGroupBox::resizeEvent(QResizeEvent* event)
{
	Converter cvt(390, 230, event);
	GroupBox::resizeEvent(event);

	PositionSlider->setGeometry(cvt, 10, 70, 370, 30);
	VolumeSlider->setGeometry(cvt, 270, 110, 60, 30);
	SpeedSlider->setGeometry(cvt, 270, 140, 60, 30);

	VolumeDisplay->setGeometry(cvt, 340, 110, 40, 30);
	SpeedDisplay->setGeometry(cvt, 340, 140, 40, 30);
	TimeDisplay->setGeometry(cvt, 10, 110, 190, 30);
	FileName->setGeometry(cvt, 10, 30, 370, 30);
	
	Subtitle->setGeometry(cvt, 10, 150, 90, 20);
	Pause->setGeometry(cvt, 60, 180, 40, 40);
	Mute->setGeometry(cvt, 110, 150, 90, 20);
	Last->setGeometry(cvt, 10, 180, 40, 40);
	Next->setGeometry(cvt, 110, 180, 40, 40);
	Stop->setGeometry(cvt, 160, 180, 40, 40);

	VolumeLabel->setGeometry(cvt, 220, 110, 40, 30);
	SpeedLabel->setGeometry(cvt, 220, 140, 40, 30);
	DesktopID->setGeometry(cvt, 220, 180, 160, 40);

	VolumeDisplay->setFont(cvt, 12);
	SpeedDisplay->setFont(cvt, 12);
	TimeDisplay->setFont(cvt, 12);
	FileName->setFont(cvt, 14);

	Subtitle->setFont(cvt, 12);
	Pause->setFont(cvt, 24);
	Mute->setFont(cvt, 12);
	Last->setFont(cvt, 24);
	Next->setFont(cvt, 24);
	Stop->setFont(cvt, 20);

	VolumeLabel->setFont(cvt, 12);
	SpeedLabel->setFont(cvt, 12);
	DesktopID->setFont(cvt, 16);

	this->setFont(cvt, 16);
}
