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
#include "MissionSite.h"
#include "Ufo.h"
#include "../Engine/Language.h"
#include "../Mod/RuleAlienMission.h"
#include "../Mod/AlienDeployment.h"

namespace OpenXcom
{

/**
 * Initializes a mission site.
 */
MissionSite::MissionSite(const RuleAlienMission *rules, const AlienDeployment *deployment, const AlienDeployment *alienCustomDeploy) : Target(),
	_rules(rules), _deployment(deployment), _missionCustomDeploy(alienCustomDeploy),
	_texture(-1), _secondsRemaining(0), _inBattlescape(false), _detected(false), _ufo(nullptr), _ufoUniqueId(-1)
{
}

/**
 *
 */
MissionSite::~MissionSite()
{
}

/**
 * Loads the mission site from a YAML file.
 * @param node YAML node.
 */
void MissionSite::load(const YAML::YamlNodeReader& reader)
{
	Target::load(reader);
	reader.tryRead("texture", _texture);
	reader.tryRead("secondsRemaining", _secondsRemaining);
	reader.tryRead("race", _race);
	reader.tryRead("inBattlescape", _inBattlescape);
	reader.tryRead("detected", _detected);
	//_missionCustomDeploy loaded outside
	reader.tryRead("ufoUniqueId", _ufoUniqueId);
	// _ufo loaded outside
}

/**
 * Saves the mission site to a YAML file.
 * @return YAML node.
 */
void MissionSite::save(YAML::YamlNodeWriter writer) const
{
	writer.setAsMap();
	Target::save(writer);

	writer.write("type", _rules->getType());
	writer.write("deployment", _deployment->getType());
	if (_missionCustomDeploy)
		writer.write("missionCustomDeploy", _missionCustomDeploy->getType());
	writer.write("texture", _texture);
	if (_secondsRemaining)
		writer.write("secondsRemaining", _secondsRemaining);
	writer.write("race", _race);
	if (_inBattlescape)
		writer.write("inBattlescape", _inBattlescape);
	writer.write("detected", _detected);
	if (_ufo)
		writer.write("ufoUniqueId", _ufo->getUniqueId());
}

/**
 * Returns the mission's unique type used for
 * savegame purposes.
 * @return ID.
 */
std::string MissionSite::getType() const
{
	return _deployment->getMarkerName();
}

/**
 * Returns the ruleset for the mission's type.
 * @return Pointer to ruleset.
 */
const RuleAlienMission *MissionSite::getRules() const
{
	return _rules;
}

/**
 * Returns the ruleset for the mission's deployment.
 * @return Pointer to deployment rules.
 */
const AlienDeployment *MissionSite::getDeployment() const
{
	return _deployment;
}

/**
 * Get mission's custom deployment of weapons.
 * @return Aline deployment.
 */
const AlienDeployment *MissionSite::getMissionCustomDeploy() const
{
	return _missionCustomDeploy;
}

/**
 * Returns the name on the globe for the mission.
 * @return String ID.
 */
std::string MissionSite::getMarkerName() const
{
	return getType();
}

/**
 * Returns the globe marker for the mission site.
 * @return Marker sprite, -1 if none.
 */
int MissionSite::getMarker() const
{
	if (!_detected)
		return -1;
	if (_deployment->getMarkerIcon() == -1)
		return 5;
	return _deployment->getMarkerIcon();
}

/**
 * Returns the number of seconds remaining before the mission site expires.
 * @return Amount of seconds.
 */
size_t MissionSite::getSecondsRemaining() const
{
	return _secondsRemaining;
}

/**
 * Changes the number of seconds before the mission site expires.
 * @param seconds Amount of seconds.
 */
void MissionSite::setSecondsRemaining(size_t seconds)
{
	_secondsRemaining = seconds;
}

/**
 * Returns the alien race currently residing in the mission site.
 * @return Alien race.
 */
std::string MissionSite::getAlienRace() const
{
	return _race;
}

/**
 * Changes the alien race currently residing in the mission site.
 * @param race Alien race.
 */
void MissionSite::setAlienRace(const std::string &race)
{
	_race = race;
}

/**
 * Gets the mission site's battlescape status.
 * @return Is the mission currently in battle?
 */
bool MissionSite::isInBattlescape() const
{
	return _inBattlescape;
}

/**
 * Sets the mission site's battlescape status.
 * @param inbattle True if it's in battle, False otherwise.
 */
void MissionSite::setInBattlescape(bool inbattle)
{
	_inBattlescape = inbattle;
}

/**
 * Gets the mission site's associated texture.
 * @return Texture ID.
 */
int MissionSite::getTexture() const
{
	return _texture;
}

/**
 * Sets the mission site's associated texture.
 * @param texture Texture ID.
 */
void MissionSite::setTexture(int texture)
{
	_texture = texture;
}

/**
 * Gets the mission site's associated city, if any.
 * @return String ID for the city, "" if none.
 */
const std::string& MissionSite::getCity() const
{
	return _city;
}

/**
 * Sets the mission site's associated city, if any.
 * @param city String ID for the city, "" if none.
 */
void MissionSite::setCity(const std::string &city)
{
	_city = city;
}

/**
 * Gets the detection state for this mission site.
 * used for popups of sites spawned directly rather than by UFOs.
 * @return whether or not this site has been detected.
 */
bool MissionSite::getDetected() const
{
	return _detected;
}

/**
 * Sets the mission site's detection state.
 * @param detected whether we want this site to show on the geoscape or not.
 */
void MissionSite::setDetected(bool detected)
{
	_detected = detected;
}

}
