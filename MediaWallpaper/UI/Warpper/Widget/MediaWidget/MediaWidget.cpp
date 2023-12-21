#include"UI/Warpper/Resources/Resources.hpp"
#include"UI/Basic/DesktopHandle.hpp"
#include"mpvcpp/mpvCommand.hpp"
#include"mpvcpp/mpvEvent.hpp"
#include"MediaWidget.hpp"
#include<unordered_map>
#include<thread>
#include<chrono>

#include<QDesktopWidget>
#include<QApplication>
#include<QDir>

using namespace mpv;
using namespace std;
using namespace UI;

MediaWidget::~MediaWidget()
{
	StopState = true;

	while (ListenThread || EventThread);
	DesktopHandle::RefreshProgman();
}

void MediaWidget::allocation()
{
	Handle.create();
	Handle.initialize();
}

void MediaWidget::initialization()
{
	this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
	DesktopHandle::InsertProgman(this->winId());

	Property::Apply(Handle, "wid", static_cast<
		long long>(this->winId()));

	this->updateStyleSheet();
	this->setPlaymode(0);
	this->loadConfig();
	StopState = false;
	this->hide();

	std::thread(&MediaWidget::eventThread,
		this).detach();
	std::thread(&MediaWidget::listenThread,
		this).detach();
}

bool MediaWidget::loadfile(const QString& data)
{
	if (data.isEmpty()) return false;
	QDir directory = QDir(data);

	if (directory.exists() == false)
		return false;
	if (directory.entryInfoList().isEmpty())
		return false;

	FolderPath = data.toStdString();
	Command::Async(this->Handle,
		{
			string("loadfile"),
			FolderPath,
			string("")
		},
		DesktopID);

	PlaylistIndex = -1;
	this->play();
	Event event;

	while (event.ID != code::EventID::FileLoaded)
		event.receive(Handle);

	this->importPlayfile();
	return true;
}

void MediaWidget::updateStyleSheet()
{
	css::Setter(css::MediaWidget, this);
}

void MediaWidget::loadConfig()
{
	std::string rootPath = QDir::currentPath().replace("/", "\\").toStdString();
	std::string prefix = rootPath + "\\mediaData\\config\\screen#";
	std::string number = std::to_string(DesktopID);
	std::string suffix = ".conf";
	
	std::string path = prefix + number + suffix;
	Handle.loadConfig(path);
}

void MediaWidget::play()
{
	this->refreshDisplay();
	this->setPause(false);
	this->show();
}

void MediaWidget::last()
{
	Command::Async(this->Handle,
		{
			string("playlist-prev"),
			string("")
		},
		DesktopID);
}

void MediaWidget::next()
{
	Command::Async(this->Handle,
		{
			string("playlist-next"),
			string("")
		},
		DesktopID);
}

void MediaWidget::stop()
{
	this->close();
	this->setPause(true);
	this->setPosition(0);
	DesktopHandle::RefreshProgman();
}

void MediaWidget::refreshDisplay()
{
	std::unique_ptr<QDesktopWidget> desktop(new QDesktopWidget);
	QRect rect = desktop->screenGeometry(DesktopID);
	this->setGeometry(rect);
	this->loadConfig();
}

void MediaWidget::clearInfo()
{
	Command::Async(Handle,
		{
			std::string("stop"),
			std::string(""),
			std::string("")
		},
		DesktopID);
	this->stop();

	Duration = Position = 0.0;
	SubVisibility = true;
	Playmode = 0;

	FolderPath = "";
	Volume = 100.0;
	Speed = 1.0;

	Pause = false;
	Mute = false;

	this->setSubVisibility(true);
	this->setPlaymode(0);

	this->setVolume(100.0);
	this->setSpeed(1.0);

	this->setPause(false);
	this->setMute(false);
}

void MediaWidget::setStartTime(double data)
{
	long long tick = 0;
	bool failState = false;
	while (data != Position)
	{
		this_thread::sleep_for(chrono::milliseconds(20));
		this->setPosition(data);
		if (tick >= 250) {
			failState = true;
			break;
		}
		++tick;
	}

	if (failState) {
		this->stop();
		QApplication::exit(-2);
	}
}

void MediaWidget::importPlayfile()
{
	Node node;
	QString convert = "";
	size_t pos = 0, left = 0, right = 0;
	std::vector<QString>().swap(Playlist);
	Property::Acquire(Handle, "playlist", node);
	for (auto& file : node.Array)
	{
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

void MediaWidget::listenThread()
{
	ListenThread = true;

	while (!StopState)
	{
		this_thread::sleep_for(chrono::milliseconds(100));

		Property::Acquire(Handle, "sub-visibility", DesktopID, Format::BooleanInt);
		Property::Acquire(Handle, "playback-time", DesktopID, Format::Double);
		Property::Acquire(Handle, "playlist-pos", DesktopID, Format::Int);

		Property::Acquire(Handle, "duration", DesktopID, Format::Double);
		Property::Acquire(Handle, "volume", DesktopID, Format::Double);
		Property::Acquire(Handle, "speed", DesktopID, Format::Double);

		Property::Acquire(Handle, "pause", DesktopID, Format::BooleanInt);
		Property::Acquire(Handle, "mute", DesktopID, Format::BooleanInt);
	}

	ListenThread = false;
}

void MediaWidget::eventThread()
{
	EventThread = true;
	int tick = 0;
	Event event;

	auto& property = event.Property;
	auto& name = property.Name;
	while (!StopState)
	{
		this_thread::sleep_for(chrono::milliseconds(20));

		for (tick = 0; tick < 8; tick++)
		{
			event.receive(Handle);
			if (event.ErrorCode == code::Error::Success) {
				if (event.ID == EventID::GetProperty)
				{
					auto it = PropertyKey.find(name);
					if (it == PropertyKey.end())
						continue;

					this->eventFilter(&event,
						it->second);
				}
			}
		}
	}

	EventThread = false;
}

void MediaWidget::eventFilter(Event* event, const int& code)
{
	auto& storage = event->Property;

	switch (code)
	{
	case 0:	SubVisibility = storage.Bool; break;
	case 1:	Position = storage.Double; break;
	case 2:
		if (storage.Int != PlaylistIndex) {
			emit this->updatePlaylistIndex(
				storage.Int);
			PlaylistIndex = storage.Int;

			if (!Playlist.empty() && PlaylistIndex > -1) {
				emit this->updatePlayfile(Playlist.at(
					storage.Int));
			}
		}
		break;
	case 3:	Duration	= storage.Double;	break;
	case 4:	Volume		= storage.Double;	break;
	case 5:	Speed		= storage.Double;	break;
	case 6:	Pause		= storage.Bool;		break;
	case 7:	Mute		= storage.Bool;		break;
	}

	emit this->updateTime(Position, Duration);
}

const std::unordered_map<std::string, int> MediaWidget::PropertyKey =
{
	{"sub-visibility", 0},
	{"playback-time", 1},
	{"playlist-pos", 2},
	{"duration", 3},
	{"volume", 4},
	{"speed", 5},
	{"pause", 6},
	{"mute", 7}
};
