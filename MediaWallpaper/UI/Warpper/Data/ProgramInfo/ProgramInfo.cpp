#include"ProgramInfo.hpp"

using namespace UI;

ProgramInfo::umap<ProgramInfo::strmap> ProgramInfo::Map = ProgramInfo::umap<ProgramInfo::strmap>();
QString ProgramInfo::Path = "./mediaData/ProgramInfo.json";

QString ProgramInfo::Acquire(const QString& group, const QString& name)
{
	strmap& elem = Map[group];
	return elem[name];
}

void ProgramInfo::Apply(const QString& group, const QString& name,
	const QString& value)
{
	strmap& elem = Map[group];
	elem[name] = value;
}

void ProgramInfo::ReadInfo()
{
	Map = JsonIO::Read(Path);
}

void ProgramInfo::WriteInfo()
{
	JsonIO::Write(Map, Path);
}
