#include"UI/Data/ShellWindow/ShellWindow.hpp"
#include"UI/Data/Translator/Translator.hpp"
#include"UI/Data/StyleSheet.hpp"

#include<QAction>
#include<QMenu>

#include"SystemTrayIcon.hpp"

using namespace UI;

SystemTrayIcon::~SystemTrayIcon()
{
	delete MonitorMenu;
	delete MainMenu;

	MonitorMenu = nullptr;
	MainMenu = nullptr;
}

void SystemTrayIcon::allocation()
{
	MonitorMenu = new QMenu("MonitorMenu");
	MainMenu = new QMenu("MainMenu");
	QAction* screen = nullptr;

	auto screenCount = ShellWindowCore::ScreenCount();
	for (auto it = 0; it < screenCount; ++it)
	{
		screen = new QAction(QString::number(it), this);
		MonitorMenu->addAction(screen);
		Monitor.push_back(screen);
	}

	Terminal = new QAction("Terminal", this);
	Shutdown = new QAction("Shutdown", this);
	Showup = new QAction("Showup", this);
}

void SystemTrayIcon::connection()
{
	connect(Terminal, &QAction::triggered, this, [&]() {
		emit this->terminal();
		});
	connect(Shutdown, &QAction::triggered, this, [&]() {
		emit this->shutdown();
		});
	connect(Showup, &QAction::triggered, this, [&]() {
		emit this->showup();
		});

	connect(this, &SystemTrayIcon::activated, this, [&](ActivationReason reason) {
		if (reason == ActivationReason::DoubleClick)
			emit this->showup();
		});
	connect(MonitorMenu, &QMenu::triggered, this, [&](QAction* action) {
			int temp = 0;
			for (auto& it : Monitor) {
				if (action == it) {
					emit this->monitorSelected(temp);
					break;
				}

				++temp;
			}
		});
}

void SystemTrayIcon::initialization()
{
	for (auto& it : Monitor) MonitorMenu->addAction(it);
	MainMenu->addMenu(MonitorMenu);

	MainMenu->addAction(Terminal);
	MainMenu->addAction(Showup);

	MainMenu->addAction(Shutdown);
	this->setContextMenu(MainMenu);
}

void SystemTrayIcon::updateStyleSheet()
{
	StyleSheet::Set(MonitorMenu, "MainWindow");
	StyleSheet::Set(MainMenu, "MainWindow");
}

void SystemTrayIcon::updateLanguage()
{
	auto text = [&](const QString& name)
		{
			return Translator::Acquire("TrayIcon", name);
		};

	MonitorMenu->setTitle(text("MonitorMenu"));
	MainMenu->setTitle(text("MainWindow"));
	Terminal->setText(text("Terminal"));
	Shutdown->setText(text("Shutdown"));
	Showup->setText(text("Showup"));

	auto screenText = text("MonitorID");
	size_t pos = 0;

	for (auto& it : Monitor) {
		it->setText(screenText + QString::number(pos));
		++pos;
	}
}
