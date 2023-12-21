#include"UI/Basic/Button/PushButton.hpp"
#include"MessageBox.hpp"

using namespace UI;

MessageBox::MessageBox(QWidget* parent, const QString& title)
	:QMessageBox(parent)
{
	connect(this, &QMessageBox::buttonClicked,
		this, &MessageBox::buttonFilter);
	this->setWindowTitle(title);
}

void MessageBox::setAcceptText(const QString& text)
{
	Accept = new PushButton(this);

	this->addButton(Accept, ButtonRole::AcceptRole);
	Accept->setText(text);
}

void MessageBox::setRejectText(const QString& text)
{
	Reject = new PushButton(this);

	this->addButton(Reject, ButtonRole::RejectRole);
	Reject->setText(text);
}

void MessageBox::setHelpText(const QString& text)
{
	Help = new PushButton(this);

	this->addButton(Help, ButtonRole::HelpRole);
	Help->setText(text);
}

void MessageBox::buttonFilter(QAbstractButton* button)
{
	PushButton* curButton = static_cast<PushButton*>(button);

	if (curButton == Accept)
		emit this->acceptMessage();
	else if (curButton == Reject)
		emit this->rejectMessage();
	else if (curButton == Help)
		emit this->helpMessage();
}
