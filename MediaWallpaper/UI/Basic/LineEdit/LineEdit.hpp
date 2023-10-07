#pragma once
#include"UI/Basic/Font/Font.hpp"
#include<QLineEdit>

namespace UI
{
	class LineEdit :public QLineEdit
	{
		Q_OBJECT

	public:
		inline explicit LineEdit(QWidget* parent = nullptr,
			const QString& text = "")
			:QLineEdit(text, parent)
		{
			this->setFrame(true);
			this->setFocusPolicy(Qt::NoFocus);
			this->setAlignment(Qt::AlignCenter);
			this->setContextMenuPolicy(Qt::NoContextMenu);
		}

		inline void setGeometry(const Converter& cvt,
			int x, int y, int width, int height)
		{
			QWidget::setGeometry(cvt.width(x), cvt.height(y),
				cvt.width(width), cvt.height(height));
		}

		inline void setFont(const Converter& cvt,
			double num)
		{
			QWidget::setFont(Font(cvt, num,
				this->height()));
		}

		inline void setNoFocus(bool data)
		{
			NoFocusState = data;
		}
	protected:
		void mouseDoubleClickEvent(QMouseEvent* event) override;
		void keyPressEvent(QKeyEvent* event) override;
	signals:
		void textModified(const QString& text);
		void mouseDoubleClicked();
		void lostFocus();
	private:
		bool NoFocusState = false;
	public:
		inline virtual ~LineEdit() {}
	};
}