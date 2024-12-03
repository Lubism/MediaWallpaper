#pragma once
#include"Json.hpp"

#include<fstream>
#include<QString>

namespace UI
{
	class JsonIO
	{
	public:
		using Map = nlohmann::ordered_json;
	public:
		static inline bool Write(const QString& filePath, const Map& map);

		static inline bool Read(const QString& filePath, Map& result);
	public:
		static inline bool GetValue(const Map& map, const std::string& key, QString& value);

		template<typename Ty>
		static inline bool GetValue(const Map& map, const std::string& key, Ty& value);
	};

	inline bool JsonIO::Write(const QString& filePath, const Map& map)
	{
		std::ofstream writer(filePath.toStdString(), std::ios::trunc);
		bool state = true;

		try
		{
			writer << std::setw(4) << map;
		}
		catch (...)
		{
			state = false;
		}

		writer.close();
		return state;
	}

	inline bool JsonIO::Read(const QString& filePath, Map& result)
	{
		std::ifstream reader(filePath.toStdString());
		bool state = true;

		try
		{
			reader >> result;
		}
		catch (...)
		{
			state = false;
		}

		reader.close();
		return state;
	}

	inline bool JsonIO::GetValue(const Map& map, const std::string& key, QString& value)
	{
		using type = nlohmann::detail::value_t;
		auto result = map.find(key);
		if (result == map.end())
			return false;

		switch (result->type())
		{
		case type::number_unsigned:
		case type::number_integer:
		case type::number_float:
		case type::boolean:
			value = QString::number(result->get<double>());
			break;
		case type::string:
			value = QString::fromStdString(
				result->get<std::string>()
			);
			break;
		default:
			return false;
		}

		return true;
	}

	template<typename Ty>
	inline bool JsonIO::GetValue(const Map& map, const std::string& key, Ty& value)
	{
		using type = nlohmann::detail::value_t;
		auto result = map.find(key);
		if (result == map.end())
			return false;

		switch (result->type())
		{
		case type::number_unsigned:
		case type::number_integer:
		case type::number_float:
		case type::boolean:
			value = result->get<Ty>();
			break;
		case type::string:
			value = std::stod(result->get<std::string>());
			break;
		default:
			return false;
		}

		return true;
	}
}
