#pragma once
#include"UI/Basic/PushButton.hpp"
#include<QMessageBox>

#include<unordered_map>

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
		inline void setAcceptText(const QString& text = "")
		{
			if (!Accept)
			{
				Accept = new PushButton(this);
				this->addButton(Accept, ButtonRole::AcceptRole);
			}

			Accept->setText(text);
			ButtonMap[Accept] = 0;
		}

		inline void setRejectText(const QString& text = "")
		{
			if (!Reject)
			{
				Reject = new PushButton(this);
				this->addButton(Reject, ButtonRole::RejectRole);
			}

			Reject->setText(text);
			ButtonMap[Reject] = 1;
		}

		inline void setHelpText(const QString& text = "")
		{
			if (!Help)
			{
				Help = new PushButton(this);
				this->addButton(Help, ButtonRole::HelpRole);
			}

			Help->setText(text);
			ButtonMap[Help] = 2;
		}

		inline void aboutQt() const;
	protected:
		inline void buttonFilter(QAbstractButton* button)
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
	
	inline void MessageBox::aboutQt() const
	{
		QMessageBox::aboutQt(this->parentWidget(),
			this->windowTitle());
	}
}
