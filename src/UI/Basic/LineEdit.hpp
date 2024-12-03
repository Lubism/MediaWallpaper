#pragma once
#include<QFocusEvent>
#include<QKeyEvent>
#include<QLineEdit>

namespace UI
{
	class LineEdit :public QLineEdit
	{
		Q_OBJECT

	public:
		inline explicit LineEdit(QWidget* parent = nullptr, const QString& text = "")
			:QLineEdit(parent)
		{
			this->setFrame(true);
			this->setPlaceholderText(text);
			this->setFocusPolicy(Qt::NoFocus);
			this->setAlignment(Qt::AlignCenter);
			this->setContextMenuPolicy(Qt::NoContextMenu);
			this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		}

		inline void importText(const QString& text)
		{
			QLineEdit::setText(text);
		}

		inline void setText(const QString& text)
		{
			if (this->hasFocus()) return;
			QLineEdit::setText(text);
		}

		inline void setNoFocus(bool data)
		{
			NoFocusState = data;
		}
	protected:
		inline void mouseDoubleClickEvent(QMouseEvent* event) override
		{
			if (NoFocusState == true || this->hasFocus())
				return;

			QLineEdit::mouseDoubleClickEvent(event);
			this->setFocusPolicy(Qt::ClickFocus);
			emit this->mouseDoubleClicked();
			emit this->occurFocus();
			this->setFocus();
		}

		inline void focusOutEvent(QFocusEvent* event) override
		{
			QLineEdit::focusOutEvent(event);
			emit this->lostFocus();
		}

		inline void focusInEvent(QFocusEvent* event) override
		{
			QLineEdit::focusInEvent(event);
			emit this->occurFocus();
		}

		void keyPressEvent(QKeyEvent* event) override
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
	signals:
		void textModified(const QString& text);

		void mouseDoubleClicked();
		void occurFocus();
		void lostFocus();
	private:
		bool NoFocusState = false;
		QString Before = "";
	public:
		inline virtual ~LineEdit() {}
	};
}
