#include"UI/Warpper/Widget/PlaylistWidget/PlaylistWidget.hpp"
#include"UI/Warpper/Widget/BasicWidget/BasicWidget.hpp"
#include"UI/Warpper/Widget/MediaWidget/MediaWidget.hpp"
#include"UI/Warpper/Widget/FileWidget/FileWidget.hpp"
#include"UI/Warpper/Data/Translator/Translator.hpp"
#include"UI/Warpper/Data/PanelInfo/PanelInfo.hpp"
#include<thread>
#include<chrono>

#include"PageWidget.hpp"

using namespace UI;

void PageWidget::allocation()
{
	Playlist = new PlaylistWidget(this);

	Basic = new BasicWidget(this, DesktopID);
	Media = new MediaWidget(this, DesktopID);

	File = new FileWidget(this);
}

void PageWidget::connection()
{
	connect(this, &PageWidget::tabBarClicked, this,
		[&](int index)
		{
			if (index == this->indexOf(Playlist))
				Playlist->resetSelected();
		});

	connection_file();
	connection_basic();
	connection_media();
	connection_playlist();
}

void PageWidget::initLayout()
{
	// Preserved, doing implementation while having mutiple monitor
}

void PageWidget::initialization()
{
	this->addTab(Basic, "Basic");
	this->addTab(File, "File");
	this->addTab(Playlist,
		"Playlist");
}

void PageWidget::connection_file()
{
	connect(File, &FileWidget::directorySelected, Media,
		&MediaWidget::loadFile);
	connect(File, &FileWidget::refreshDisplay, Media,
		&MediaWidget::refreshDisplay);
	connect(File, &FileWidget::clearInfo, Media,
		&MediaWidget::clearInfo);
	connect(File, &FileWidget::playmode, Media,
		&MediaWidget::setPlaymode);
}

void PageWidget::connection_basic()
{
	connect(Basic, &BasicWidget::position, Media,
		&MediaWidget::setPosition);
	connect(Basic, &BasicWidget::volume, Media,
		&MediaWidget::setVolume);
	connect(Basic, &BasicWidget::speed, Media,
		&MediaWidget::setSpeed);

	connect(Basic, &BasicWidget::subVisibility, Media,
		&MediaWidget::setSubVisibility);
	connect(Basic, &BasicWidget::pause, Media,
		&MediaWidget::setPause);
	connect(Basic, &BasicWidget::mute, Media,
		&MediaWidget::setMute);

	connect(Basic, &BasicWidget::last, Media,
		&MediaWidget::last);
	connect(Basic, &BasicWidget::next, Media,
		&MediaWidget::next);
	connect(Basic, &BasicWidget::stop, Media,
		&MediaWidget::stop);
}

void PageWidget::connection_media()
{
	connect(Media, &MediaWidget::updateCurrentIndex, Playlist,
		&PlaylistWidget::setCurrentIndex,
		Qt::DirectConnection);
	connect(Media, &MediaWidget::updatePlaylist, Playlist,
		&PlaylistWidget::importList);

	connect(Media, &MediaWidget::updateSubVisibility, Basic,
		&BasicWidget::setSubVisibility);
	connect(Media, &MediaWidget::currentFileChanged, Basic,
		&BasicWidget::setFileName);
	connect(Media, &MediaWidget::updateVolume, Basic,
		&BasicWidget::setVolume);
	connect(Media, &MediaWidget::updateSpeed, Basic,
		&BasicWidget::setSpeed);
	connect(Media, &MediaWidget::updateMute, Basic,
		&BasicWidget::setMute);
	connect(Media, &MediaWidget::updateTime, Basic,
		&BasicWidget::setPosition);

	connect(Media, &MediaWidget::updateDirectory, File,
		&FileWidget::setDirectoryPath);
	connect(Media, &MediaWidget::updatePlaymode, File,
		&FileWidget::setPlaymode,
		Qt::QueuedConnection);
}

void PageWidget::connection_playlist()
{
	connect(Playlist, &PlaylistWidget::fileSelected, Media,
		&MediaWidget::setCurrentIndex);
}

void PageWidget::updateStyleSheet()
{
	Playlist->updateStyleSheet();
	Media->updateStyleSheet();
	Basic->updateStyleSheet();
	File->updateStyleSheet();
}

void PageWidget::updateLanguage()
{
	if (!Translator::TranslationAvaliable()) return;
	Playlist->updateLanguage();
	Basic->updateLanguage();
	File->updateLanguage();

	this->setTabText(1, Translator::Acquire("FileGroup", "File"));
	this->setTabText(0, Translator::Acquire("BasicGroup", "Basic"));
	this->setTabText(2, Translator::Acquire("PlaylistGroup", "Playlist"));
}

void PageWidget::refreshDisplay()
{
	Media->refreshDisplay();
}

void PageWidget::setMediaInfo()
{
	QString group = "Desktop#" + QString::number(DesktopID);
	auto acquire = [&](const QString& name) {return PanelInfo::Acquire(group, name); };

	Media->setPlaymode(acquire("Playmode").toInt());
	Media->setCurrentIndex(acquire("CurrentIndex").toInt());

	Media->setSubVisibility(acquire("SubVisibility").toInt());
	Media->setStartTime(acquire("Position").toDouble());
	Media->setVolume(acquire("Volume").toDouble());
	Media->setSpeed(acquire("Speed").toDouble());
	Media->setMute(acquire("Mute").toDouble());
}

bool PageWidget::readInfo()
{
	QString group = "Desktop#" + QString::number(DesktopID);
	if (Media->loadFile(PanelInfo::Acquire(group,
		"DirectoryPath")))
	{
		this->setMediaInfo();
		return true;
	}

	return false;
}

void PageWidget::saveInfo()
{
	QString group = "Desktop#" + QString::number(DesktopID);
	auto apply = [&](const QString& name, const QString& value)
		{
			PanelInfo::Apply(group, name, value);
		};

	Int iData = 0;
	bool bData = 0;
	double dData = 0.0;
	QString sData = "";

	Media->directory(sData);
	apply("DirectoryPath", sData);

	Media->currentIndex(iData);
	apply("CurrentIndex", QString::number(iData));

	Media->playmode(iData);
	apply("Playmode", QString::number(iData));

	Media->subVisibility(bData);
	apply("SubVisibility", QString::number(bData));

	Media->position(dData);
	apply("Position", QString::number(dData));

	Media->volume(dData);
	apply("Volume", QString::number(dData));

	Media->speed(dData);
	apply("Speed", QString::number(dData));

	Media->mute(bData);
	apply("Mute", QString::number(bData));
}
