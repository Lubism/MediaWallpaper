#include"Translator.hpp"
#include<QFile>
#include<QDir>

using namespace UI;

Translator::umap<Translator::strmap> Translator::Map = Translator::umap<Translator::strmap>();

QStringList Translator::TranslationList()
{
	QDir dir("./resources/translation");
	auto list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);

	QStringList result;
	QString storage = "";
	for (auto& it : list)
	{
		storage = it.fileName();
		result.push_back(storage.split('.').at(0));
	}

	return result;
}

QString Translator::Acquire(const QString& group, const QString& name)
{
	auto it = Map.find(group);
	if (it == Map.end()) return QString();

	auto& storage = it.value();
	auto result = storage.find(name);
	if (result == storage.end()) return QString();

	return result.value();
}
