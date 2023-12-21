#include"UI/Warpper/Resources/Resources.hpp"
#include"SystemTrayIcon.hpp"
#include"UI/Basic/Font.hpp"
#include<QAction>
#include<QMenu>
#include<QIcon>

using namespace UI;

SystemTrayIcon::~SystemTrayIcon()
{
	delete AboutMenu;
	delete MainMenu;

	AboutMenu = nullptr;
	MainMenu = nullptr;
}

void SystemTrayIcon::allocation()
{
	AboutMenu = new QMenu(nullptr);
	MainMenu = new QMenu(nullptr);

	Program = new QAction(this);
	Auther = new QAction(this);
	Icon = new QAction(this);

	Show = new QAction(this);
	Quit = new QAction(this);
}

void SystemTrayIcon::connection()
{
	connect(Program, &QAction::triggered, this,
		[&]() {emit this->aboutProgram(); });
	connect(Auther, &QAction::triggered, this,
		[&]() {emit this->aboutAuther(); });
	connect(Icon, &QAction::triggered, this,
		[&]() {emit this->aboutIcon(); });

	connect(Show, &QAction::triggered, this,
		[&]() {emit this->showup(); });
	connect(Quit, &QAction::triggered, this,
		[&]() {emit this->quit(); });

	connect(this, &QSystemTrayIcon::activated, this,
		[&](ActivationReason reason)
		{
			if (reason == Reason::DoubleClick)
				emit this->showup();
		});
}

void SystemTrayIcon::initialization()
{
	this->setIcon(QIcon("resources\\image\\Icon.ico"));
	this->setContextMenu(MainMenu);

	AboutMenu->addAction(Program);
	AboutMenu->addAction(Auther);
	AboutMenu->addAction(Icon);

	MainMenu->addMenu(AboutMenu);
	MainMenu->addAction(Show);
	MainMenu->addAction(Quit);

	AboutMenu->setTitle(Converter::CH("关于"));
	Program->setText(Converter::CH("程序"));
	Auther->setText(Converter::CH("作者"));
	Icon->setText(Converter::CH("图标"));

	Show->setText(Converter::CH("显示"));
	Quit->setText(Converter::CH("退出"));

	this->updateStyleSheet();
}

void SystemTrayIcon::updateStyleSheet()
{
	css::Setter(css::MainMenu, MainMenu);
	css::Setter(css::AboutMenu, AboutMenu);
}
