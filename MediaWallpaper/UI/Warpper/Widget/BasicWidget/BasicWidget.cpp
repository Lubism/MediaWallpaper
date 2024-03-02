#include"UI/Warpper/Data/Translator/Translator.hpp"
#include"UI/Warpper/Data/StyleSheet.hpp"
#include"UI/Base/Slider/Slider.hpp"
#include<QGridLayout>

#include"BasicWidget.hpp"

using namespace UI;

void BasicWidget::allocation()
{
	VolumeDisplay = new LineEdit(this, "VolumeDisplay");
	SpeedDisplay = new LineEdit(this, "SpeedDisplay");
	TimeDisplay = new LineEdit(this, "TimeDisplay");
	FileName = new LineEdit(this);

	Subtitle = new PushButton(this, "Subtitle");
	Pause = new PushButton(this, "Pause");
	Mute = new PushButton(this, "Mute");
	Last = new PushButton(this, "Last");
	Next = new PushButton(this, "Next");
	Stop = new PushButton(this, "Stop");

	TimeSlider = new Slider(this, 1000);

	VolumeLabel = new Label(this, "VolumeLabel");
	SpeedLabel = new Label(this, "SpeedLabel");
	DesktopID = new Label(this, "DesktopID");

	Layout = new QGridLayout(this);
}

void BasicWidget::connection()
{
	this->connection_button();
	this->connection_lineEdit();
}

void BasicWidget::initLayout()
{
	Layout->addWidget(VolumeDisplay, 2, 6, 1, 1);
	Layout->addWidget(SpeedDisplay, 3, 6, 1, 1);
	Layout->addWidget(TimeDisplay, 2, 1, 1, 4);
	Layout->addWidget(FileName, 1, 1, 1, -1);

	Layout->addWidget(Subtitle, 4, 1, 1, 2);
	Layout->addWidget(Mute, 4, 3, 1, 2);

	Layout->addWidget(Pause, 5, 2, 1, 1);
	Layout->addWidget(Last, 5, 1, 1, 1);
	Layout->addWidget(Next, 5, 3, 1, 1);
	Layout->addWidget(Stop, 5, 4, 1, 1);

	Layout->addWidget(TimeSlider, 3, 1, 1, 4);

	Layout->addWidget(VolumeLabel, 2, 5, 1, 1);
	Layout->addWidget(SpeedLabel, 3, 5, 1, 1);
	Layout->addWidget(DesktopID, 4, 5, 2, 2);

	Layout->setContentsMargins(5, 5, 5, 5);
}

void BasicWidget::initialization()
{
	this->initLayout();
	this->updateLanguage();

	FileName->setNoFocus(true);
	FileName->setPlaceholderText("FileName");

	Mute->setCheckable(true);
	Pause->setCheckable(true);
	Subtitle->setCheckable(true);
}

void BasicWidget::connection_button()
{
	connect(Subtitle, &PushButton::clicked, this, [&](bool data) {emit this->subVisibility(!data); });
	connect(Pause, &PushButton::clicked, this, [&](bool data) {emit this->pause(data); });
	connect(Mute, &PushButton::clicked, this, [&](bool data) {emit this->mute(data); });

	connect(Last, &PushButton::clicked, this, [&](bool) {emit this->last(); });
	connect(Next, &PushButton::clicked, this, [&](bool) {emit this->next(); });
	connect(Stop, &PushButton::clicked, this, [&](bool) {emit this->stop(); });
}

void BasicWidget::connection_lineEdit()
{
	connect(VolumeDisplay, &LineEdit::textModified, this, [&](const QString& text) {emit this->volume(text.toDouble()); });

	connect(SpeedDisplay, &LineEdit::textModified, this, [&](const QString& text) {emit this->speed(text.toDouble()); });

	connect(TimeDisplay, &LineEdit::textModified, this, [&](const QString& text) {emit this->position(text.toDouble()); });
	connect(TimeDisplay, &LineEdit::occurFocus, this, [&]() {TimeDisplay->importText(QString::number(Position)); });
	connect(TimeSlider, &Slider::sliderTriggered, this, [&](int value) {emit this->position(value); });
}

void BasicWidget::updateStyleSheet()
{
	StyleSheet::Set(this, "BasicWidget");
}

void BasicWidget::updateLanguage()
{
	auto receive = [](const QString& name) {return Translator::Acquire("BasicGroup", name); };
	if (!Translator::TranslationAvaliable()) return;
	this->setWindowTitle(receive("Basic"));

	FileName->setPlaceholderText(receive("FileName"));

	Subtitle->setText(receive("Subtitle"));
	Pause->setText(receive("Pause"));
	Mute->setText(receive("Mute"));
	Last->setText(receive("Last"));
	Next->setText(receive("Next"));
	Stop->setText(receive("Stop"));

	VolumeLabel->setText(receive("Volume"));
	SpeedLabel->setText(receive("Speed"));

	DesktopID->setText(receive("Desktop") + QString::number(ScreenIndex));
}
