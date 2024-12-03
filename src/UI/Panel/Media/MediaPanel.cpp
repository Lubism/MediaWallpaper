#include"UI/Data/ShellWindow/ShellWindow.hpp"
#include"UI/Data/DisplayInfo/DisplayInfo.hpp"
#include"UI/Data/ScreenInfo/ScreenInfo.hpp"
#include"UI/Data/StyleSheet.hpp"

#include"mpvcpp/mpvCommand.hpp"

#include<QFile>
#include<QDir>

#include<queue>

#include"MediaPanel.hpp"

using EventID = mpv::code::EventID;
using Error = mpv::code::Error;
using Command = mpv::Command;
using Node = mpv::Node;

using namespace UI;

const std::string MediaPanel::ConfigPrefix = std::string("./mediaData/panelConfig/Monitor#");
const std::string MediaPanel::ConfigSuffix = std::string(".conf");

std::vector<QString> MediaPanel::exportPlaylist(const std::vector<QString>& fileList) const
{
	static QString temp(1 << 11, '\0');
	static std::vector<QString> ret(fileList.capacity());

	ret.clear();
	temp.clear();
	size_t pos = 0, left = 0, right = 0;

	for (auto& elem : fileList)
	{
		pos = elem.size() - 1ULL;
		right = left = 0;
		temp.clear();

		for (auto rev = elem.rbegin(); rev != elem.rend(); ++rev)
		{
			if ((*rev) == '.' && right == 0)
				right = pos;
			else if ((*rev) == '/' && left == 0)
				left = pos + 1;

			if (left && right)
				break;
			--pos;
		}

		for (auto it = left; it < right; ++it)
			temp.push_back(elem.at(it));
		ret.push_back(temp);
	}

	return ret;
}

std::vector<QString> MediaPanel::analyzeDirectory(const QString& path) const
{
	std::vector<QString> result;
	QDir dir(path);

	if (path.isEmpty() || !dir.exists())
		return result;
	result.reserve(1ULL << 8);

	auto dirFilter = QDir::Dirs | QDir::NoDotAndDotDot;
	std::queue<QString> fileQueue;
	QFileInfoList fileList;
	QFileInfoList dirList;
	QDir directory;

	auto fileImport = [&]() {for (auto& it : fileList) result.push_back(it.filePath()); };
	auto dirImport = [&]() { for (auto& it : dirList) fileQueue.push(it.filePath()); };
	fileList = dir.entryInfoList(QDir::Files, QDir::LocaleAware);
	dirList = dir.entryInfoList(dirFilter, QDir::LocaleAware);

	fileImport();
	dirImport();

	while (!fileQueue.empty())
	{
		directory.setPath(fileQueue.front());
		fileQueue.pop();

		fileList = directory.entryInfoList(QDir::Files, QDir::LocaleAware);
		dirList = directory.entryInfoList(dirFilter, QDir::LocaleAware);

		fileImport();
		dirImport();
	}

	return result;
}

void MediaPanel::initialization()
{
	this->setWindowTitle("Desktop#" + QString::number(MonitorID));
	Property::Apply(Handle, "wid", static_cast<long long>(
			this->winId()), MonitorID);
	Property::Apply(Handle, "stop-screensaver",
		"no", MonitorID);
	this->setPlaymode(0);

	std::string temp = ConfigPrefix + std::to_string(MonitorID) + ConfigSuffix;
	QString configPath = QString::fromStdString(temp);
	QFile file(configPath);

	if (file.open(QFile::NewOnly))
		file.close();

	ShellWindow::ImportHandle(this->winId());
	Info.MonitorID = MonitorID;
	this->hide();
}

void MediaPanel::checkWindowState(int state)
{
	auto check = [&](long long& value, bool target)
		{
			switch (value)
			{
			case 2: // Pause
				this->setPause(target);
				break;
			case 1: //Mute
				this->setMute(target);
				break;
			case 0: // Do nothing
			default:
				break;
			}
		};

	switch (state)
	{
	case ShellWindow::Fullscreen:
		check(Info.AtFullscreen, true);
		break;
	case ShellWindow::Focused:
		check(Info.AtFocus, true);
		break;
	case ShellWindow::None:
		check(Info.AtFullscreen, false);
		check(Info.AtFocus, false);
	default:
		break;
	}
}

void MediaPanel::updateStyleSheet()
{
	this->setGeometry(ShellWindow::ScreenGeometry(MonitorID));
	StyleSheet::Set(this, "MediaPanel");
	this->loadConfig();
}

void MediaPanel::updatePlaylist()
{
	auto tempList = this->analyzeDirectory(Info.Directory);
	if (tempList.empty()) return;

	auto playlist = this->exportPlaylist(tempList);
	StreamInfo tempInfo = Info;
	size_t index = 0;

	for (auto it = playlist.cbegin(); it != playlist.cend(); ++it) {
		if (it->contains(tempInfo.Name)) {
			tempInfo.Index = index;
			break;
		}

		++index;
	}

	this->clearInfo();
	this->loadFile(tempList, tempInfo.Directory);

	this->setStreamInfo(tempInfo);
	this->setStartTime(tempInfo.Position);
}

void MediaPanel::saveInfo()
{
	this->streamInfo();
	ScreenInfo::ImportInfo(Info);
	DisplayInfo::ImportInfo(Info);
}

void MediaPanel::clearInfo()
{
	this->stop();
	this->setStartTime(0.0);
	Command::Sync(Handle, { "stop" });

	Info.clear();
	Playlist.clear();
	FileLoadedState = false;
	auto temp = StreamInfo();
	this->setStreamInfo(temp);
}

void MediaPanel::readInfo()
{
	StreamInfo info;
	ScreenInfo::ExportInfo(info, MonitorID);
	DisplayInfo::ExportInfo(info, MonitorID);

	this->loadFile(info.Directory);
	this->setStreamInfo(info);
	if (FileLoadedState)
	{
		this->setStartTime(info.Position);
	}
}

void MediaPanel::loadFile(const std::vector<QString>& playlist, const QString& dirPath)
{
	FileLoadedState = false;
	if (playlist.empty())
		return;

	Command::Sync(Handle, { "stop" });
	for (auto& it : playlist) {
		Command::Sync(Handle,
			{
				"loadfile",
				it.toStdString(),
				"append"
			});
	}

	FileLoadedState = true;
	Info.Directory = dirPath;
	Playlist = this->exportPlaylist(playlist);
	Property::Apply(Handle, "playlist-pos", 0LL);
}

void MediaPanel::loadFile(const QString& path)
{
	auto fileList = this->analyzeDirectory(path);
	if (fileList.empty())
		return;

	Command::Sync(Handle, { "stop" });
	FileLoadedState = false;

	for (auto& it : fileList) {
		Command::Sync(Handle,
			{
				"loadfile",
				it.toStdString(),
				"append"
			});
	}

	Info.Directory = path;
	FileLoadedState = true;
	Playlist = this->exportPlaylist(fileList);
	Property::Apply(Handle, "playlist-pos", 0LL);
}

void MediaPanel::play()
{
	Property::Apply(Handle, "pause", false);
	this->updateStyleSheet();
	this->show();
}

void MediaPanel::stop()
{
	this->hide();

	Property::Apply(Handle, "pause", true);
	Property::Apply(Handle, "playback-time", 0.0);

	ShellWindow::RefreshDisplay();
}
