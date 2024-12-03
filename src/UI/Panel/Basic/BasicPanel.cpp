#include"UI/Data/Translator/Translator.hpp"
#include"UI/Data/StyleSheet.hpp"

#if QT_VERSION == QT_VERSION_CHECK(5, 15, 5)
#include<QRegExpValidator>
#else // QRegExpValidator is no longer supported since version 6.8
#include<QRegularExpression>
#include<QValidator>
#endif

#include<QGridLayout>

#include"BasicPanel.hpp"

using namespace UI;

void BasicPanel::allocation()
{
	VolumeDisplay = new LineEdit(this, "VolumeDisplay");
	SpeedDisplay = new LineEdit(this, "SpeedDisplay");
	TimeDisplay = new LineEdit(this, "TimeDisplay");
	FileName = new LineEdit(this, "FileName");

	Subtitle = new PushButton(this, "Subtitle");
	Pause = new PushButton(this, "Pause");
	Mute = new PushButton(this, "Mute");
	Last = new PushButton(this, "Last");
	Next = new PushButton(this, "Next");
	Stop = new PushButton(this, "Stop");

	TimeSlider = new Slider(this, 1 << 16);

	VolumeLabel = new Label(this, "VolumeLabel");
	SpeedLabel = new Label(this, "SpeedLabel");
	MonitorID = new Label(this, "MonitorID");

#if QT_VERSION == QT_VERSION_CHECK(5, 15, 5)
	Validator = new QRegExpValidator(QRegExp("\\d*\\.\\d+"), this);
#else /*Matching positive floats*/
	Validator = new QRegularExpressionValidator(QRegularExpression("\\d*\\.\\d+"), this);
#endif

	Layout = new QGridLayout(this);
}

void BasicPanel::connection()
{
	connect(TimeSlider, &Slider::sliderTriggered, this, [&](int value) {
		emit this->time(value);
		});
	this->buttonConnection();
	this->lineEditConnection();
}

void BasicPanel::buttonConnection()
{
	connect(Subtitle, &PushButton::clicked, this, [&](bool value) {
		emit this->subtitle(!value);
		});
	connect(Pause, &PushButton::clicked, this, [&](bool value) {
		emit this->pause(value);
		});
	connect(Mute, &PushButton::clicked, this, [&](bool value) {
		emit this->mute(value);
		});

	connect(Last, &PushButton::clicked, this, [&](bool value) {
		emit this->last();
		});
	connect(Next, &PushButton::clicked, this, [&](bool value) {
		emit this->next();
		});
	connect(Stop, &PushButton::clicked, this, [&](bool value) {
		emit this->stop();
		});
}

void BasicPanel::lineEditConnection()
{
	connect(VolumeDisplay, &LineEdit::textModified, this, [&](const QString& text) {
		emit this->volume(text.toDouble());
		});
	connect(SpeedDisplay, &LineEdit::textModified, this, [&](const QString& text) {
		emit this->speed(text.toDouble());
		});

	connect(TimeDisplay, &LineEdit::textModified, this, [&](const QString& text) {
		emit this->time(text.toDouble());
		});
	connect(TimeDisplay, &LineEdit::mouseDoubleClicked, this, [&]() {
		TimeDisplay->setText(QString::number(TimeSlider->value()));
		});
}

void BasicPanel::initLayout()
{
	Layout->addWidget(VolumeDisplay, 2, 6, 1, 1);
	Layout->addWidget(SpeedDisplay, 3, 6, 1, 1);
	Layout->addWidget(TimeDisplay, 2, 1, 1, 4);
	Layout->addWidget(FileName, 1, 1, 1, -1);

	Layout->addWidget(Subtitle, 4, 1, 1, 2);
	Layout->addWidget(Pause, 5, 2, 1, 1);
	Layout->addWidget(Mute, 4, 3, 1, 2);
	Layout->addWidget(Last, 5, 1, 1, 1);
	Layout->addWidget(Next, 5, 3, 1, 1);
	Layout->addWidget(Stop, 5, 4, 1, 1);

	Layout->addWidget(TimeSlider, 3, 1, 1, 4);

	Layout->addWidget(VolumeLabel, 2, 5, 1, 1);
	Layout->addWidget(SpeedLabel, 3, 5, 1, 1);
	Layout->addWidget(MonitorID, 4, 5, 2, 2);

	Layout->setContentsMargins(5, 5, 5, 5);
}

void BasicPanel::initialization()
{
	this->setWindowTitle("Basic");
	this->initLayout();

	VolumeDisplay->setValidator(Validator);
	SpeedDisplay->setValidator(Validator);
	TimeDisplay->setValidator(Validator);

	FileName->setNoFocus(true);

	Subtitle->setCheckable(true);
	Pause->setCheckable(true);
	Mute->setCheckable(true);
}

void BasicPanel::updateStyleSheet()
{
	StyleSheet::Set(this, "BasicPanel");
}

void BasicPanel::updateLanguage()
{
	auto text = [](const QString& name) { return Translator::Acquire("BasicPanel", name); };

	FileName->setPlaceholderText(text("FileName"));

	VolumeLabel->setText(text("Volume"));
	SpeedLabel->setText(text("Speed"));
	DesktopPrefix = text("Monitor");

	Subtitle->setText(text("Subtitle"));
	Pause->setText(text("Pause"));
	Mute->setText(text("Mute"));
	Last->setText(text("Last"));
	Next->setText(text("Next"));
	Stop->setText(text("Stop"));
}
