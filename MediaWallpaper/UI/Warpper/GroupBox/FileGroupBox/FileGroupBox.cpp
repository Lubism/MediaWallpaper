#include"UI/Warpper/Widget/PlaylistWidget/PlaylistWidget.hpp"
#include"UI/Basic/PushButton/PushButton.hpp"
#include"UI/Basic/MessageBox/MessageBox.hpp"
#include"UI/Warpper/Resources/Resources.hpp"
#include"UI/Basic/ComboBox/ComboBox.hpp"
#include"UI/Basic/LineEdit/LineEdit.hpp"
#include"UI/Basic/Label/Label.hpp"
#include"FileGroupBox.hpp"
#include<QResizeEvent>
#include<QFileDialog>

using namespace UI;

void FileGroupBox::allocation()
{
	RefreshDisplay = new PushButton(this);
	OpenPlaylist = new PushButton(this);
	SelectFolder = new PushButton(this);
	ClearInfo = new PushButton(this);

	PlaymodeBox = new ComboBox(this);
	FolderPath = new LineEdit(this);
	PlaymodeLabel = new Label(this);

	ClearInfoWarn = new MessageBox(this, "Are you sure about that ?");
	Playlist = new PlaylistWidget(this);
}

void FileGroupBox::connection()
{
	connect(RefreshDisplay, &PushButton::clicked,
		this, [&]()
		{
			emit this->refreshDisplay();
		});
	connect(OpenPlaylist, &PushButton::clicked,
		Playlist, &PlaylistWidget::show);
	connect(SelectFolder, &PushButton::clicked,
		this, [&]()
		{
			auto folderPath = QFileDialog::getExistingDirectory(this,
				Converter::CH("选择要播放的文件夹..."),
				"");
			if (folderPath.isEmpty()) return;
			FolderPath->setText(folderPath);
			emit this->folderSelected(folderPath);
		});
	connect(ClearInfo, &PushButton::clicked,
		ClearInfoWarn, &MessageBox::exec);

	connect(PlaymodeBox, &ComboBox::itemSelected,
		this, [&](int index)
		{
			emit this->playmodeSelected(index);
		});

	connect(FolderPath, &LineEdit::textChanged,
		this, [&](const QString& text)
		{
			if (text.isEmpty()) {
				FolderPath->setText(Converter::CH(
					"无播放的文件夹"));
			}
		});

	connect(ClearInfoWarn, &MessageBox::acceptMessage,
		this, [&]()
		{
			Playlist->clearPlaylist();
			this->setFolderPath("");
			this->setPlaymode(0);

			emit this->clearInfo();
		});
	connect(Playlist, &PlaylistWidget::fileSelected, this,
		[&](int index, const QString& filename)
		{
			emit this->fileSelected(index, filename);
		});
}

void FileGroupBox::initialization()
{
	css::Setter(css::FileGroupBox, this);

	RefreshDisplay->setText(Converter::CH("刷新显示"));
	OpenPlaylist->setText(Converter::CH("播放列表"));
	SelectFolder->setText(Converter::CH("选择文件夹"));
	ClearInfo->setText(Converter::CH("清空面板信息"));

	PlaymodeBox->addItem(Converter::CH("列表循环"));
	PlaymodeBox->addItem(Converter::CH("单项循环"));

	FolderPath->setText(Converter::CH("没有要播放的文件夹"));
	PlaymodeLabel->setText(Converter::CH("播放模式"));

	ClearInfoWarn->setText(Converter::CH("确认清空面板信息 ？") + "\n" +
		Converter::CH("此操作不可逆 !"));
	ClearInfoWarn->setAcceptText(Converter::CH("是的，我还有别的事要做"));
	ClearInfoWarn->setRejectText(Converter::CH("不不不，爷手贱点到而已"));
	ClearInfoWarn->setIcon(QMessageBox::Warning);

	FolderPath->setNoFocus(true);
	this->updateStyleSheet();
}

void FileGroupBox::importPlaylist(const std::vector<QString>& data)
{
	Playlist->importPlaylist(data);
}

void FileGroupBox::playlistSize(int& width, int& height)
{
	QSize size = Playlist->size();
	height = size.height();
	width = size.width();
}

void FileGroupBox::setPlaylistIndex(int index)
{
	Playlist->setPlaylistIndex(index);
}

void FileGroupBox::updateStyleSheet()
{
	css::Setter(css::fileGroup::RefreshDisplay, RefreshDisplay);
	css::Setter(css::fileGroup::OpenPlaylist, OpenPlaylist);
	css::Setter(css::fileGroup::SelectFolder, SelectFolder);
	css::Setter(css::fileGroup::ClearInfo, ClearInfo);

	css::Setter(css::fileGroup::PlaymodeBox, PlaymodeBox);
	css::Setter(css::fileGroup::FolderPath, FolderPath);
	css::Setter(css::fileGroup::PlaymodeLabel, PlaymodeLabel);
	css::Setter(css::fileGroup::ClearInfoWarn, ClearInfoWarn);

	css::Setter(css::PlaylistWidget, Playlist);
	css::Setter(css::FileGroupBox, this);
}

void FileGroupBox::setPlaylistSize(const int& width, const int& height)
{
	Playlist->resize(width, height);
}

void FileGroupBox::setFolderPath(const QString& path)
{
	FolderPath->setText(path);
}

void FileGroupBox::setPlaymode(int mode)
{
	PlaymodeBox->setCurrentIndex(mode);
}

void FileGroupBox::resizeEvent(QResizeEvent* event)
{
	Converter cvt(390, 230, event);
	QGroupBox::resizeEvent(event);

	RefreshDisplay->setGeometry(cvt, 10, 180, 110, 40);
	OpenPlaylist->setGeometry(cvt, 10, 130, 110, 40);
	SelectFolder->setGeometry(cvt, 130, 130, 120, 40);
	ClearInfo->setGeometry(cvt, 130, 180, 120, 40);

	PlaymodeBox->setGeometry(cvt, 130, 80, 120, 40);
	FolderPath->setGeometry(cvt, 10, 30, 370, 30);
	PlaymodeLabel->setGeometry(cvt, 10, 80, 110, 40);

	RefreshDisplay->setFont(cvt, 14);
	OpenPlaylist->setFont(cvt, 14);
	SelectFolder->setFont(cvt, 12);
	ClearInfo->setFont(cvt, 12);

	PlaymodeBox->setFont(cvt, 14);
	FolderPath->setFont(cvt, 14);
	PlaymodeLabel->setFont(cvt, 16);

	this->setFont(cvt, 16);
}
