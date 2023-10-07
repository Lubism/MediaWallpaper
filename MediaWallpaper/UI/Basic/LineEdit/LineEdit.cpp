#include"LineEdit.hpp"
#include<QMouseEvent>
#include<QKeyEvent>

using namespace UI;

void LineEdit::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (NoFocusState == true)
		return;

	QLineEdit::mouseDoubleClickEvent(event);
	this->setFocusPolicy(Qt::ClickFocus);
	emit this->mouseDoubleClicked();
	this->setFocus();
}

void LineEdit::keyPressEvent(QKeyEvent* event)
{
	QLineEdit::keyPressEvent(event);
	switch (event->key())
	{
	case Qt::Key::Key_Enter:
	case Qt::Key::Key_Return:
		emit this->textModified(this->text());
		emit this->lostFocus();

		this->setFocusPolicy(Qt::NoFocus);
		this->clearFocus();
		break;
	case Qt::Key::Key_Escape:
		this->setFocusPolicy(Qt::NoFocus);
		emit this->lostFocus();
		this->clearFocus();
		break;
	}
}
