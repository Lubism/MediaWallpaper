#include"UI/Warpper/Data/ProgramInfo/ProgramInfo.hpp"
#include"UI/Warpper/Data/Translator/Translator.hpp"
#include"UI/Warpper/Data/StyleSheet.hpp"
#include"UI/Base/LineEdit/LineEdit.hpp"
#include"UI/Base/ComboBox/ComboBox.hpp"
#include"UI/Base/Button/PushButton.hpp"
#include"UI/Base/Label.hpp"
#include<QFontDatabase>
#include<QApplication>
#include<QGridLayout>
#include<QCloseEvent>
#include<QSettings>
#include<QFont>

#include"TerminalWidget.hpp"

using namespace UI;

void TerminalWidget::allocation()
{
	Layout = new QGridLayout(this);

	FontComboBox = new ComboBox(this);
	LangComboBox = new ComboBox(this);
	PanelComboBox = new ComboBox(this);
	AutobootComboBox = new ComboBox(this);
	FontsizeComboBox = new ComboBox(this);

	FontLabel = new Label(this, "FontLabel");
	LangLabel = new Label(this, "LangLabel");
	PanelLabel = new Label(this, "PanelLabel");
	AutobootLabel = new Label(this, "AutobootLabel");
	FontsizeLabel = new Label(this, "FontsizeLabel");

	RefreshDisplay = new PushButton(this, "UpdateDisplay");
	UpdateStyleSheet = new PushButton(this, "UpdateStyleSheet");
}

void TerminalWidget::connection()
{
	connect(FontComboBox, &ComboBox::itemSelected, this,
		[&](int) {this->setFontInfo(); });

	connect(LangComboBox, &ComboBox::itemSelected,
		this, [&](int index)
		{
			Translator::ReadTranslation(LangComboBox->itemText(index));
			emit this->selectLanguage();
		});

	connect(PanelComboBox, &ComboBox::itemSelected, this, [&](int index)
		{emit this->selectPanel(index); });

	connect(AutobootComboBox, &ComboBox::itemSelected,
		this, &TerminalWidget::setAutoboot);

	connect(FontsizeComboBox, &ComboBox::itemSelected, this,
		[&](int) {this->setFontInfo(); });

	connect(RefreshDisplay, &PushButton::clicked, this,
		[&](bool) {emit this->refreshDisplay(); });

	connect(UpdateStyleSheet, &PushButton::clicked, this,
		[&](bool)
		{
			StyleSheet::Set(this, "TerminalWidget");
			emit this->updateStyleSheet();
		});
}

void TerminalWidget::initLayout()
{
	Layout->addWidget(FontComboBox, 4, 2, 1, 1);
	Layout->addWidget(LangComboBox, 3, 2, 1, 1);
	Layout->addWidget(PanelComboBox, 1, 2, 1, 1);
	Layout->addWidget(FontsizeComboBox, 5, 2, 1, 1);
	Layout->addWidget(AutobootComboBox, 2, 2, 1, 1);

	Layout->addWidget(FontLabel, 4, 1, 1, 1);
	Layout->addWidget(LangLabel, 3, 1, 1, 1);
	Layout->addWidget(PanelLabel, 1, 1, 1, 1);
	Layout->addWidget(AutobootLabel, 2, 1, 1, 1);
	Layout->addWidget(FontsizeLabel, 5, 1, 1, 1);

	Layout->addWidget(RefreshDisplay, 6, 1, 1, 2);
	Layout->addWidget(UpdateStyleSheet, 7, 1, 1, 2);
}

void TerminalWidget::setFontInfo()
{
	auto size = FontsizeComboBox->currentText().toInt();
	auto type = FontComboBox->currentText();

	QApplication::setFont(QFont(type, size));
	this->updateStyleSheet();
}

void TerminalWidget::initialzation()
{
	this->initLayout();
	this->updateLanguage();
	this->setMinimumSize(320, 280);
	this->setWindowTitle("Terminal");
	auto fontList = QFontDatabase().families();
	auto langList = Translator::TranslationList();

	for (auto& it : fontList)
	{
		FontComboBox->addItem(it);
	}
	for (auto it = 0; it < ScreenCount; it++)
	{
		PanelComboBox->addItem(QString::number(it));
	}
	for (auto it = 10; it < 81; it++)
	{
		FontsizeComboBox->addItem(QString::number(it));
	}

	AutobootComboBox->addItem("No");
	AutobootComboBox->addItem("Yes");
	LangComboBox->addItems(langList);

	FontComboBox->setFocusPolicy(Qt::ClickFocus);
	LangComboBox->setFocusPolicy(Qt::ClickFocus);
	PanelComboBox->setFocusPolicy(Qt::ClickFocus);
	AutobootComboBox->setFocusPolicy(Qt::ClickFocus);
	FontsizeComboBox->setFocusPolicy(Qt::ClickFocus);
}

