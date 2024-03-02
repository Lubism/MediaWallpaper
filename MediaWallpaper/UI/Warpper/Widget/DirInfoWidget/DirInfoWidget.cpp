#include"UI/Warpper/Data/Translator/Translator.hpp"
#include"UI/Warpper/Data/StyleSheet.hpp"
#include"UI/Base/Button/PushButton.hpp"
#include"UI/Base/Label.hpp"
#include<QGridLayout>
#include<QListWidget>
#include<QDir>

#include"DirInfoWidget.hpp"

using namespace UI;

static const QDir::Filters Filter = QDir::AllEntries | QDir::NoDotAndDotDot;

void DirInfoWidget::allocation()
{
	Layout = new QGridLayout(this);
	List = new QListWidget(this);
	Back = new PushButton(this);
	Name = new Label(this,
		"Name");
}

void DirInfoWidget::connection()
{
	connect(List, &QListWidget::itemDoubleClicked, this,
		[&](QListWidgetItem* item)
		{
			QDir dir(item->text());
			auto dirList = dir.entryInfoList(Filter);

			if (dirList.isEmpty()) return;
			DirStack.push_back(CurrentDir);
			CurrentDir = item->text();

			this->importDirList(dirList);
		});
	
	connect(Back, &PushButton::clicked, this,
		[&](bool)
		{
			if (DirStack.empty()) return;
			CurrentDir = DirStack.back();
			DirStack.pop_back();

			auto dirList = QDir(CurrentDir).entryInfoList(Filter);
			this->importDirList(dirList);
		});
}

void DirInfoWidget::initLayout()
{
	Layout->setMargin(5);
	Layout->addWidget(List, 2, 1, -1, 4);
	Layout->addWidget(Back, 1, 4, 1, 1);
	Layout->addWidget(Name, 1, 1, 1, 3);
}

void DirInfoWidget::initialization()
{
	List->setFocusPolicy(Qt::NoFocus);

	this->initLayout();
	this->setFocusPolicy(Qt::NoFocus);
	this->setFrameShape(QFrame::Panel);
	this->setFrameShadow(QFrame::Sunken);
}

void DirInfoWidget::importDirList(const QFileInfoList& dirList)
{
	List->clear();
	for (auto& it : dirList)
	{
		List->addItem(it.filePath());
	}
}

void DirInfoWidget::importDirectory(const QString& path)
{
	if (path.isEmpty())
	{
		CurrentDir = "";
		List->clear();
		return;
	}

	CurrentDir = path;
	while (!DirStack.empty()) DirStack.pop_back();

	QDir dir(CurrentDir);
	auto dirList = dir.entryInfoList(Filter);

	this->importDirList(dirList);
}

void DirInfoWidget::updateStyleSheet()
{
	StyleSheet::Set(this, "DirInfoWidget");
}

void DirInfoWidget::updateLanguage()
{
	auto receive = [](const QString& name) {return Translator::Acquire("DirInfoGroup", name); };
	if (!Translator::TranslationAvaliable()) return;

	Back->setText(receive("Back"));
	Name->setText(receive("Name"));
}
