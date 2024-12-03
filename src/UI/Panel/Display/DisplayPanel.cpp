#include"UI/Data/Translator/Translator.hpp"
#include"UI/Data/StyleSheet.hpp"

#include"UI/Basic/Label.hpp"

#if QT_VERSION == QT_VERSION_CHECK(5, 15, 5)
#include<QRegExpValidator>
#else // QRegExpValidator is no longer supported since version 6.8
#include<QRegularExpression>
#include<QValidator>
#endif

#include<QGridLayout>
#include<QScrollArea>

#include"DisplayPanel.hpp"

using namespace UI;

void DisplayPanel::allocation()
{
#if QT_VERSION == QT_VERSION_CHECK(5, 15, 5)
	Validator = new QRegExpValidator(QRegExp("-?\\d*\\.\\d+"), this);
#else /*Matching positive floats*/
	Validator = new QRegularExpressionValidator(QRegularExpression("-?\\d*\\.\\d+"), this);
#endif
	Canvas = new QWidget(this);

	MainLayout = new QGridLayout(this);
	AreaLayout = new QGridLayout(this);
	Area = new QScrollArea(this);

	AspectRatio = new SliderEdit(Canvas, "AspectRatio");
	Brightness = new SliderEdit(Canvas, "Brightness");
	Saturation = new SliderEdit(Canvas, "Saturation");
	Contrast = new SliderEdit(Canvas, "Contrast");
	Panscan = new SliderEdit(Canvas, "Panscan");

	Rotate = new SliderEdit(Canvas, "Rotate");
	HAlign = new SliderEdit(Canvas, "HAlign");
	VAlign = new SliderEdit(Canvas, "VAlign");
	Gamma = new SliderEdit(Canvas, "Gamma");
	Hue = new SliderEdit(Canvas, "Hue");

	HFlip = new PushButton(this, "HFlip");
	VFlip = new PushButton(this, "VFlip");
}

void DisplayPanel::connection()
{
	this->editConnection();
	this->buttonConnection();
}

void DisplayPanel::initLayout()
{
	AreaLayout->addWidget(AspectRatio, 1, 1, 1, -1);
	AreaLayout->addWidget(Brightness, 2, 1, 1, -1);
	AreaLayout->addWidget(Saturation, 3, 1, 1, -1);
	AreaLayout->addWidget(Contrast, 4, 1, 1, -1);
	AreaLayout->addWidget(Panscan, 5, 1, 1, -1);
	AreaLayout->addWidget(Rotate, 6, 1, 1, -1);
	AreaLayout->addWidget(HAlign, 7, 1, 1, -1);
	AreaLayout->addWidget(VAlign, 8, 1, 1, -1);
	AreaLayout->addWidget(Gamma, 9, 1, 1, -1);
	AreaLayout->addWidget(Hue, 10, 1, 1, -1);

	AreaLayout->addWidget(HFlip, 11, 1, 1, 2);
	AreaLayout->addWidget(VFlip, 11, 3, 1, 2);

	Canvas->setLayout(AreaLayout);

	Area->setWidgetResizable(true);
	Area->setWidget(Canvas);

	MainLayout->addWidget(Area, 1, 1, -1, -1);
	this->setLayout(MainLayout);
}

void DisplayPanel::initialization()
{
	AspectRatio->setValidator(Validator);
	AspectRatio->setRange(-1, 7);

	Brightness->setValidator(Validator);
	Brightness->setRange(-100, 100);

	Saturation->setValidator(Validator);
	Saturation->setRange(-100, 100);

	Contrast->setValidator(Validator);
	Contrast->setRange(-100, 100);

	Panscan->setValidator(Validator);
	Panscan->setFactor(0.01);

	Rotate->setValidator(Validator);
	Rotate->setRange(0, 359);

	HAlign->setValidator(Validator);
	HAlign->setRange(-100, 100);
	HAlign->setFactor(0.01);

	VAlign->setValidator(Validator);
	VAlign->setRange(-100, 100);
	VAlign->setFactor(0.01);

	Gamma->setValidator(Validator);
	Gamma->setRange(-100, 100);

	Hue->setValidator(Validator);
	Hue->setRange(-100, 100);

	HFlip->setCheckable(true);
	VFlip->setCheckable(true);

	this->initLayout();
}

void DisplayPanel::editConnection()
{
	connect(AspectRatio, &SliderEdit::sendData, this, [&](double data) {
		emit this->aspectRatio(data);
		});
	connect(Brightness, &SliderEdit::sendData, this, [&](double data) {
		emit this->brightness(static_cast<Int>(data));
		});
	connect(Saturation, &SliderEdit::sendData, this, [&](double data) {
		emit this->saturation(static_cast<Int>(data));
		});
	connect(Contrast, &SliderEdit::sendData, this, [&](double data) {
		emit this->contrast(static_cast<Int>(data));
		});
	connect(Panscan, &SliderEdit::sendData, this, [&](double data) {
		emit this->panscan(data);
		});

	connect(Rotate, &SliderEdit::sendData, this, [&](double data) {
		emit this->rotate(static_cast<Int>(data));
		});
	connect(HAlign, &SliderEdit::sendData, this, [&](double data) {
		emit this->align(data, VAlign->value());
		});
	connect(VAlign, &SliderEdit::sendData, this, [&](double data) {
		emit this->align(HAlign->value(), data);
		});
	connect(Gamma, &SliderEdit::sendData, this, [&](double data) {
		emit this->gamma(static_cast<Int>(data));
		});
	connect(Hue, &SliderEdit::sendData, this, [&](double data) {
		emit this->hue(static_cast<Int>(data));
		});
}

void DisplayPanel::buttonConnection()
{
	connect(HFlip, &PushButton::clicked, this, [&](bool data) {
		emit this->flip(data, VFlip->isChecked());
		});
	connect(VFlip, &PushButton::clicked, this, [&](bool data) {
		emit this->flip(HFlip->isChecked(), data);
		});
}

void DisplayPanel::updateStyleSheet()
{
	StyleSheet::Set(this, "DisplayPanel");
}

void DisplayPanel::updateLanguage()
{
	auto text = [](const QString& name) { return Translator::Acquire("DisplayPanel", name); };

	AspectRatio->setText(text("AspectRatio"));
	Brightness->setText(text("Brightness"));
	Saturation->setText(text("Saturation"));
	Contrast->setText(text("Contrast"));
	Panscan->setText(text("Panscan"));

	Rotate->setText(text("Rotate"));
	HAlign->setText(text("HAlign"));
	VAlign->setText(text("VAlign"));
	Gamma->setText(text("Gamma"));
	Hue->setText(text("Hue"));

	HFlip->setText(text("HFlip"));
	VFlip->setText(text("VFlip"));
}
