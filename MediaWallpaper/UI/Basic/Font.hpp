#pragma once
#include"UI/Basic/Converter/Converter.hpp"
#include<QFont>

namespace UI
{
	class Font :public QFont
	{
	public:
		inline Font(const Converter& cvt,
			int size, int height)
			:QFont()
		{
			this->setPixelSize(cvt.font(size, height));
			this->setFamily(QString::fromLocal8Bit("ºÚÌå"));
		}

		inline Font(int size = 12) :QFont()
		{
			this->setPixelSize(size += 4);
			this->setFamily(QString::fromLocal8Bit("ºÚÌå"));
		}

		virtual inline ~Font() {}
	};
}