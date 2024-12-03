#pragma once
#include"LineEdit.hpp"
#include"Slider.hpp"
#include"Label.hpp"

#include<QGridLayout>

namespace UI
{
	class SliderEdit :public QWidget
	{
		Q_OBJECT

	public:
		inline explicit SliderEdit(QWidget* parent = nullptr, const QString& text = "")
			:QWidget(parent)
		{
			Display = new UI::LineEdit(this, text + "Display");
			Label = new UI::Label(this, text + "Label");

			Slider = new UI::Slider(this);
			Layout = new QGridLayout(this);

			Layout->addWidget(Label, 1, 1, 1, 2);
			Layout->addWidget(Slider, 1, 3, 1, 2);
			Layout->addWidget(Display, 1, 5, 1, 2);

			connect(Slider, &Slider::sliderTriggered, this, &SliderEdit::emitSlider);
			connect(Display, &LineEdit::textModified, this, &SliderEdit::emitDisplay);
		}
	public:
		inline void setValidator(QValidator* data) { Display->setValidator(data); }
		inline void setText(const QString& text) { Label->setText(text); }

		inline void setFactor(const double& data) { Factor = data; }
		inline void setRange(int min = 0, int max = 100);

		inline void setValue(double value);
		inline double value() const;
	private:
		inline void emitDisplay(const QString& data);
		inline void emitSlider(int data);
	signals:
		void sendData(double data);
	public:
		UI::LineEdit* Display = nullptr;
		UI::Slider* Slider = nullptr;
		UI::Label* Label = nullptr;

		QGridLayout* Layout = nullptr;
		double Factor = 1.0;
	};

	inline void SliderEdit::emitDisplay(const QString& data)
	{
		emit this->sendData(data.toDouble());
	}

	inline void SliderEdit::emitSlider(int data)
	{
		emit this->sendData(Factor * static_cast<double>(data));
	}

	inline void SliderEdit::setRange(int min, int max)
	{
		Slider->setMinimum(min);
		Slider->setMaximum(max);
	}

	inline void SliderEdit::setValue(double data)
	{
		double max = static_cast<double>(Slider->maximum());
		double min = static_cast<double>(Slider->minimum());

		data = data > max ? max : (data < min ? min : data);
		Slider->setValue(static_cast<int>(data / Factor));
		Display->setText(QString::number(data));
	}

	inline double SliderEdit::value() const
	{
		auto text = Display->text();

		if (text.isEmpty() == false)
			return text.toDouble();

		return Factor * Slider->value();
	}
}
