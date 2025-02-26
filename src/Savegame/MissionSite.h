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
#include "Target.h"
#include <string>
#include "../Engine/Yaml.h"

namespace OpenXcom
{

class RuleAlienMission;
class AlienDeployment;
class Ufo;

/**
 * Represents an alien mission site on the world.
 */
class MissionSite : public Target
{
private:
	const RuleAlienMission *_rules;
	const AlienDeployment *_deployment;
	const AlienDeployment *_missionCustomDeploy;
	int _texture;
	size_t _secondsRemaining;
	std::string _race, _city;
	bool _inBattlescape, _detected;
	Ufo* _ufo;
	int _ufoUniqueId;
public:
	/// Creates a mission site.
	MissionSite(const RuleAlienMission *rules, const AlienDeployment *deployment, const AlienDeployment *alienWeaponDeploy);
	/// Cleans up the mission site.
	~MissionSite();
	/// Loads the mission site from YAML.
	void load(const YAML::YamlNodeReader& reader) override;
	/// Saves the mission site to YAML.
	void save(YAML::YamlNodeWriter writer) const override;
	/// Gets the waypoint's type.
	std::string getType() const override;
	/// Gets the mission site's ruleset.
	const RuleAlienMission *getRules() const;
	/// Gets the mission site's deployment.
	const AlienDeployment *getDeployment() const;
	/// Gets the optional alien weapon deployment for site.
	const AlienDeployment *getMissionCustomDeploy() const;
	/// Gets the mission site's marker name.
	std::string getMarkerName() const override;
	/// Gets the mission site's marker sprite.
	int getMarker() const override;
	/// Gets the seconds until this mission site expires.
	size_t getSecondsRemaining() const;
	/// Sets the seconds until this mission site expires.
	void setSecondsRemaining(size_t seconds);
	/// Gets the mission site's alien race.
	std::string getAlienRace() const;
	/// Sets the mission site's alien race.
	void setAlienRace(const std::string &race);
	/// Sets the mission site's battlescape status.
	void setInBattlescape(bool inbattle);
	/// Gets if the mission site is in battlescape.
	bool isInBattlescape() const;
	/// Gets the mission site's texture.
	int getTexture() const;
	/// Sets the mission site's texture.
	void setTexture(int texture);
	/// Gets the mission site's city.
	const std::string& getCity() const;
	/// Sets the mission site's city.
	void setCity(const std::string &city);
	/// Gets the mission site's detection state.
	bool getDetected() const;
	/// Sets the mission site's detection state.
	void setDetected(bool detected);
	/// Gets the mission site's corresponding Ufo.
	Ufo* getUfo() const { return _ufo; }
	/// Sets the mission site's corresponding Ufo.
	void setUfo(Ufo* ufo) { _ufo = ufo; }
	/// DO NOT USE! Used only for loading saved games.
	int getUfoUniqueId() const { return _ufoUniqueId; }
};

}
