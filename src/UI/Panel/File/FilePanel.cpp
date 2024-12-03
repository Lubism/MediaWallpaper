#include"UI/Data/Translator/Translator.hpp"
#include"UI/Data/StyleSheet.hpp"

#include"UI/Basic/MessageBox.hpp"
#include"UI/Basic/Label.hpp"

#include<QGridLayout>
#include<QFileDialog>
#include<QAction>

#include"FilePanel.hpp"

using namespace UI;

void FilePanel::allocation()
{
	SelectDirectory = new PushButton(this, "SelectDirectory");
	UpdatePlaylist = new PushButton(this, "updatePlaylist");
	LoadConfig = new PushButton(this, "LoadConfig");
	ClearInfo = new PushButton(this, "ClearInfo");

	ClearInfoWarn = new MessageBox(this, "ClearInfoWarn");
	DirectoryPath = new LineEdit(this, "DirectoryPath");

	AtFullscreenLabel = new Label(this, "AtFullscreenLabel");
	AtFullscreenBox = new ComboBox(this);

	PlaymodeLabel = new Label(this, "PlaymodeLabel");
	PlaymodeBox = new ComboBox(this);

	AtFocusLabel = new Label(this, "AtFocusLabel");
	AtFocusBox = new ComboBox(this);

	Layout = new QGridLayout(this);
}

void FilePanel::connection()
{
	connect(SelectDirectory, &PushButton::clicked,
		this, [&]()
		{
			QString path = QFileDialog::getExistingDirectory(this, SelectDirectory->text() + "...", DirectoryPath->text() );

			if (path.isEmpty())
				return;
			
			emit this->directorySelected(path);
		});

	connect(AtFullscreenBox, &ComboBox::itemSelected, this, [&](int index) {
		emit this->atFullscreen(index);
		});
	connect(PlaymodeBox, &ComboBox::itemSelected, this, [&](int index) {
		emit this->playmode(index);
		});
	connect(AtFocusBox, &ComboBox::itemSelected, this, [&](int index) {
		emit this->atFocus(index);
		});

	connect(UpdatePlaylist, &PushButton::clicked, this, [&]() {
		emit this->updatePlaylist();
		});
	connect(LoadConfig, &PushButton::clicked, this, [&]() {
		emit this->loadConfig();
		});
	connect(ClearInfo, &PushButton::clicked, ClearInfoWarn,
		&MessageBox::show);

	connect(ClearInfoWarn, &MessageBox::acceptMessage, this, [&]() {
		emit this->clearInfo();
		});
}

void FilePanel::initLayout()
{ /*Connection for new controllors*/
	Layout->addWidget(SelectDirectory, 1, 5, 1, 1);
	Layout->addWidget(UpdatePlaylist, 2, 5, 1, 1);
	Layout->addWidget(LoadConfig, 3, 5, 1, 1);
	Layout->addWidget(ClearInfo, 4, 5, 1, 1);

	Layout->addWidget(AtFullscreenLabel, 4, 1, 1, 2);
	Layout->addWidget(AtFullscreenBox, 4, 3, 1, 2);

	Layout->addWidget(PlaymodeLabel, 2, 1, 1, 2);
	Layout->addWidget(PlaymodeBox, 2, 3, 1, 2);

	Layout->addWidget(AtFocusLabel, 3, 1, 1, 2);
	Layout->addWidget(AtFocusBox, 3, 3, 1, 2);

	Layout->addWidget(DirectoryPath, 1, 1, 1, 4);
}

void FilePanel::initialization()
{
	ClearInfoWarn->setAcceptText("YES");
	ClearInfoWarn->setRejectText("NO");

	DirectoryPath->setNoFocus(true);

	AtFocusBox->addItem("None");
	AtFocusBox->addItem("Mute");
	AtFocusBox->addItem("Pause");

	PlaymodeBox->addItem("ListLoop");
	PlaymodeBox->addItem("SingleLoop");

	AtFullscreenBox->addItem("None");
	AtFullscreenBox->addItem("Mute");
	AtFullscreenBox->addItem("Pause");

	this->setWindowTitle("File");
	this->initLayout();
}

void FilePanel::updateStyleSheet()
{
	StyleSheet::Set(this, "FilePanel");
}

void FilePanel::updateLanguage()
{
	auto text = [&](const QString& name) { return Translator::Acquire("FilePanel", name); };

	ClearInfo->setText(text("ClearInfo"));
	LoadConfig->setText(text("LoadConfig"));

	AtFocusLabel->setText(text("AtFocus"));
	PlaymodeLabel->setText(text("Playmode"));
	AtFullscreenLabel->setText(text("AtFullscreen"));

	ClearInfoWarn->setAcceptText(text("Accept"));
	ClearInfoWarn->setRejectText(text("Reject"));

	ClearInfoWarn->setText(text("ClearInfoWarn"));
	ClearInfoWarn->setWindowTitle(text("ClearInfo"));

	AtFocusBox->setItemText(0, text("None"));
	AtFocusBox->setItemText(1, text("Mute"));
	AtFocusBox->setItemText(2, text("Pause"));

	PlaymodeBox->setItemText(0, text("ListLoop"));
	PlaymodeBox->setItemText(1, text("SingleLoop"));

	AtFullscreenBox->setItemText(0, text("None"));
	AtFullscreenBox->setItemText(1, text("Mute"));
	AtFullscreenBox->setItemText(2, text("Pause"));

	UpdatePlaylist->setText(text("UpdatePlaylist"));
	SelectDirectory->setText(text("SelectDirectory"));

	DirectoryPath->setPlaceholderText(text("DirectoryPath"));
}
