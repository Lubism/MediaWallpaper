#include"UI/Basic/ListWidget/ListWidget.hpp"
#include"UI/Warpper/Resources/Resources.hpp"
#include"PlaylistWidget.hpp"
#include<QResizeEvent>
#include<QCloseEvent>

using namespace UI;

void PlaylistWidget::allocation()
{
	Display = new ListWidget(this);
}

void PlaylistWidget::connection()
{
	connect(Display, &ListWidget::itemDoubleClicked, this,
		[&](QListWidgetItem* item)
		{
			Item = item;
			CurrentIndex = Display->row(item);
			emit this->fileSelected(CurrentIndex, item->text());
		});
}

void PlaylistWidget::initialization()
{
	this->setWindowTitle(Converter::CH("²¥·ÅÁÐ±í"));
	css::Setter(css::PlaylistWidget, this);
	this->setMinimumSize(560, 280);
}

void PlaylistWidget::importPlaylist(const std::vector<QString>& data)
{
	this->clearPlaylist();
	for (const QString& it : data)
		Display->addItem(it);
}

void PlaylistWidget::setPlaylistIndex(int index)
{
	CurrentIndex = index;
	Item = Display->item(index);
	Display->setItemSelected(Item, true);
}

void PlaylistWidget::clearPlaylist()
{
	Item = nullptr;
	Display->clear();
	CurrentIndex = 0;
}

void PlaylistWidget::resizeEvent(QResizeEvent* event)
{
	Converter cvt(560, 280, event);
	Widget::resizeEvent(event);

	Display->setGeometry(cvt, 0, 0, 560, 280);
	Display->setFont(cvt, 16);
}

void PlaylistWidget::closeEvent(QCloseEvent* event)
{
	event->ignore();
	this->hide();

	Item = Display->item(CurrentIndex);
	Display->setItemSelected(Item, true);
}
