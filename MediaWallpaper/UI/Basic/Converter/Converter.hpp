#pragma once
#include<QObject>

class QResizeEvent;

namespace UI
{
	class Converter :public QObject
	{
	public:
		inline Converter(int width, int height,
			QResizeEvent*& event)
			:QObject()
		{
			this->importData(width, height, event);
		}

		void importData(int width, int height, QResizeEvent*& event);

		inline int width(double num) const
		{
			return static_cast<int>((num / FixWidth) * CurrentWidth);
		}

		inline int height(double num) const
		{
			return static_cast<int>((num / FixHeight) * CurrentHeight);
		}

		inline int font(double num, double den) const
		{
			return static_cast<int>(((num += 4) / den) *
				this->height(den));
		}

		static inline QString CH(const char* str)
		{
			return QString::fromLocal8Bit(str);
		}
	public:
		inline Converter() {}
		inline virtual ~Converter() {}
		inline Converter(const Converter&) = default;
		inline Converter& operator=(const Converter&) = default;
	private:
		double FixWidth = 1;
		double FixHeight = 1;
		double CurrentWidth = 1;
		double CurrentHeight = 1;
	};
}