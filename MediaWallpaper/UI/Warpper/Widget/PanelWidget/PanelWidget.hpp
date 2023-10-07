#pragma once
#include"UI/Basic/StackedWidget/StackedWidget.hpp"

namespace UI
{
	class PageWidget;

	class PanelWidget :public StackedWidget
	{
		Q_OBJECT

	public:
		inline explicit PanelWidget(QWidget* parent = nullptr,
			const int& screenCount = 1)
			:StackedWidget(parent)
		{
			this->allocation(screenCount);
			this->connection();
			this->initialization();
		}
	private:
		void allocation(const int& screenCount);
		void connection();
		void initialization();
	public:
		void readMediaData();
		void saveMediaData();
		void setPage(int data);
		void updateStyleSheet();
	protected:
		void resizeEvent(QResizeEvent* event) override;
	private:
		PageWidget* Page = nullptr;
	};
}