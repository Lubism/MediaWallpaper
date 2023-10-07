#include"MediaData.hpp"
#include<fstream>
#include<QDir>

namespace UI
{
	struct MediaDataStruct
	{
		char FolderPath[1024] = {};
		bool SubVisisbility = true;
		int WidgetHeight = 280;
		int WidgetWidth = 560;
		int PlaylistIndex = 0;
		double Position = 0.0;
		double Volume = 0.0;
		double Speed = 0.0;
		bool Pause = false;
		bool Mute = false;
		int Playmode = 0;
	public:
		inline void copystr(const std::string& data)
		{
			size_t size = data.size() > 1024 ? 1024 : data.size();
			for (size_t it = 0; it < size; it++)
				FolderPath[it] = data.at(it);
		}
	};
}

using namespace std;
using namespace UI;

MediaData::MediaData(QObject* parent,
	const int& screenIndex)
	:QObject(parent)
{
	auto path = QDir::currentPath() + "/mediaData";
	ScreenIndex = screenIndex;
	QDir dir(path);

	if (dir.exists() == false)
		dir.mkdir(path);
	this->read();
}

void MediaData::read()
{
	string filePath = "mediaData\\screenData#" + to_string(ScreenIndex);
	MediaDataStruct data;
	ifstream reader(filePath, ios::binary);
	if (reader.fail()) { reader.close(); return; }
	reader.read(reinterpret_cast<char*>(&data),
		sizeof(data));
	FolderPath.assign(data.FolderPath);

	SubVisisbility = data.SubVisisbility;
	PlaylistIndex = data.PlaylistIndex;
	WidgetHeight = data.WidgetHeight;
	WidgetWidth = data.WidgetWidth;
	Playmode = data.Playmode;
	Position = data.Position;
	Volume = data.Volume;
	Speed = data.Speed;
	Pause = data.Pause;
	Mute = data.Mute;

	reader.close();
}

void MediaData::save()
{
	string filePath = "mediaData\\screenData#" + to_string(ScreenIndex);
	MediaDataStruct data;

	ofstream writer(filePath, ios::binary);
	data.copystr(FolderPath);

	data.SubVisisbility = SubVisisbility;
	data.PlaylistIndex = PlaylistIndex;
	data.WidgetHeight = WidgetHeight;
	data.WidgetWidth = WidgetWidth;
	data.Playmode = Playmode;
	data.Position = Position;
	data.Volume = Volume;
	data.Speed = Speed;
	data.Pause = Pause;
	data.Mute = Mute;

	writer.write(reinterpret_cast<char*>(&data),
		sizeof(data));

	writer.close();
}

void MediaData::clearInfo()
{
	string filePath = "mediaData\\screenData#" + to_string(ScreenIndex);
	int no_use = std::remove(filePath.data());

	SubVisisbility = true;
	WidgetHeight = 280;
	WidgetWidth = 560;
	PlaylistIndex = 0;
	FolderPath = "";
	Playmode = 0;

	Position = 0.0;
	Volume = 100.0;
	Speed = 1.0;

	Pause = false;
	Mute = false;
}
