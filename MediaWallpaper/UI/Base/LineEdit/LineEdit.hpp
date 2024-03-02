#pragma once
#include<QLineEdit>

namespace UI
{
	class LineEdit :public QLineEdit
	{
		Q_OBJECT

	public:
		inline explicit LineEdit(QWidget* parent = nullptr, const QString& text = "")
			:QLineEdit(text, parent)
		{
			this->setFrame(true);
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
		void mouseDoubleClickEvent(QMouseEvent* event) override;
		void focusOutEvent(QFocusEvent* event) override;
		void focusInEvent(QFocusEvent* event) override;
		void keyPressEvent(QKeyEvent* event) override;
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
