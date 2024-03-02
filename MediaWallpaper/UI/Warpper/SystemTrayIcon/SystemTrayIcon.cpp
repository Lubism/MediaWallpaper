#include"UI/Warpper/Data/Translator/Translator.hpp"
#include"SystemTrayIcon.hpp"
#include<QAction>
#include<QMenu>

using namespace UI;

void SystemTrayIcon::allocation()
{
	Show = new QAction("Show", this);
	Quit = new QAction("Quit", this);
	Terminal = new QAction("Terminal", this);

	MainMenu = new QMenu("MainMenu", static_cast<QWidget*>(
		this->parent()));
	ScreenMenu = new QMenu("ScreenMenu", static_cast<QWidget*>(
		this->parent()));

	for (auto it = 0; it < ScreenCount; it++) {
		Screen = new QAction(QString::number(it), this);
		ScreenMenu->addAction(Screen);
	}

	Screen = nullptr;
}

void SystemTrayIcon::connection()
{
	connect(this, &QSystemTrayIcon::activated, this, [&](QSystemTrayIcon::ActivationReason reason)
		{
			if (reason == ActivationReason::DoubleClick)
				emit this->showup();
		});

	connect(ScreenMenu, &QMenu::triggered, this,
		[&](QAction* target)
		{
			Int index = 0;
			auto list = ScreenMenu->actions();
			for (auto it = list.begin(); it != list.end(); it++) {
				index = std::distance(list.begin(), it);
				if (target == *it)
				{
					emit this->selectPanel(index);
					break;
				}
			}
		});

	connect(Terminal, &QAction::triggered, this,
		[&]() {emit this->terminal(); });
	connect(Show, &QAction::triggered, this,
		[&]() {emit this->showup(); });
	connect(Quit, &QAction::triggered, this,
		[&]() {emit this->quit(); });
}

void SystemTrayIcon::initialization()
{
	MainMenu->addMenu(ScreenMenu);
	MainMenu->addAction(Terminal);
	MainMenu->addAction(Show);
	MainMenu->addAction(Quit);

	this->setContextMenu(MainMenu);
}

void SystemTrayIcon::updateLanguage()
{
	auto receive = [](const QString& name) {return Translator::Acquire("TrayIconGroup", name); };
	if (!Translator::TranslationAvaliable()) return;

	Show->setText(receive("Show"));
	Quit->setText(receive("Quit"));
	Terminal->setText(receive("Terminal"));

	auto list = ScreenMenu->actions();
	auto storage = receive("Screen");
	auto size = list.size();

	for (auto it = 0; it < size; it++)
	{
		list.at(it)->setText(storage + QString::number(it));
	}

	MainMenu->setTitle(receive("MainMenu"));
	ScreenMenu->setTitle(receive("ScreenMenu"));
}
