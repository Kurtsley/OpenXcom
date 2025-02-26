#pragma once
/*
 * Copyright 2010-2016 OpenXcom Developers.
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
#include <string>
#include <vector>
#include "../Engine/Yaml.h"

namespace OpenXcom
{

class Language;
class MovingTarget;
class Craft;
class Ufo;

/**
 * Base class for targets on the globe
 * with a set of radian coordinates.
 */
class Target
{
protected:
	double _lon, _lat;
	int _id;
	std::string _name;
	std::vector<MovingTarget*> _followers;
	/// Creates a target.
	Target();
public:
	/// Cleans up the target.
	virtual ~Target();
	/// Loads the target from YAML.
	virtual void load(const YAML::YamlNodeReader& reader);
	/// Saves the target to YAML.
	virtual void save(YAML::YamlNodeWriter writer) const;
	/// Saves the target's ID to YAML.
	virtual void saveId(YAML::YamlNodeWriter writer) const;
	/// Gets the target's type.
	virtual std::string getType() const = 0;
	/// Gets the target's longitude.
	double getLongitude() const;
	/// Sets the target's longitude.
	void setLongitude(double lon);
	/// Gets the target's latitude.
	double getLatitude() const;
	/// Sets the target's latitude.
	void setLatitude(double lat);
	/// Gets the target's ID.
	int getId() const;
	/// Sets the target's ID.
	void setId(int id);
	/// Gets the target's name.
	virtual std::string getName(Language *lang) const;
	/// Sets the target's name.
	void setName(const std::string &newName);
	/// Gets the target's default name.
	virtual std::string getDefaultName(Language *lang) const;
	/// Gets the target's marker name.
	virtual std::string getMarkerName() const;
	/// Gets the target's marker ID.
	virtual int getMarkerId() const;
	/// Gets the target's marker sprite.
	virtual int getMarker() const = 0;
	/// Gets the target's followers.
	std::vector<MovingTarget*> *getFollowers();
	/// Gets the target's craft followers.
	std::vector<Craft*> getCraftFollowers() const;
	/// Gets the target's UFO followers.
	std::vector<Ufo*> getUfoFollowers() const;
	/// Gets the distance to another target.
	double getDistance(const Target *target) const { return getDistance(target->getLongitude(), target->getLatitude()); }
	/// Gets the distance to another position.
	double getDistance(double lon, double lat) const;
};

}
