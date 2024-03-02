#pragma once
#include"UI/Warpper/Data/JsonIO/JsonIO.hpp"
#include<QStringList>

namespace UI
{
	class Translator
	{
		template<typename Ty>
		using umap = JsonIO::Umap<Ty>;
		using strmap = JsonIO::Strmap;
	public:
		static QStringList TranslationList();
		static inline bool TranslationAvaliable();
		static inline void ReadTranslation(const QString& type);
		static QString Acquire(const QString& group, const QString& name);
	private:
		inline Translator() {}
		inline ~Translator() {}
		static umap<strmap> Map;
	};

	inline bool Translator::TranslationAvaliable()
	{
		return !Map.empty();
	}

	inline void Translator::ReadTranslation(const QString& type)
	{
		Map = JsonIO::Read("./resources/translation/" + type + ".json");
	}
}
