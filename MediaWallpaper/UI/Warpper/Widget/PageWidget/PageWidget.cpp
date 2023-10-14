#include"UI/Warpper/GroupBox/BasicGroupBox/BasicGroupBox.hpp"
#include"UI/Warpper/GroupBox/FileGroupBox/FileGroupBox.hpp"
#include"UI/Warpper/Widget/MediaWidget/MediaWidget.hpp"
#include"UI/Warpper/Resources/Resources.hpp"
#include"PageWidget.hpp"
#include<QResizeEvent>
#include<thread>
#include<chrono>

using namespace UI;

void PageWidget::allocation(const int& screenIndex)
{
	Basic = new BasicGroupBox(this, screenIndex);
	File = new FileGroupBox(this);

	Media = new MediaWidget(this, screenIndex);
	Data = new MediaData(this, screenIndex);
}

void PageWidget::connection()
{
	this->connection_file();
	this->connection_basic();
	this->connection_media();
}

void PageWidget::initialization()
{
	this->updateStyleSheet();
}

void PageWidget::connection_file()
{
	connect(File, &FileGroupBox::fileSelected, this,
		[&](int index, const QString& filename)
		{
			Media->setPlaylistIndex(index);
			Basic->setFileName(filename);
		});
	connect(File, &FileGroupBox::folderSelected,
		Media, &MediaWidget::loadfile);
	connect(File, &FileGroupBox::refreshDisplay,
		this, [&]()
		{
			Media->refreshDisplay();
		});
	connect(File, &FileGroupBox::clearInfo,
		this, [&]()
		{
			Media->clearInfo();
			Basic->clearInfo();
			Data->clearInfo();
		});

	connect(File, &FileGroupBox::playmodeSelected,
		Media, &MediaWidget::setPlaymode);
}

void PageWidget::connection_basic()
{
	connect(Basic, &BasicGroupBox::position, Media,
		&MediaWidget::setPosition);
	connect(Basic, &BasicGroupBox::volume, Media,
		&MediaWidget::setVolume);
	connect(Basic, &BasicGroupBox::speed, Media,
		&MediaWidget::setSpeed);

	connect(Basic, &BasicGroupBox::subVisibility, Media,
		&MediaWidget::setSubVisibility);
	connect(Basic, &BasicGroupBox::pause,
		this, [&](bool data)
		{
			if (StopState == true && data == false) {
				StopState = false;
				Media->play();
			}
			else {
				Media->setPause(data);
			}
		});
	connect(Basic, &BasicGroupBox::mute, Media,
		&MediaWidget::setMute);

	connect(Basic, &BasicGroupBox::last,
		Media, &MediaWidget::last);
	connect(Basic, &BasicGroupBox::stop,
		this, [&]()
		{
			Media->stop();
			StopState = true;
		});
	connect(Basic, &BasicGroupBox::next,
		Media, &MediaWidget::next);
}

void PageWidget::connection_media()
{
	connect(Media, &MediaWidget::updateTime, Basic,
		&BasicGroupBox::setPosition);
	connect(Media, &MediaWidget::updatePlaylist, this,
		[&](const std::vector<QString>& data)
		{
			if (!data.empty()) Basic->setFileName(data.at(0));
			File->importPlaylist(data);
		});
	connect(Media, &MediaWidget::updatePlayfile,
		Basic, &BasicGroupBox::setFileName);
	connect(Media, &MediaWidget::updatePlaylistIndex,
		File, &FileGroupBox::setPlaylistIndex);
}

void PageWidget::readMediaData()
{
	Data->read();
	Media->importData(*Data);

	Basic->setMute(Data->Mute);
	Basic->setSpeed(Data->Speed);
	Basic->setPause(Data->Pause);
	Basic->setVolume(Data->Volume);
	Basic->setSubVisibility(Data->SubVisisbility);

	File->setPlaymode(Data->Playmode);
	File->setPlaylistSize(Data->WidgetWidth, Data->WidgetHeight);
	File->setFolderPath(QString::fromStdString(Data->FolderPath));
}

void PageWidget::saveMediaData()
{
	File->playlistSize(Data->WidgetWidth, Data->WidgetHeight);
	Media->exportData(*Data);
	Data->save();
}

void PageWidget::updateStyleSheet()
{
	css::Setter(css::PageWidget, this);
	Basic->updateStyleSheet();
	File->updateStyleSheet();
}

void PageWidget::resizeEvent(QResizeEvent* event)
{
	Converter cvt(410, 490, event);
	QWidget::resizeEvent(event);

	Basic->setGeometry(cvt, 10, 10, 390, 230);
	File->setGeometry(cvt, 10, 250, 390, 230);
}