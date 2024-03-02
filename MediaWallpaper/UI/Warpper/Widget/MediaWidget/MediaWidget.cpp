#include"UI/Warpper/Data/DesktopInfo/DesktopInfo.hpp"
#include"UI/Base/DesktopHandle/DesktopHandle.hpp"
#include"UI/Warpper/Data/StyleSheet.hpp"
#include"mpvcpp/mpvEvent.hpp"
#include<thread>
#include<chrono>
#include<queue>
#include<QDir>

#include"MediaWidget.hpp"

using namespace mpv::code;
using namespace mpv;
using namespace UI;

MediaWidget::~MediaWidget()
{
	this->stop();
	StopState = true;
	while (EventThread);
	DesktopHandle::RefreshDesktop();
}

void MediaWidget::allocation()
{
	Handle.create();
	Handle.initialize();
}

void MediaWidget::initialization()
{
	this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
	DesktopHandle::InsertWindow(this->winId());

	Property::Apply(Handle, "wid", static_cast<long long>(
		this->winId()), DesktopID);

	this->updateStyleSheet();
	this->setPlaymode(0);
	this->loadConfig();
	StopState = false;
	this->hide();

	std::thread(&MediaWidget::eventThread, this).detach();
}

bool MediaWidget::loadFile(const QString& data)
{
	auto filelist = this->analyzeDirectory(data);
	if (filelist.empty() || data.isEmpty())
		return false;
	Int storage = 0;
	DirectoryPath = data;

	Command::Sync(Handle, { "stop" });
	for (auto& it : filelist) {
		Command::Sync(Handle,
			{
				"loadfile",
				it.toStdString(),
				"append"
			});
	}

	emit this->updateDirectory(DirectoryPath);
	this->setCurrentIndex(0);
	this->importPlaylist();
	this->play();

	return true;
}

void MediaWidget::updateStyleSheet()
{
	StyleSheet::Set(this, "MediaWidget");
}

void MediaWidget::refreshDisplay()
{
	QRect rect = DesktopInfo::screenGeometry(DesktopID);
	DesktopHandle::InsertWindow(this->winId());
	this->setGeometry(rect);
	this->loadConfig();
}

void MediaWidget::loadConfig()
{
	auto path = "./mediaData/config/Desktop#" + QString::number(DesktopID) + ".conf";

	QFile file(path);

	if (!file.exists()) {
		file.open(QIODevice::WriteOnly);
		file.close();
		return;
	}

	auto ret = Handle.loadConfig(path.toStdString());
}

void MediaWidget::clearInfo()
{
	emit this->updatePlaylist(std::vector<QString>());
	emit this->updateCurrentIndex(-1);
	emit this->currentFileChanged("");
	emit this->updateDirectory("");

	this->stop();
	this->setStartTime(0.0);
	Command::Sync(Handle, { "stop" });

	this->setSubVisibility(true);
	this->setPlaymode(0);

	this->setVolume(100.0);
	this->setSpeed(1.0);

	this->setPause(false);
	this->setMute(false);

	DirectoryPath = "";
	Duration = 0.0;

	this->hide();
	DesktopHandle::RefreshDesktop();
}

void MediaWidget::play()
{
	this->refreshDisplay();
	this->setPause(false);
}

void MediaWidget::stop()
{
	this->hide();
	this->setPause(true);
	this->setPosition(0.0);
	DesktopHandle::RefreshDesktop();
}

bool MediaWidget::setStartTime(double data)
{
	Int tick = 0;

	while (data != Position)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		Property::Apply(Handle, "playback-time", data);
		if (tick >= 150) return false;
		tick++;
	}

	return true;
}

void MediaWidget::setPause(bool data)
{
	Property::Apply(Handle, "pause", data, DesktopID);
	if (!data) this->show();
}

std::vector<QString> MediaWidget::analyzeDirectory(const QString& dirPath)
{
	auto dirFilter = QDir::Dirs | QDir::NoDotAndDotDot;
	std::queue<QString> fileQueue;
	std::vector<QString> result;
	QFileInfoList fileList;
	QFileInfoList dirList;

	QDir dir(dirPath);
	QDir directory;

	auto pushFile = [&]() {for (auto& it : fileList) result.push_back(it.filePath()); };
	auto pushDir = [&]() { for (auto& it : dirList) fileQueue.push(it.filePath()); };
	fileList = dir.entryInfoList(QDir::Files, QDir::LocaleAware);
	dirList = dir.entryInfoList(dirFilter, QDir::LocaleAware);
	pushFile();
	pushDir();

	while (!fileQueue.empty())
	{
		directory.setPath(fileQueue.front());
		fileQueue.pop();

		fileList = directory.entryInfoList(QDir::Files,
			QDir::LocaleAware);
		dirList = directory.entryInfoList(dirFilter,
			QDir::LocaleAware);

		pushFile();
		pushDir();
	}

	return result;
}

void MediaWidget::importPlaylist()
{
	Node node;
	QString convert = "";
	size_t pos = 0, left = 0, right = 0;
	std::vector<QString>().swap(Playlist);
	Property::Acquire(Handle, "playlist", node);
	for (auto& file : node.Array) {
		for (auto& it : file.Map)
		{
			if (it.first == "filename")
			{
				auto& String = it.second.String;
				pos = String.size() - 1;
				left = right = 0;

				for (auto rvs = String.rbegin(); rvs != String.rend(); rvs++)
				{
					if ((*rvs) == '.' && right == 0)
						right = pos;
					if ((*rvs) == '/' && left == 0)
						left = pos + 1;
					if (right && left) break;

					--pos;
				}
				Playlist.push_back(QString::fromStdString(
					String.substr(left,
						right - left))
				);
				break;
			}
		}
	}

	emit this->updatePlaylist(Playlist);
}

void MediaWidget::eventThread()
{
	EventThread = true;
	using ID = code::EventID;

	Event event;
	while (!StopState)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(33));

		Property::Acquire(Handle, "sub-visibility", SubVisibility);
		Property::Acquire(Handle, "playlist-pos", CurrentIndex);
		Property::Acquire(Handle, "playback-time", Position);
		Property::Acquire(Handle, "duration", Duration);
		Property::Acquire(Handle, "volume", Volume);
		Property::Acquire(Handle, "speed", Speed);
		Property::Acquire(Handle, "mute", Mute);

		event.receive(Handle);
		switch (event.ID)
		{
		case ID::FileLoaded:
			for (auto it = Playlist.begin(); it != Playlist.end(); it++)
			{
				if (CurrentIndex == std::distance(Playlist.begin(), it))
				{
					emit this->updateCurrentIndex(CurrentIndex);
					emit this->currentFileChanged(*it);
				}
			}
			break;
		default:
			break;
		}

		this->emitThread();
	}

	EventThread = false;
}
