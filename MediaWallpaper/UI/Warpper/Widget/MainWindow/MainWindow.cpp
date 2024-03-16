#include"UI/Warpper/Widget/TerminalWidget/TerminalWidget.hpp"
#include"UI/Warpper/Widget/PanelWidget/PanelWidget.hpp"
#include"UI/Warpper/SystemTrayIcon/SystemTrayIcon.hpp"
#include"UI/Warpper/Data/DesktopInfo/DesktopInfo.hpp"
#include"UI/Warpper/Data/ProgramInfo/ProgramInfo.hpp"
#include"UI/Warpper/Data/Translator/Translator.hpp"
#include"UI/Warpper/Data/StyleSheet.hpp"
#include<QGridLayout>
#include<QCloseEvent>
#include<QFile>

#include"MainWindow.hpp"

using namespace UI;

void MainWindow::quit()
{
	Terminal->quit();
	QuitState = true;
	this->close();
}

void MainWindow::allocation()
{
	auto screenCount = DesktopInfo::screenCount();

	TrayIcon = new SystemTrayIcon(this, screenCount);
	Terminal = new TerminalWidget(this, screenCount);
	Panel = new PanelWidget(this, screenCount);

	Layout = new QGridLayout(this);
}

void MainWindow::connection()
{
	connect(TrayIcon, &SystemTrayIcon::selectPanel, Terminal,
		&TerminalWidget::setCurrentPanel);
	connect(TrayIcon, &SystemTrayIcon::selectPanel, Panel,
		&PanelWidget::selectPanel);
	connect(TrayIcon, &SystemTrayIcon::terminal, Terminal,
		&TerminalWidget::showup);
	connect(TrayIcon, &SystemTrayIcon::showup, this,
		&MainWindow::showup);
	connect(TrayIcon, &SystemTrayIcon::quit, this,
		&MainWindow::quit);

	connect(Terminal, &TerminalWidget::updateStyleSheet, this,
		&MainWindow::updateStyleSheet);
	connect(Terminal, &TerminalWidget::selectLanguage, this,
		&MainWindow::updateLanguage);

	connect(Terminal, &TerminalWidget::refreshDisplay, Panel,
		&PanelWidget::refreshDisplay);
	connect(Terminal, &TerminalWidget::selectPanel, Panel,
		&PanelWidget::selectPanel);
}

void MainWindow::initialization()
{
	this->setWindowIcon(QIcon("./resources/image/MainIcon.ico"));
	this->setMinimumSize(540, 280);
	this->updateStyleSheet();

	Layout->setContentsMargins(0, 0, 0, 0);
	Layout->addWidget(Panel);

	TrayIcon->setIcon(this->windowIcon());
	TrayIcon->show();
}

void MainWindow::updateStyleSheet()
{
	StyleSheet::Set(this, "MainWindow");
	Panel->updateStyleSheet();
}

void MainWindow::updateLanguage()
{
	if (!Translator::TranslationAvaliable()) return;
	this->setWindowTitle(Translator::Acquire(
		"MainGroup", "Main"));

	TrayIcon->updateLanguage();
	Terminal->updateLanguage();
	Panel->updateLanguage();

	emit this->selectLanguage();
}

bool MainWindow::readInfo()
{
	ProgramInfo::ReadInfo();
	int width = 0, height = 0;

	width = ProgramInfo::Acquire("MainWindow", "Width").toInt();
	height = ProgramInfo::Acquire("MainWindow", "Height").toInt();

	this->resize(width, height);
	auto result = Panel->readInfo();

	Terminal->readInfo();
	return result;
}

void MainWindow::saveInfo()
{
	auto windowSize = this->size();

	ProgramInfo::Apply("MainWindow",
		"Width", QString::number(
		windowSize.width())
	);
	ProgramInfo::Apply("MainWindow",
		"Height", QString::number(
		windowSize.height())
	);

	Panel->saveInfo();
	Terminal->saveInfo();
	ProgramInfo::WriteInfo();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if (!QuitState)
	{
		event->ignore();
		this->hide();
		return;
	}

	this->saveInfo();
	event->accept();
}
