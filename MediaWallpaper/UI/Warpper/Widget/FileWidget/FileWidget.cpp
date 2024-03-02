#include"UI/Warpper/Widget/DirInfoWidget/DirInfoWidget.hpp"
#include"UI/Warpper/Data/Translator/Translator.hpp"
#include"UI/Base/MessageBox/MessageBox.hpp"
#include"UI/Warpper/Data/StyleSheet.hpp"
#include"UI/Base/ComboBox/ComboBox.hpp"
#include"UI/Base/LineEdit/LineEdit.hpp"
#include"UI/Base/Button/PushButton.hpp"
#include"UI/Base/Label.hpp"
#include<QGridLayout>
#include<QFileDialog>
#include<QTextEdit>

#include"FileWidget.hpp"

using namespace UI;

void FileWidget::allocation()
{
	SelectDirectory = new PushButton(this, "SelectDirectory");
	RefreshDisplay = new PushButton(this, "RefreshDisplay");
	ClearInfo = new PushButton(this, "ClearInfo");

	ClearInfoWarn = new MessageBox(this, "",
		QMessageBox::Warning);
	DirInfo = new DirInfoWidget(this);

	PlaymodeLabel = new Label(this, "PlaymodeLabel");
	DirectoryPath = new LineEdit(this);
	PlaymodeBox = new ComboBox(this);

	Layout = new QGridLayout(this);
}

void FileWidget::connection()
{
	connect(SelectDirectory, &PushButton::clicked, this, &FileWidget::selectDirectory);
	connect(PlaymodeBox, &ComboBox::itemSelected, this, [&](int index)
		{emit this->playmode(index); });

	connect(RefreshDisplay, &PushButton::clicked, this, [&](bool)
		{emit this->refreshDisplay(); });
	connect(ClearInfo, &PushButton::clicked, ClearInfoWarn,
		&MessageBox::show);

	connect(ClearInfoWarn, &MessageBox::acceptMessage,
		this, &FileWidget::clearInfo);
}

void FileWidget::initLayout()
{
	Layout->addWidget(SelectDirectory, 3, 1, 1, 2);
	Layout->addWidget(RefreshDisplay, 4, 1, 1, 1);
	Layout->addWidget(ClearInfo, 4, 2, 1, 1);
	Layout->addWidget(DirInfo, 2, 3, -1, -1);

	Layout->addWidget(DirectoryPath, 1, 1, 1, 4);
	Layout->addWidget(PlaymodeLabel, 2, 1, 1, 1);
	Layout->addWidget(PlaymodeBox, 2, 2, 1, 1);
}

void FileWidget::initialization()
{
	this->initLayout();

	DirectoryPath->setNoFocus(true);
	DirectoryPath->setPlaceholderText("DirectoryPath");

	PlaymodeBox->addItem("ListLoop");
	PlaymodeBox->addItem("SingleLoop");
}

void FileWidget::selectDirectory()
{
	QString str = QFileDialog::getExistingDirectory(this,
		SelectDirectory->text() + "...",
		DirectoryPath->text()
	);

	if (str.isEmpty()) return;
	emit this->directorySelected(str);
}

void FileWidget::setDirectoryPath(const QString& path)
{
	DirInfo->importDirectory(path);
	DirectoryPath->setText(path);
}

void FileWidget::setPlaymode(Int index)
{
	PlaymodeBox->setCurrentIndex(index);
}

void FileWidget::updateStyleSheet()
{
	StyleSheet::Set(this, "FileWidget");
	DirInfo->updateStyleSheet();
}

void FileWidget::updateLanguage()
{
	auto receive = [](const QString& name) {return Translator::Acquire("FileGroup", name); };
	if (!Translator::TranslationAvaliable()) return;
	this->setWindowTitle(receive("File"));
	DirInfo->updateLanguage();

	SelectDirectory->setText(receive("SelectDirectory"));
	RefreshDisplay->setText(receive("RefreshDisplay"));
	ClearInfo->setText(receive("ClearInfo"));

	DirectoryPath->setPlaceholderText(receive("DirectoryPath"));
	PlaymodeLabel->setText(receive("Playmode"));

	PlaymodeBox->setItemText(0, receive("ListLoop"));
	PlaymodeBox->setItemText(1, receive("SingleLoop"));

	ClearInfoWarn->setAcceptText(receive("Accept"));
	ClearInfoWarn->setRejectText(receive("Reject"));
	ClearInfoWarn->setText(receive("ClearInfoWarn"));
	ClearInfoWarn->setWindowTitle(receive("ClearInfo"));
}
