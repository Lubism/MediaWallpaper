#include"UI/Data/TerminalInfo/TerminalInfo.hpp"
#include"UI/Data/ShellWindow/ShellWindow.hpp"
#include"UI/Data/Translator/Translator.hpp"
#include"UI/Data/StartupInfo.hpp"
#include"UI/Data/StyleSheet.hpp"

#include"UI/Basic/PushButton.hpp"
#include"UI/Basic/ComboBox.hpp"
#include"UI/Basic/Label.hpp"

#include<QFontDataBase>
#include<QApplication>
#include<QMessageBox>
#include<QGridLayout>
#include<QFont>

#include"TerminalPanel.hpp"

namespace UI
{
	static const std::vector<QString> AboutStatement =
	{
		"Author: Lubism",
		"\n\n",

		"Dependent librarie(s) and project(s):",
		"\n\n",

		"mpv: https://github.com/mpv-player",
		"\n\n",

		"JSON for modern C++: https://github.com/nlohmann/json"
	};

	static QString ApplyStatement()
	{
		QString result;

		for (auto& it : AboutStatement)
			result += it;

		return result;
	}
}

using namespace UI;

void TerminalPanel::allocation()
{
	UpdateStyleSheet = new PushButton(this, "UpdateStyleSheet");
	UpdatePlaylist = new PushButton(this, "updatePlaylist");
	LoadAllConfig = new PushButton(this, "LoadAllConfig");
	AboutQt = new PushButton(this, "AboutQt");

	FontsizeLabel = new Label(this, "FontsizeLabel");
	StartupLabel = new Label(this, "StartupLabel");
	MonitorLabel = new Label(this, "MonitorLabel");
	LangLabel = new Label(this, "LangLabel");
	FontLabel = new Label(this, "FontLabel");

	FontsizeComboBox = new ComboBox(this);
	StartupComboBox = new ComboBox(this);
	MonitorComboBox = new ComboBox(this);
	LangComboBox = new ComboBox(this);
	FontComboBox = new ComboBox(this);

	Layout = new QGridLayout(this);
}

void TerminalPanel::connection()
{
	connect(FontsizeComboBox, &ComboBox::itemSelected, this, [&](int index) {
		TerminalInfo::Fontsize = FontsizeComboBox->itemText(index).toInt();
		QApplication::setFont(QFont(this->fontInfo().family(),
			TerminalInfo::Fontsize));

		emit this->updateStyleSheet();
		});

	connect(StartupComboBox, &ComboBox::itemSelected, this, [&](int index) {
		TerminalInfo::Startup = static_cast<bool>(index);
		TerminalInfo::LaunchStartup();
		});
	connect(FontComboBox, &ComboBox::itemSelected, this, [&](int index) {
		TerminalInfo::Font = FontComboBox->itemText(index);
		QApplication::setFont(QFont(TerminalInfo::Font,
			this->fontInfo().pointSize())
		);

		emit this->updateStyleSheet();
		});

	connect(LangComboBox, &ComboBox::itemSelected, this, [&](int index) {
		TerminalInfo::Lang = LangComboBox->itemText(index);
		Translator::ReadTranslation(TerminalInfo::Lang);
		emit this->updateLanguage();
		});
	connect(MonitorComboBox, &ComboBox::itemSelected, this, [&](int index) {
		emit this->selectMonitor(index);
		});

	connect(UpdateStyleSheet, &PushButton::clicked, this, [&]() {
		emit this->updateStyleSheet();
		});
	connect(UpdatePlaylist, &PushButton::clicked, this, [&]() {
		emit this->updatePlaylist();
		});
	connect(LoadAllConfig, &PushButton::clicked, this, [&]() {
		emit this->loadAllConfig();
		});
	connect(AboutQt, &PushButton::clicked, this, [&]() {
		QMessageBox::aboutQt(this, AboutQt->text());
		QMessageBox::about(this, "About Program (Part II)",
			ApplyStatement());
		});
}

