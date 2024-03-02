#pragma once
#include"UI/Base/Button/PushButton.hpp"
#include<unordered_map>
#include<QMessageBox>

class QAbstractButton;

namespace UI
{
	class PushButton;

	class MessageBox :public QMessageBox
	{
		Q_OBJECT

	public:
		inline explicit MessageBox(QWidget* parent = nullptr, const QString& title = "",
			Icon type = Icon::NoIcon)
			:QMessageBox(parent)
		{
			connect(this, &QMessageBox::buttonClicked, this,
				&MessageBox::buttonFilter);
			this->setWindowTitle(title);
			this->setIcon(type);
		}

		virtual ~MessageBox() {}
	public:
		void setAcceptText(const QString& text = "");
		void setRejectText(const QString& text = "");
		void setHelpText(const QString& text = "");
		inline void aboutQt();
	protected:
		virtual void buttonFilter(QAbstractButton* button);
	signals:
		void acceptMessage();
		void rejectMessage();
		void helpMessage();
	private:
		std::unordered_map<PushButton*, int> ButtonMap;
		PushButton* Accept = nullptr;
		PushButton* Reject = nullptr;
		PushButton* Help = nullptr;
	};
	
	inline void MessageBox::aboutQt()
	{
		QMessageBox::aboutQt(this->parentWidget(),
			this->windowTitle());
	}
}
