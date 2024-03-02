#include"MessageBox.hpp"

using namespace UI;

void MessageBox::setAcceptText(const QString& text)
{
	if (!Accept)
	{
		Accept = new PushButton(this);
		this->addButton(Accept, ButtonRole::AcceptRole);
	}

	Accept->setText(text);
	ButtonMap[Accept] = 0;
}

void MessageBox::setRejectText(const QString& text)
{
	if (!Reject)
	{
		Reject = new PushButton(this);
		this->addButton(Reject, ButtonRole::AcceptRole);
	}

	Reject->setText(text);
	ButtonMap[Reject] = 1;
}

void MessageBox::setHelpText(const QString& text)
{
	if (!Help)
	{
		Help = new PushButton(this);
		this->addButton(Help, ButtonRole::AcceptRole);
	}

	Help->setText(text);
	ButtonMap[Help] = 2;
}

void MessageBox::buttonFilter(QAbstractButton* button)
{
	PushButton* current = static_cast<PushButton*>(button);
	switch (ButtonMap[current])
	{
	case 0:
		emit this->acceptMessage();
		break;
	case 1:
		emit this->rejectMessage();
		break;
	case 2:
		emit this->helpMessage();
		break;
	default:
		break;
	}
}
