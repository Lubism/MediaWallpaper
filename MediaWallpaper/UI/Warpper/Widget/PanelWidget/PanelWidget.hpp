#pragma once
#include<QStackedWidget>

class QGridLayout;

namespace UI
{
	class PageWidget;

	class PanelWidget :public QStackedWidget
	{
		using Int = long long;
		Q_OBJECT

	public:
		inline explicit PanelWidget(QWidget* parent = nullptr,
			const Int& screenCount = 1)
			:QStackedWidget(parent)
		{
			this->allocation(screenCount);
			this->connection();
			this->initialization();
		}

		virtual ~PanelWidget() {}
	private:
		void allocation(const Int& screenCount);
		void connection();
		void initialization();
	public:
		inline void selectPanel(Int index) { this->setCurrentIndex(index); }
		void updateStyleSheet();
		void updateLanguage();
		void refreshDisplay();
		bool readInfo();
		void saveInfo();
	private:
		PageWidget* Page = nullptr;
	};
}
