#include"PanelInfo.hpp"

using namespace UI;

PanelInfo::umap<PanelInfo::strmap> PanelInfo::Map = PanelInfo::umap<PanelInfo::strmap>();
QString PanelInfo::Path = "./mediaData/PanelInfo.json";

QString PanelInfo::Acquire(const QString& group, const QString& name)
{
	strmap& elem = Map[group];
	return elem[name];
}

void PanelInfo::Apply(const QString& group, const QString& name,
	const QString& value)
{
	strmap& elem = Map[group];
	elem[name] = value;
}

void PanelInfo::ReadInfo()
{
	Map = JsonIO::Read(Path);
}

void PanelInfo::WriteInfo()
{
	JsonIO::Write(Map, Path);
}