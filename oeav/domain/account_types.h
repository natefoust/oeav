#pragma once

// std
#include <string>

namespace oeav
{
	namespace domain
	{
		enum class AccountTypes
		{
			UNDEFINED,
			ACTIVE,
			PASSIVE,
			BOTH
		};

		inline const std::string getStringRepresentation(AccountTypes type)
		{
			switch (type)
			{
			case oeav::domain::AccountTypes::ACTIVE:
				return "Актив";
				break;
			case oeav::domain::AccountTypes::PASSIVE:
				return "Пассив";
				break;
			case oeav::domain::AccountTypes::BOTH:
				return "Активно-пассивный";
				break;
			default:
				return {};
				break;
			}
		}

		inline const std::string getShortStringRepresentation(AccountTypes type)
		{
			switch (type)
			{
			case oeav::domain::AccountTypes::ACTIVE:
				return "A";
				break;
			case oeav::domain::AccountTypes::PASSIVE:
				return "П";
				break;
			case oeav::domain::AccountTypes::BOTH:
				return "Х";
				break;
			default:
				return {};
				break;
			}
		}

		inline const std::string getFullStringRepresentation(AccountTypes type)
		{
			switch (type)
			{
			case oeav::domain::AccountTypes::ACTIVE:
				return "A - актив";
				break;
			case oeav::domain::AccountTypes::PASSIVE:
				return "П - пассив";
				break;
			case oeav::domain::AccountTypes::BOTH:
				return "Х - активно-пассивный";
				break;
			default:
				return {};
				break;
			}
		}

		inline const int getIdByRepresentation(const std::string &representation)
		{
			if (representation == "A - актив")
				return static_cast<int>(oeav::domain::AccountTypes::ACTIVE);
			else if (representation == "П - пассив")
				return static_cast<int>(oeav::domain::AccountTypes::PASSIVE);
			else if (representation == "Х - активно-пассивный")
				return static_cast<int>(oeav::domain::AccountTypes::BOTH);
			else
				return static_cast<int>(oeav::domain::AccountTypes::UNDEFINED);
		}
	}
}