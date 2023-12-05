#include"UI/Warpper/Widget/PageWidget/PageWidget.hpp"
#include"UI/Warpper/Resources/Resources.hpp"
#include"PanelWidget.hpp"
#include<QResizeEvent>

using namespace UI;

void PanelWidget::allocation(const int& screenCount)
{
	for (int it = 0; it < screenCount; it++) {
		Page = new PageWidget(this, it);
		this->addWidget(Page);
	}
	Page = nullptr;
}

void PanelWidget::connection()
{
	connect(this, &StackedWidget::currentChanged, this,
		[&](int) { this->resize(this->size()); });
}

void PanelWidget::initialization()
{
	this->setFrameStyle(QFrame::Panel);
	css::Setter(css::PanelWidget, this);
	this->setFrameShadow(QFrame::Sunken);
}

void PanelWidget::readMediaData()
{
	int screenCount = this->count();
	for (int it = 0; it < screenCount; it++) {
		Page = reinterpret_cast<PageWidget*>(this->widget(it));
		Page->readMediaData();
	}
	Page = nullptr;
}

void PanelWidget::saveMediaData()
{
	int screenCount = this->count();
	for (int it = 0; it < screenCount; it++) {
		Page = reinterpret_cast<PageWidget*>(this->widget(it));
		Page->saveMediaData();
	}
	Page = nullptr;
}

void PanelWidget::setPage(int data)
{
	QWidget* widget = this->widget(data);
	this->setCurrentWidget(widget);
}

void PanelWidget::updateStyleSheet()
{
	int screenCount = this->count();
	for (int it = 0; it < screenCount; it++) {
		Page = reinterpret_cast<PageWidget*>(this->widget(it));
		Page->updateStyleSheet();
	}
	Page = nullptr;
}

void PanelWidget::resizeEvent(QResizeEvent* event)
{
	StackedWidget::resizeEvent(event);
	Converter cvt(410, 490, event);

	Page = reinterpret_cast<PageWidget*>(this->currentWidget());
	Page->setGeometry(cvt, 0, 0, 410, 490);
	Page = nullptr;
}
