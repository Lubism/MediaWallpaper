#include"UI/Basic/DesktopHandle/DesktopHandle.hpp"
#include"UI/Warpper/Resources/Resources.hpp"
#include"mpvcpp/mpvCommand.hpp"
#include"mpvcpp/mpvEvent.hpp"
#include"MediaWidget.hpp"
#include<unordered_map>
#include<thread>
#include<chrono>

#include<QDesktopWidget>
#include<QDir>

using namespace mpv;
using namespace std;
using namespace UI;

MediaWidget::~MediaWidget()
{
	StopState = true;

	while (AcquireThread || EventThread);
	DesktopHandle::RefreshProgman();
}

void MediaWidget::allocation()
{
	Handle.create();
	Handle.initialize();
}

void MediaWidget::initialization()
{
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	DesktopHandle::InsertProgman(this->winId());
	Property::Apply(Handle, "wid", static_cast<
		long long>(this->winId()));
	this->updateStyleSheet();
	this->setPlaymode(0);
	this->loadConfig();
	StopState = false;
	this->hide();

	std::thread(&MediaWidget::eventThread, this).detach();
	std::thread(&MediaWidget::acquireThread, this).detach();
}

bool MediaWidget::loadfile(const QString& data)
{
	if (data.isEmpty()) return false;
	QDir fileValidate = QDir(data);

	if (fileValidate.exists() == false)
		return false;
	if (fileValidate.entryInfoList().isEmpty())
		return false;

	this->FolderPath = data.toStdString();
	Command::Async(this->Handle,
		{
			string("loadfile"),
			FolderPath,
			string("")
		},
		this->DesktopID);
	PlaylistIndex = -1;
	this->play();
	Event event;

	while (event.ID != code::EventID::FileLoaded)
		event.receive(Handle);
	if (Playlist.size() == 1) {
		this->setPlaymode(1);
	}

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
	try
	{
		std::string path = prefix + number + suffix;
		Handle.loadConfig(path);
	}
	catch (...)
	{
	}
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
		this->DesktopID);
}

void MediaWidget::next()
{
	Command::Async(this->Handle,
		{
			string("playlist-next"),
			string("")
		},
		this->DesktopID);
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
	Command::Async(this->Handle,
		{
			std::string("stop"),
			std::string(""),
			std::string("")
		}, this->DesktopID);
	this->stop();

	this->Duration = this->Position = 0.0;
	this->SubVisibility = true;
	this->Playmode = 0;

	this->FolderPath = "";
	this->Volume = 100.0;
	this->Speed = 1.0;

	this->Pause = false;
	this->Mute = false;

	this->setSubVisibility(true);
	this->setPlaymode(0);

	this->setVolume(100.0);
	this->setSpeed(1.0);

	this->setPause(false);
	this->setMute(false);
}

void MediaWidget::setStartTime(double data)
{
	while (data != Position)
	{
		Property::Apply(Handle, "playback-time",
			data, this->DesktopID);

		Property::Acquire(Handle, "playback-time", this->DesktopID,
			code::Format::Double);

		this_thread::sleep_for(chrono::milliseconds(20));
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

				for (auto rvs = String.rbegin();
					rvs != String.rend();
					rvs++)
				{
					if ((*rvs) == '.' && right == 0)
						right = pos;
					if ((*rvs) == '/' && left == 0)
						left = pos + 1;
					if (right && left) break;

					--pos;
				}
				Playlist.push_back(QString::fromStdString(
					String.substr(left, right - left)
				));
				break;
			}
		}
	}

	emit this->updatePlaylist(Playlist);
}

void MediaWidget::acquireThread()
{
	AcquireThread = true;

	while (!StopState)
	{
		this_thread::sleep_for(chrono::milliseconds(100));

		Property::Acquire(this->Handle, "sub-visibility",
			this->DesktopID, Format::BooleanInt);
		Property::Acquire(this->Handle, "playback-time",
			this->DesktopID, Format::Double);
		Property::Acquire(this->Handle, "playlist-pos",
			this->DesktopID, Format::Int);

		Property::Acquire(this->Handle, "duration",
			this->DesktopID, Format::Double);
		Property::Acquire(this->Handle, "volume",
			this->DesktopID, Format::Double);
		Property::Acquire(this->Handle, "speed",
			this->DesktopID, Format::Double);
		Property::Acquire(this->Handle, "pause",
			this->DesktopID, Format::BooleanInt);
		Property::Acquire(this->Handle, "mute",
			this->DesktopID, Format::BooleanInt);
	}

	AcquireThread = false;
}

void MediaWidget::eventThread()
{
	EventThread = true;

	Event event;
	int it = 0;

	auto& property = event.PropertyEvent;
	auto& name = property.Name;

	std::unordered_map<std::string, int> key =
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

	while (!StopState)
	{
		this_thread::sleep_for(chrono::milliseconds(10));

		for (it = 0; it < 6; it++)
		{
			event.receive(Handle, 0.0);
			if (event.ErrorCode == code::Error::Success) {
				if (event.ID == code::EventID::GetProperty) {
					auto iter = key.find(name);
					if (iter == key.end())
						continue;
					this->eventFilter(&event,
						iter->second);
				}
			}
		}
	}

	EventThread = false;
}

void MediaWidget::eventFilter(Event* event, int& code)
{
	auto& property = event->PropertyEvent;

	switch (code)
	{
	case 0:
		SubVisibility = property.Bool;
		break;
	case 1:
		Position = property.Double;
		break;
	case 2:
		if (property.Int != PlaylistIndex) {
			emit this->updatePlaylistIndex(property.Int);
			PlaylistIndex = property.Int;
		}
		if (!Playlist.empty() && property.Int > -1) {
			emit this->updatePlayfile(Playlist.at(
				property.Int));
		}
		break;
	case 3:
		Duration = property.Double;
		break;
	case 4:
		Volume = property.Double;
		break;
	case 5:
		Speed = property.Double;
		break;
	case 6:
		Pause = property.Bool;
		break;
	case 7:
		Mute = property.Bool;
		break;
	}

	emit this->updateTime(Position, Duration);
}
