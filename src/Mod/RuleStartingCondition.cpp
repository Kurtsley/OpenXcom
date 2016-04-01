/*
 * Copyright 2010-2015 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "RuleStartingCondition.h"
#include <algorithm>

namespace OpenXcom
{

/**
 * Creates a blank ruleset for a certain type of Starting Condition.
 * @param type String defining the type.
 */
RuleStartingCondition::RuleStartingCondition(const std::string &type) : _type(type)
{
}

/**
 *
 */
RuleStartingCondition::~RuleStartingCondition()
{
}

/**
 * Loads the Starting Conditions from a YAML file.
 * @param node YAML node.
 */
void RuleStartingCondition::load(const YAML::Node &node)
{
	if (const YAML::Node &parent = node["refNode"])
	{
		load(parent);
	}
	_type = node["type"].as<std::string>(_type);
	_armorTransformations = node["armorTransformations"].as< std::map<std::string, std::string> >(_armorTransformations);
	_defaultArmor = node["defaultArmor"].as< std::map<std::string, std::string> >(_defaultArmor);
	_defaultItems = node["defaultItems"].as< std::map<std::string, int> >(_defaultItems);
	_allowedArmors = node["allowedArmors"].as< std::vector<std::string> >(_allowedArmors);
	_allowedItems = node["allowedItems"].as< std::vector<std::string> >(_allowedItems);
	_allowedCraft = node["allowedCraft"].as< std::vector<std::string> >(_allowedCraft);

}

/**
 * Returns the language string that names the Starting Condition. Each type has a unique name.
 * @return Starting Condition name.
 */
std::string RuleStartingCondition::getType() const
{
	return _type;
}

/**
* Checks if the craft type is allowed.
* @param craftType Craft type name.
* @return True if allowed, false otherwise.
*/
bool RuleStartingCondition::isCraftAllowed(const std::string &craftType) const
{
	return _allowedCraft.empty() || (std::find(_allowedCraft.begin(), _allowedCraft.end(), craftType) != _allowedCraft.end());
}

/**
* Gets the replacement armor.
* @param soldierType Soldier type name.
* @param armorType Existing/old armor type name.
* @return Replacement armor type name (or empty string if no replacement is needed).
*/
std::string RuleStartingCondition::getArmorReplacement(const std::string &soldierType, const std::string &armorType) const
{
	if (!_allowedArmors.empty() && (std::find(_allowedArmors.begin(), _allowedArmors.end(), armorType) == _allowedArmors.end()))
	{
		std::map<std::string, std::string>::const_iterator j = _defaultArmor.find(soldierType);
		if (j != _defaultArmor.end())
		{
			return j->second;
		}
	}

	return std::string();
}

/**
* Gets the transformed armor.
* @param armorType Existing/old armor type name.
* @return Transformed armor type name (or empty string if there is no transformation).
*/
std::string RuleStartingCondition::getArmorTransformation(const std::string &armorType) const
{
	if (!_armorTransformations.empty())
	{
		std::map<std::string, std::string>::const_iterator i = _armorTransformations.find(armorType);
		if (i != _armorTransformations.end())
		{
			return i->second;
		}
	}

	return std::string();
}

/**
* Checks if the item type is allowed.
* @param itemType Item type name.
* @return True if allowed, false otherwise.
*/
bool RuleStartingCondition::isItemAllowed(const std::string &itemType) const
{
	return _allowedItems.empty() || (std::find(_allowedItems.begin(), _allowedItems.end(), itemType) != _allowedItems.end());
}

/**
* Returns all the default items.
* @return List of items.
*/
const std::map<std::string, int> *RuleStartingCondition::getDefaultItems() const
{
	return &_defaultItems;
}

}
