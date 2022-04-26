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
				return "�����";
				break;
			case oeav::domain::AccountTypes::PASSIVE:
				return "������";
				break;
			case oeav::domain::AccountTypes::BOTH:
				return "�������-���������";
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
				return "�";
				break;
			case oeav::domain::AccountTypes::BOTH:
				return "�";
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
				return "A - �����";
				break;
			case oeav::domain::AccountTypes::PASSIVE:
				return "� - ������";
				break;
			case oeav::domain::AccountTypes::BOTH:
				return "� - �������-���������";
				break;
			default:
				return {};
				break;
			}
		}

		inline const int getIdByRepresentation(const std::string &representation)
		{
			if (representation == "A - �����")
				return static_cast<int>(oeav::domain::AccountTypes::ACTIVE);
			else if (representation == "� - ������")
				return static_cast<int>(oeav::domain::AccountTypes::PASSIVE);
			else if (representation == "� - �������-���������")
				return static_cast<int>(oeav::domain::AccountTypes::BOTH);
			else
				return static_cast<int>(oeav::domain::AccountTypes::UNDEFINED);
		}
	}
}