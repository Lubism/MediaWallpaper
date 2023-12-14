#include"UI/Warpper/GroupBox/TerminalGroupBox/TerminalGroupBox.hpp"
#include"UI/Warpper/Widget/PanelWidget/PanelWidget.hpp"
#include"UI/Warpper/SystemTrayIcon/SystemTrayIcon.hpp"
#include"UI/Basic/MessageBox/MessageBox.hpp"
#include"UI/Warpper/Resources/Resources.hpp"
#include"MainWindow.hpp"
#include<QDesktopWidget>
#include<QApplication>
#include<QResizeEvent>
#include<QCloseEvent>
#include<QShowEvent>
#include<QSettings>
#include<fstream>
#include<vector>
#include<QIcon>

namespace UI
{
	struct MainWindowSize
	{
		int Width = 900;
		int Height = 550;
	public:
		inline MainWindowSize& operator=(const QSize& right)
		{
			Height = right.height();
			Width = right.width();
			return *this;
		}

		inline MainWindowSize(const QSize& right) {
			this->operator=(right);
		}

		inline QSize toQSize() const {
			QSize ret(Width, Height);
			return ret;
		}

		inline MainWindowSize() {}
	};
}

using namespace UI;

void MainWindow::allocation()
{
	std::unique_ptr<QDesktopWidget> desktop(new QDesktopWidget);
	int screenCount = desktop->screenCount();

	Terminal = new TerminalGroupBox(this, screenCount);
	Panel = new PanelWidget(this, screenCount);
	TrayIcon = new SystemTrayIcon(this);

	AboutProgram = new MessageBox(this,
		Converter::CH("关于程序"));
	AboutAuther = new MessageBox(this,
		Converter::CH("关于作者"));
	AboutIcon = new MessageBox(this,
		Converter::CH("关于图标"));
}

void MainWindow::connection()
{
	connect(Terminal, &TerminalGroupBox::selectPanel,
		Panel, &PanelWidget::setPage);
	connect(Terminal, &TerminalGroupBox::autoboot,
		this, &MainWindow::setAutoBoot);
	connect(Terminal, &TerminalGroupBox::updatePanel,
		this, &MainWindow::updateStyleSheet);
	connect(TrayIcon, &SystemTrayIcon::aboutProgram,
		this, [&]()
		{
			this->show();
			AboutProgram->aboutQt();
		});
	connect(TrayIcon, &SystemTrayIcon::aboutAuther,
		this, [&]()
		{
			this->show();
			AboutAuther->show();
		});
	connect(TrayIcon, &SystemTrayIcon::aboutIcon,
		this, [&]()
		{
			this->show();
			AboutIcon->show();
		});
	connect(TrayIcon, &SystemTrayIcon::showup,
		this, &MainWindow::showup);
	connect(TrayIcon, &SystemTrayIcon::quit,
		this, &MainWindow::quit);
}

void MainWindow::initialization()
{
	this->setWindowTitle(Converter::CH("视频壁纸播放器"));
	this->setWindowIcon(QIcon(image::MainIcon));
	this->setMinimumSize(900, 550);
	this->updateStyleSheet();

	AboutAuther->setText(Converter::CH("作者：Lubism(大三)"));
	AboutAuther->setIconPixmap(QPixmap(image::AutherIcon));
	AboutIcon->setIconPixmap(QPixmap(image::MainIcon));
	TrayIcon->setIcon(QIcon(image::MainIcon));
	TrayIcon->show();

	std::ifstream reader("autoboot.dat", std::ios::binary);
	if (reader.fail() == false)
	{
		reader.read(reinterpret_cast<char*>(
			&AutobootState),
			sizeof(bool));
		Terminal->setAutoboot(
			AutobootState);
	}
	
	reader.close();
}

void MainWindow::readMediaData()
{
	Panel->readMediaData();

	std::ifstream reader("mainWindow.dat", std::ios::binary);
	if (reader.fail()) return;
	MainWindowSize windowSize;

	reader.read(reinterpret_cast<char*>(&windowSize),
		sizeof(windowSize));
	this->resize(windowSize.toQSize());
	reader.close();
}

void MainWindow::saveMediaData()
{
	Panel->saveMediaData();
	MainWindowSize windowSize = this->size();
	std::ofstream writer("mainWindow.dat", std::ios::binary);

	writer.write(reinterpret_cast<char*>(&windowSize),
		sizeof(windowSize));
	writer.close();
}

void MainWindow::updateStyleSheet()
{
	css::Setter(css::MainWindow, this);
	TrayIcon->updateStyleSheet();
	Panel->updateStyleSheet();
}

void MainWindow::setAutoBoot(bool data)
{
	const QString regPath = "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	std::unique_ptr<QSettings> Setting(new QSettings(regPath, QSettings::NativeFormat));
	QString path = "\"" + QApplication::applicationDirPath().replace("/", "\\");
	path += "\\autoboot.bat\"";

	QString name = QApplication::applicationName();
	this->makeAutobootFile(data);
	if (data == true)
	{
		AutobootState = true;
		Setting->setValue(name, path);
		std::ofstream writer("autoboot.dat", std::ios::binary);

		writer.write(reinterpret_cast<char*>(
			&AutobootState),
			sizeof(bool));
		writer.close();

		return;
	}

	int no_use = std::remove("autoboot.dat");
	AutobootState = false;
	Setting->remove(name);
}

void MainWindow::makeAutobootFile(bool data)
{
	if (data == false)
	{
		int no_use = std::remove("autoboot.bat");
		return;
	}

	std::string name = QApplication::applicationName().toStdString();
	const std::vector<std::string> bat =
	{
		"@echo off",
		"\n",

		"cd /d %~dp0",
		"\n",

		"start \"\" \"" + name + ".exe\"",
		"\n",

		"exit"
	};
	std::string input = "";
	for (const std::string& it : bat)
		input += it;

	std::ofstream writer("autoboot.bat");
	writer << input;
	writer.close();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	Converter cvt(900, 550, event);
	Widget::resizeEvent(event);

	Terminal->setGeometry(cvt, 10, 10, 330, 530);
	Panel->setGeometry(cvt, 460, 10, 430, 530);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if (QuitState == true)
	{
		this->saveMediaData();
		event->accept();
		return;
	}

	event->ignore();
	this->hide();
}
