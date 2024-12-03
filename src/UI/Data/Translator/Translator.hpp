#pragma once
#include"UI/Data/JsonIO.hpp"

#include<QStringList>
#include<QFile>
#include<QDir>

namespace UI
{
	class Translator
	{
	public:
		static inline bool TranslationAvaliable();
		static inline QStringList TranslationList();

		static inline void ReadTranslation(const QString& type);
		static inline QString Acquire(const QString& group, const QString& name);
	public:
		inline Translator() {}
		inline ~Translator() {}
	private:
		static JsonIO::Map Map;
	};

	inline bool Translator::TranslationAvaliable()
	{
		return !Map.empty();
	}

	QStringList Translator::TranslationList()
	{
		QDir dir("./resources/translation");
		auto list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);

		QString temp = "";
		QStringList result;
		for (auto& it : list)
		{
			temp = it.fileName();
			result.push_back(temp.split('.').at(0));
		}

		return result;
	}

	inline void Translator::ReadTranslation(const QString& type)
	{
		JsonIO::Read("./resources/translation/" + type + ".json", Map);
	}

	QString Translator::Acquire(const QString& group, const QString& name)
	{
		auto it = Map.find(group.toStdString());
		if (it == Map.end()) return QString();

		QString result = "";
		JsonIO::GetValue(*it, name.toStdString(), result);

		return result;
	}
}
