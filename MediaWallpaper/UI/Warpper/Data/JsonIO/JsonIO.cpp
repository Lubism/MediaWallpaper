#include"JsonIO.hpp"
#include<vector>
#include<QFile>

using namespace UI;

template<typename Ty>
using Umap = JsonIO::Umap<Ty>;
using Strmap = JsonIO::Strmap;

Umap<Strmap> JsonIO::Read(const QString& filepath)
{
	Umap<Strmap> result;
	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly))
		return result;

	auto str = QString::fromUtf8(file.readAll());
	file.close();

	if (str.isEmpty()) return result;
	str.remove(QRegExp("[\r\n\t]"));

	auto list = str.split(QRegExp("[{,}]"), Qt::SkipEmptyParts);
	size_t left = 0, right = 0;
	for (auto& elem : list)
	{
		for (auto it = elem.begin(); it != elem.end(); it++)
		{
			left = std::distance(elem.begin(), it);
			if (*it != ' ') break;
		}

		for (auto it = elem.rbegin(); it != elem.rend(); it++)
		{
			right = std::distance(elem.rbegin(), it);
			if (*it != ' ') break;
		}

		elem = elem.mid(left, elem.size() - left - right);
	}

	result = Deconstruct(list);
	return result;
}

void JsonIO::Write(const Umap<Strmap>& data, const QString& filepath)
{
	QFile file(filepath);
	file.open(QIODevice::WriteOnly | QIODevice::Truncate);

	auto result = Construct(data);
	file.write(result.toUtf8());
	file.close();
}

QString JsonIO::Construct(const Umap<Strmap>& data)
{
	QString sign = "\r\n";
	QString result = "{" + sign;

	size_t objSize = data.size();
	size_t valSize = 0, objIndex = 0, valIndex = 0;
	for (auto& object : data)
	{
		result = result + "\t\"" + object.key() + "\"";
		result += ":" + sign + "\t{" + sign;
		valSize = object.value().size();
		valIndex = 0;

		for (auto& val : object.value())
		{
			result += "\t\t\"" + val.key() + "\": ";
			result += "\"" + val.value() + "\"";

			++valIndex;

			if (valIndex >= valSize)
				result += sign;
			else
				result += "," + sign;
		}

		++objIndex;

		if (objIndex >= objSize)
			result += "\t}" + sign;
		else
			result += "\t}," + sign + "\n";
	}

	result += "}" + sign;
	return result;
}

Umap<Strmap> JsonIO::Deconstruct(const QStringList& list)
{
	std::vector<QString> keys;
	Umap<Strmap> result;
	QStringList valList;
	Strmap strmap;
	QString str;

	auto appendMap = [&]()
	{
		str = keys.back();
		keys.pop_back();

		str.remove(QRegExp("[\"]"));

		result[str.mid(0, str.size() - 1)] = strmap;
		Strmap().swap(strmap);
	};

	for (auto& it : list)
	{
		if (it.back() == ':')
		{
			if (!keys.empty())
				appendMap();

			keys.push_back(it);
		}
		else
		{
			valList = it.split(QRegExp("[\"]"),
				Qt::SkipEmptyParts);

			strmap[valList.front()] = valList.back();
		}
	}

	while (!keys.empty())
		appendMap();

	return result;
}
