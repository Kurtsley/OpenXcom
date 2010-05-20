/*
 * Copyright 2010 Daniel Albano
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
#ifndef OPENXCOM__RULEBASEFACILITY_H
#define OPENXCOM__RULEBASEFACILITY_H

/**
 * Represents a specific type of base facility.
 * Contains constant info about a facility like
 * costs, capacities, size, etc.
 * @sa BaseFacility
 */
class RuleBaseFacility
{
private:
	int _size, _buildCost, _buildTime, _monthlyCost;
	int _stores, _quarters, _aliens, _hangars, _labs, _workshops;
	int _radarRange, _radarChance, _defence;
public:
	/// Creates a blank facility ruleset.
	RuleBaseFacility();
	/// Cleans up the facility ruleset.
	~RuleBaseFacility();
};

#endif