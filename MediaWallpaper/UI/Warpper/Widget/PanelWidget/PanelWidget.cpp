#include"UI/Warpper/Widget/PageWidget/PageWidget.hpp"
#include"UI/Warpper/Data/PanelInfo/PanelInfo.hpp"
#include<QGridLayout>

#include"PanelWidget.hpp"

using namespace UI;

void PanelWidget::allocation(const Int& screenCount)
{
	for (auto it = 0; it < screenCount; it++) {
		Page = new PageWidget(this, it);
		this->addWidget(Page);
	}
	Page = nullptr;
}

void PanelWidget::connection()
{
}

void PanelWidget::initialization()
{

}

void PanelWidget::updateStyleSheet()
{
	for (auto it = 0; it < this->count(); it++) {
		Page = static_cast<PageWidget*>(
			this->widget(it));
		Page->updateStyleSheet();
	}
	Page = nullptr;
}

void PanelWidget::updateLanguage()
{
	for (auto it = 0; it < this->count(); it++) {
		Page = static_cast<PageWidget*>(
			this->widget(it));
		Page->updateLanguage();
	}
	Page = nullptr;
}

void PanelWidget::refreshDisplay()
{
	for (auto it = 0; it < this->count(); it++) {
		Page = static_cast<PageWidget*>(
			this->widget(it));
		Page->refreshDisplay();
	}
	Page = nullptr;
}

bool PanelWidget::readInfo()
{
	PanelInfo::ReadInfo();
	bool InfoLoadState = false;
	for (auto it = 0; it < this->count(); it++) {
		Page = static_cast<PageWidget*>(
			this->widget(it));
		InfoLoadState |= Page->readInfo();
	}
	Page = nullptr;
	return InfoLoadState;
}

void PanelWidget::saveInfo()
{
	for (auto it = 0; it < this->count(); it++) {
		Page = static_cast<PageWidget*>(
			this->widget(it));
		Page->saveInfo();
	}
	Page = nullptr;

	PanelInfo::WriteInfo();
}
