#pragma once
#include"UI/Warpper/Data/JsonIO/JsonIO.hpp"

namespace UI
{
	class ProgramInfo
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
		inline ProgramInfo() {}
		inline ~ProgramInfo() {}
		static umap<strmap> Map;
		static QString Path;
	};
}
