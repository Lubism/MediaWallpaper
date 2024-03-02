#pragma once
#include"UI/Warpper/Data/JsonIO/JsonIO.hpp"

namespace UI
{
	class PanelInfo
	{
		template<typename Ty>
		using umap = JsonIO::Umap<Ty>;
		using strmap = JsonIO::Strmap;
	public:
		static QString Acquire(const QString& group, const QString& name);
		static void Apply(const QString& group, const QString& name,
			const QString& value);

		static void ReadInfo();
		static void WriteInfo();
	private:
		inline PanelInfo() {}
		inline ~PanelInfo() {}
		static umap<strmap> Map;
		static QString Path;
	};
}
