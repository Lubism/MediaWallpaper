#include"LineEdit.hpp"
#include<QFocusEvent>
#include<QKeyEvent>

using namespace UI;

void LineEdit::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (NoFocusState == true || this->hasFocus())
		return;

	QLineEdit::mouseDoubleClickEvent(event);
	this->setFocusPolicy(Qt::ClickFocus);
	emit this->mouseDoubleClicked();
	emit this->occurFocus();
	this->setFocus();
}

void LineEdit::focusOutEvent(QFocusEvent* event)
{
	QLineEdit::focusOutEvent(event);
	emit this->lostFocus();
}

void LineEdit::focusInEvent(QFocusEvent* event)
{
	QLineEdit::focusInEvent(event);
	emit this->occurFocus();
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