void TerminalWidget::setAutobootFile(bool state)
{
	if (state == false)
	{
		int no_use = std::remove("MediaWallpaper.bat");
		return;
	}

	QString name = QApplication::applicationName();
	const std::vector<QString> bat =
	{
		"@echo off",
		"\n",

		"cd /d %~dp0",
		"\n",

		"start \"\" \"" + name + ".exe\"",
		"\n",

		"exit"
	};
	QString input = "";
	for (const auto& it : bat)
		input += it;

	QFile file("MediaWallpaper.bat");
	file.open(QIODevice::WriteOnly | QIODevice::Truncate);

	file.write(input.toLocal8Bit());
	file.close();
}

void TerminalWidget::setFont(QString& type, Int size)
{
	QApplication::setFont(QFont(type, size));
	int index = 0;

	index = FontsizeComboBox->findText(QString::number(size));
	FontsizeComboBox->setCurrentIndex(index);

	index = FontComboBox->findText(type);
	FontComboBox->setCurrentIndex(index);
}

void TerminalWidget::setCurrentPanel(Int index)
{
	PanelComboBox->setCurrentIndex(index);
}

void TerminalWidget::setAutoboot(bool state)
{
	const QString regPath = "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	std::unique_ptr<QSettings> Setting(new QSettings(regPath, QSettings::NativeFormat));
	QString path = "\"" + QApplication::applicationDirPath().replace("/", "\\");
	path += "\\MediaWallpaper.bat\"";

	QString name = QApplication::applicationName();
	this->setAutobootFile(state);
	if (state == true)
	{
		Setting->setValue(name, path);
		return;
	}

	Setting->remove(name);
}

void TerminalWidget::updateLanguage()
{
	auto acquire = [](const QString& name) {return Translator::Acquire("TerminalGroup", name); };
	if (!Translator::TranslationAvaliable()) return;
	this->setWindowTitle(acquire("Terminal"));
	QString storage = "";

	storage = acquire("Desktop");
	for (auto it = 0LL; it < ScreenCount; it++)
	{
		PanelComboBox->setItemText(it, storage +
			QString::number(it));
	}

	AutobootComboBox->setItemText(0, acquire("No"));
	AutobootComboBox->setItemText(1, acquire("Yes"));

	FontLabel->setText(acquire("Font"));
	LangLabel->setText(acquire("Lang"));
	PanelLabel->setText(acquire("Panel"));
	AutobootLabel->setText(acquire("Autoboot"));
	FontsizeLabel->setText(acquire("Fontsize"));

	RefreshDisplay->setText(acquire("RefreshDisplay"));
	UpdateStyleSheet->setText(acquire("UpdateStyleSheet"));
}

void TerminalWidget::readInfo()
{
	auto acquire = [](const QString& name) {return ProgramInfo::Acquire("Terminal", name); };

	auto width = acquire("Width").toInt();
	auto height = acquire("Height").toInt();

	auto lang = acquire("Lang");

	auto type = acquire("Font");
	auto size = acquire("Fontsize").toInt();
	auto autoboot = acquire("Autoboot").toInt();

	Translator::ReadTranslation(lang.isEmpty() ? (lang = "en") : lang);
	if (type.isEmpty()) type = "Comic Sans MS";
	if (size == 0) size = 12;

	AutobootComboBox->setCurrentIndex(autoboot);
	auto index = LangComboBox->findText(lang);
	LangComboBox->setCurrentIndex(index);
	emit this->selectLanguage();
	this->setAutoboot(autoboot);

	this->setFont(type, size);
	this->resize(width, height);
	this->setAutoboot(autoboot);
}

void TerminalWidget::saveInfo()
{
	auto& font = this->font();
	auto windowSize = this->size();
	auto apply = [](const QString& name, const QString& value)
		{
			ProgramInfo::Apply("Terminal", name, value);
		};

	apply("Font", font.family());
	apply("Fontsize", QString::number(font.pointSize()));
	apply("Autoboot", QString::number(AutobootComboBox->currentIndex()));

	apply("Lang", LangComboBox->currentText());
	apply("Width", QString::number(windowSize.width()));
	apply("Height", QString::number(windowSize.height()));
}

void TerminalWidget::quit()
{
	QuitState = true;
	this->close();
}

void TerminalWidget::closeEvent(QCloseEvent* event)
{
	if (!QuitState)
	{
		event->ignore();
		this->hide();
		return;
	}

	event->accept();
}
