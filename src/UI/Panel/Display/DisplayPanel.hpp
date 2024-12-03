#pragma once
#include"UI/Basic/PushButton.hpp"
#include"UI/Basic/SliderEdit.hpp"
#include"UI/Basic/Widget.hpp"

class QGridLayout;
class QScrollArea;
class QValidator;

namespace UI
{
	class PushButton;
	class LineEdit;
	class Slider;
	class Label;

	class DisplayPanel :public Widget
	{
		Q_OBJECT

	private:
		using Int = long long;
	public:
		inline explicit DisplayPanel(QWidget* parent = nullptr)
			:Widget(parent)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}
	private:
		void allocation();
		void connection();
		void initLayout();
		void initialization();

		void editConnection();
		void buttonConnection();
	public:
		inline void setBrightness(Int data) { Brightness->setValue(static_cast<double>(data)); }
		inline void setSaturation(Int data) { Saturation->setValue(static_cast<double>(data)); }
		inline void setContrast(Int data) { Contrast->setValue(static_cast<double>(data)); }

		inline void setRotate(Int data) { Rotate->setValue(static_cast<double>(data)); }
		inline void setGamma(Int data) { Gamma->setValue(static_cast<double>(data)); }
		inline void setHue(Int data) { Hue->setValue(static_cast<double>(data)); }

		inline void setAspectRatio(double data) { AspectRatio->setValue(data); }
		inline void setPanscan(double data) { Panscan->setValue(data); }
		inline void setAlign(double halign, double valign);
		inline void setFlip(bool hflip, bool vflip);

		void updateStyleSheet();
		void updateLanguage();
	signals:
		void align(double halign, double valign);
		void flip(bool hflip, bool vflip);

		void aspectRatio(double data);
		void panscan(double data);

		void brightness(Int data);
		void saturation(Int data);
		void contrast(Int data);

		void rotate(Int data);
		void gamma(Int data);
		void hue(Int data);
	private:
		QValidator* Validator = nullptr;
		QWidget* Canvas = nullptr;

		QGridLayout* MainLayout = nullptr;
		QGridLayout* AreaLayout = nullptr;
		QScrollArea* Area = nullptr;

		SliderEdit* AspectRatio = nullptr;
		SliderEdit* Brightness = nullptr;
		SliderEdit* Saturation = nullptr;
		SliderEdit* Contrast = nullptr;
		SliderEdit* Panscan = nullptr;

		SliderEdit* Rotate = nullptr;
		SliderEdit* HAlign = nullptr;
		SliderEdit* VAlign = nullptr;
		SliderEdit* Gamma = nullptr;
		SliderEdit* Hue = nullptr;

		PushButton* HFlip = nullptr;
		PushButton* VFlip = nullptr;
	};

	inline void DisplayPanel::setAlign(double halign, double valign)
	{
		HAlign->setValue(halign);
		VAlign->setValue(valign);
	}

	inline void DisplayPanel::setFlip(bool hflip, bool vflip)
	{
		if (hflip != HFlip->isChecked())
			HFlip->setChecked(hflip);
		if (vflip != VFlip->isChecked())
			VFlip->setChecked(vflip);
	}
}
