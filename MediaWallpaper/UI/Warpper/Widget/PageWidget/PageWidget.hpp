#pragma once
#include"UI/Basic/Widget/Widget.hpp"

namespace UI
{
	class BasicGroupBox;
	class FileGroupBox;
	class MediaWidget;
	class MediaData;

	class PageWidget :public Widget
	{
		Q_OBJECT

	public:
		inline explicit PageWidget(QWidget* parent = nullptr,
			const int& screenIndex = 0)
			:Widget(parent)
		{
			this->allocation(screenIndex);
			this->connection();
			this->initialization();
		}
	private:
		void allocation(const int& screenIndex);
		void connection();
		void initialization();

		void connection_file();
		void connection_basic();
		void connection_media();
	public:
		void readMediaData();
		void saveMediaData();
		void updateStyleSheet();
	protected:
		void resizeEvent(QResizeEvent* event) override;
	private:
		BasicGroupBox* Basic = nullptr;
		FileGroupBox* File = nullptr;
		MediaWidget* Media = nullptr;
		MediaData* Data = nullptr;
		bool StopState = false;
	};
}