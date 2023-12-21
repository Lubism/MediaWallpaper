#include"UI/Warpper/Resources/Resources.hpp"
#include"UI/Basic/Button/PushButton.hpp"
#include"UI/Basic/ComboBox/ComboBox.hpp"
#include"TerminalGroupBox.hpp"
#include"UI/Basic/Label.hpp"
#include<QResizeEvent>

using namespace UI;

void TerminalGroupBox::allocation()
{
	AutobootLabel = new Label(this);
	PanelLabel = new Label(this);

	AutobootBox = new ComboBox(this);
	PanelBox = new ComboBox(this);

	UpdatePanelButton = new PushButton(this);
	UpdatePanelLabel = new Label(this);
}

void TerminalGroupBox::connection()
{
	connect(AutobootBox, &ComboBox::itemSelected,
		this, [&](int index)
		{
			emit this->autoboot(static_cast<bool>(index));
		});

	connect(PanelBox, &ComboBox::itemSelected,
		this, [&](int index)
		{
			emit this->selectPanel(index);
		});

	connect(UpdatePanelButton, &PushButton::clicked,
		this, [&]()
		{
			emit this->updatePanel();
			this->updateStyleSheet();
		});
}

void TerminalGroupBox::initialization(const int& screenCount)
{
	UpdatePanelLabel->setText(Converter::CH("更新界面样式"));
	UpdatePanelButton->setText(Converter::CH("更新"));
	AutobootLabel->setText(Converter::CH("开机启动"));
	PanelLabel->setText(Converter::CH("当前面板"));

	AutobootBox->addItem(Converter::CH("关闭"));
	AutobootBox->addItem(Converter::CH("开启"));

	QString prefix = Converter::CH("显示器");
	for (int it = 0; it < screenCount; it++)
	{
		PanelBox->addItem(prefix + QString::number(it));
	}

	this->updateStyleSheet();
}

void TerminalGroupBox::setAutoboot(bool data)
{
	AutobootBox->setCurrentIndex(static_cast<int>(data));
}

void TerminalGroupBox::updateStyleSheet()
{
	css::Setter(css::terminalGroup::AutobootLabel, AutobootLabel);
	css::Setter(css::terminalGroup::PanelLabel, PanelLabel);

	css::Setter(css::terminalGroup::AutobootBox, AutobootBox);
	css::Setter(css::terminalGroup::PanelBox, PanelBox);

	css::Setter(css::terminalGroup::UpdatePanelButton, UpdatePanelButton);
	css::Setter(css::terminalGroup::UpdatePanelLabel, UpdatePanelLabel);

	css::Setter(css::TerminalGroupBox, this);
}

void TerminalGroupBox::resizeEvent(QResizeEvent* event)
{
	Converter cvt(330, 530, event);
	GroupBox::resizeEvent(event);

	AutobootLabel->setGeometry(cvt, 10, 100, 110, 40);
	PanelLabel->setGeometry(cvt, 10, 40, 110, 40);

	AutobootBox->setGeometry(cvt, 130, 100, 120, 40);
	PanelBox->setGeometry(cvt, 130, 40, 120, 40);

	UpdatePanelButton->setGeometry(cvt, 170, 150, 80, 40);
	UpdatePanelLabel->setGeometry(cvt, 10, 150, 150, 40);

	AutobootLabel->setFont(cvt, 16);
	PanelLabel->setFont(cvt, 16);

	AutobootBox->setFont(cvt, 14);
	PanelBox->setFont(cvt, 14);

	UpdatePanelButton->setFont(cvt, 14);
	UpdatePanelLabel->setFont(cvt, 16);

	this->setFont(cvt, 16);
}
