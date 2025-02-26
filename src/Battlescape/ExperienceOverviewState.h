#pragma once
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
#include <vector>
#include "../Engine/State.h"

namespace OpenXcom
{

class TextButton;
class Window;
class Text;
class TextList;
class BattlescapeState;

/**
 * Displays a list of soldiers in battlescape and their gained experience.
 */
class ExperienceOverviewState : public State
{
private:
	TextButton *_btnOk;
	Window *_window;
	Text *_txtTitle, *_txtName;
	Text *_txtBravery, *_txtReactions, *_txtFiring, *_txtThrowing, *_txtPsiSkill, *_txtPsiStrength, *_txtMelee, *_txtMana;
	TextList *_lstSoldiers;

	BattlescapeState* _parent;
	std::vector<BattleUnit*> _soldiers;
public:
	/// Creates the Experience Overview state.
	ExperienceOverviewState(BattlescapeState* parent);
	/// Cleans up the Experience Overview state.
	~ExperienceOverviewState() = default;
	/// Handler for clicking the OK button.
	void btnOkClick(Action* action);
	/// Handler for clicking the Soldiers list.
	void lstSoldiersClick(Action* action);
};

}