void TerminalPanel::initLayout()
{
	Layout->addWidget(UpdateStyleSheet, 1, 3, 1, 1);
	Layout->addWidget(UpdatePlaylist, 2, 3, 1, 1);
	Layout->addWidget(LoadAllConfig, 3, 3, 1, 1);
	Layout->addWidget(AboutQt, 4, 3, 1, 1);
	
	Layout->addWidget(FontsizeComboBox, 3, 2, 1, 1);
	Layout->addWidget(StartupComboBox, 5, 2, 1, 1);
	Layout->addWidget(MonitorComboBox, 1, 2, 1, 1);
	Layout->addWidget(LangComboBox, 4, 2, 1, 1);
	Layout->addWidget(FontComboBox, 2, 2, 1, 1);

	Layout->addWidget(FontsizeLabel, 3, 1, 1, 1);
	Layout->addWidget(StartupLabel, 5, 1, 1, 1);
	Layout->addWidget(MonitorLabel, 1, 1, 1, 1);
	Layout->addWidget(LangLabel, 4, 1, 1, 1);
	Layout->addWidget(FontLabel, 2, 1, 1, 1);
}

void TerminalPanel::initialization()
{
	auto langList = Translator::TranslationList();
	for (auto& it : langList) LangComboBox->addItem(it);

	auto monitorCount = ShellWindow::ScreenCount();
	for (auto it = 0; it < monitorCount; ++it) {
		MonitorComboBox->addItem("Monitor" + QString::number(it));
	}

	auto fontList = QFontDatabase().families();
	for (auto& it : fontList) FontComboBox->addItem(it);

	for (auto it = 10; it < 81; ++it) {
		FontsizeComboBox->addItem(QString::number(it));
	}

	FontsizeComboBox->setFocusPolicy(Qt::ClickFocus);
	MonitorComboBox->setFocusPolicy(Qt::ClickFocus);
	FontComboBox->setFocusPolicy(Qt::ClickFocus);
	LangComboBox->setFocusPolicy(Qt::ClickFocus);

	StartupComboBox->addItem("NO");
	StartupComboBox->addItem("YES");

	this->setWindowTitle("Terminal");
	this->initLayout();
}

void TerminalPanel::doUpdateStyleSheet()
{
	StyleSheet::Set(this, "TerminalPanel");
}

void TerminalPanel::doUpdateLanguage()
{
	auto text = [&](const QString& name) { return Translator::Acquire("TerminalPanel", name); };

	UpdateStyleSheet->setText(text("UpdateStyleSheet"));
	UpdatePlaylist->setText(text("UpdatePlaylist"));
	LoadAllConfig->setText(text("LoadAllConfig"));
	AboutQt->setText(text("AboutQt"));

	FontsizeLabel->setText(text("Fontsize"));
	StartupLabel->setText(text("Startup"));
	MonitorLabel->setText(text("Monitor"));

	LangLabel->setText(text("Lang"));
	FontLabel->setText(text("Font"));

	StartupComboBox->setItemText(0, text("No"));
	StartupComboBox->setItemText(1, text("Yes"));

	int size = ShellWindow::ScreenCount();

	for (auto it = 0; it < size; ++it) {
		MonitorComboBox->setItemText(it, text("MonitorID") + QString::number(it));
	}
}

void TerminalPanel::setMonitor(int index)
{
	MonitorComboBox->setCurrentIndex(index);
}

void TerminalPanel::readInfo()
{
	if (TerminalInfo::Font.isEmpty())
		TerminalInfo::Font = "Comic Sans MS";
	if (TerminalInfo::Fontsize < 10)
		TerminalInfo::Fontsize = 10;
	if (TerminalInfo::Lang.isEmpty())
		TerminalInfo::Lang = "en";

	FontsizeComboBox->setCurrentIndex(FontsizeComboBox->findText(
		QString::number(TerminalInfo::Fontsize)
	));

	StartupComboBox->setCurrentIndex(static_cast<int>(
		TerminalInfo::Startup));

	LangComboBox->setCurrentIndex(LangComboBox->findText(
		TerminalInfo::Lang
	));

	FontComboBox->setCurrentIndex(FontComboBox->findText(
		TerminalInfo::Font
	));

	QApplication::setFont(QFont(TerminalInfo::Font, TerminalInfo::Fontsize));
	Translator::ReadTranslation(TerminalInfo::Lang);
	TerminalInfo::LaunchStartup();

	emit this->updateLanguage();
	emit this->updateStyleSheet();
}
