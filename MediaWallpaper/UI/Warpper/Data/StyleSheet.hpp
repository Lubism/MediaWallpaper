#pragma once
#include<QWidget>
#include<QString>
#include<QFile>

namespace UI
{
	class StyleSheet
	{
	public:
		static inline QString Read(const QString& type);
		static inline void Set(QWidget* widget,
			const QString& type);
	private:
		StyleSheet() {}
		~StyleSheet() {}
	};

	inline QString StyleSheet::Read(const QString& type)
	{
		QFile file("./resources/stylesheet/" + type + ".css");
		if (!file.open(QIODevice::ReadOnly))
			return QString();

		QString result = file.readAll();
		file.close();

		return result;
	}

	inline void StyleSheet::Set(QWidget* widget, const QString& type)
	{
		if (widget == nullptr)
			return;

		auto str = Read(type);
		widget->setStyleSheet(str);
	}
}
