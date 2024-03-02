#pragma once
#include"UI/Warpper/Data/JsonMap.hpp"
#include<QString>

namespace UI
{
	class JsonIO
	{
	public:
		template<typename Ty>
		using Umap = JsonMap<QString, Ty>;
		using Strmap = JsonMap<QString, QString>;
	public:
		static Umap<Strmap> Read(const QString& filepath);
		static void Write(const Umap<Strmap>& data,
			const QString& filepath);
	private:
		static QString Construct(const Umap<Strmap>& data);
		static Umap<Strmap> Deconstruct(const QStringList& list);
	};
}
