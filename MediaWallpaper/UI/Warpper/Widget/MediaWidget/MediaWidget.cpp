#include"UI/Basic/DesktopHandle/DesktopHandle.hpp"
#include"client/container/mpvEvent.hpp"
#include"client/mpvCommand.hpp"
#include"MediaWidget.hpp"
#include<QDesktopWidget>
#include<unordered_map>
#include<thread>
#include<chrono>

using namespace mpv::client;
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
	DesktopHandle::InsertProgman(this->winId());
	Property::apply(Handle, "wid", Format::Int,
		static_cast<int>(this->winId()));
	this->setPlaymode(0);
	StopState = false;
	this->hide();

	std::thread(&MediaWidget::eventThread, this).detach();
	std::thread(&MediaWidget::acquireThread, this).detach();
}

void MediaWidget::loadfile(const QString& data)
{
	if (data.isEmpty())
		return;

	this->FolderPath = data.toStdString();
	Command::async(this->Handle,
		{
			string("loadfile"),
			FolderPath,
			string("")
		},
		this->DesktopID);
	PlaylistIndex = -1;
	this->play();
	Event event;

	while (event.ID != EventID::FileLoaded)
		event.receive(this->Handle, 0.0);
	if (Playlist.size() == 1) {
		this->setPlaymode(1);
	}

	this->importPlayfile();
}

void MediaWidget::play()
{
	this->refreshDisplay();
	this->setPause(false);
	this->show();
}

void MediaWidget::last()
{
	Command::async(this->Handle,
		{
			string("playlist-prev"),
			string("")
		},
		this->DesktopID);
}

void MediaWidget::next()
{
	Command::async(this->Handle,
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
}

void MediaWidget::clearInfo()
{
	Command::async(this->Handle,
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
		Property::apply(Handle, "playback-time",
			Format::Double, data,
			this->DesktopID);

		Property::asyncAcquire(Handle, "playback-time",
			Format::Double, this->DesktopID);

		this_thread::sleep_for(chrono::milliseconds(20));
	}
}

void MediaWidget::importPlayfile()
{
	Node node;
	QString convert = "";
	size_t pos = 0, left = 0, right = 0;
	std::vector<QString>().swap(Playlist);
	Property::acquire(Handle, "playlist", Format::Node, node);
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

		Property::asyncAcquire(this->Handle, "sub-visibility",
			Format::BooleanInt, this->DesktopID);
		Property::asyncAcquire(this->Handle, "playback-time",
			Format::Double, this->DesktopID);
		Property::asyncAcquire(this->Handle, "playlist-pos",
			Format::Int, this->DesktopID);

		Property::asyncAcquire(this->Handle, "duration",
			Format::Double, this->DesktopID);
		Property::asyncAcquire(this->Handle, "volume",
			Format::Double, this->DesktopID);
		Property::asyncAcquire(this->Handle, "speed",
			Format::Double, this->DesktopID);
		Property::asyncAcquire(this->Handle, "pause",
			Format::BooleanInt, this->DesktopID);
		Property::asyncAcquire(this->Handle, "mute",
			Format::BooleanInt, this->DesktopID);
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
			if (event.ErrorCode != Error::Success)
				continue;
			if (event.ID == EventID::GetProperty)
			{
				auto iter = key.find(name);
				if (iter == key.end())
					continue;
				this->eventFilter(&event,
					iter->second);
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
