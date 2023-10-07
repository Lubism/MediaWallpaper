#pragma once
#include<QMessageBox>

namespace UI
{
	class PushButton;

	class MessageBox :public QMessageBox
	{
		Q_OBJECT

	public:
		explicit MessageBox(QWidget* parent, const QString& title = "Message");

		void setAcceptText(const QString& text = "");
		void setRejectText(const QString& text = "");
		void setHelpText(const QString& text = "");
		inline void aboutQt();

		virtual ~MessageBox() {}
	protected:
		virtual void buttonFilter(QAbstractButton* button);
	signals:
		void acceptMessage();
		void rejectMessage();
		void helpMessage();
	private:
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
