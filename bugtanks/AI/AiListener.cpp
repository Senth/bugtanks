/**
* @file
* @author Matteus Magnusson <senth.wallace@gmail.com>
* @version 1.0
* Copyright (�) A-Team.
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details at
* http://www.gnu.org/copyleft/gpl.html
*/

#include "AiListener.h"
#include "AiFactory.h"
#include "UnitHandler.h"
#include "PathFinder.h"
#include "AiEvents.h"
#include "AgentAi.h"

using namespace ai;

AiListener::AiListener()
{
	mpAiFactory = NULL;
	mpUnitHandler = NULL;
	mpPathFinder = NULL;

	mpAiFactory = AiFactory::getInstance();
	assert(mpAiFactory != NULL);

	mpUnitHandler = UnitHandler::getInstance();
	mpPathFinder = PathFinder::getInstance();
}

AiListener::~AiListener()
{
}

bool AiListener::handleEvent(const logic::EventData &eventData)
{
	// Pause or resume the AI
	if (EvtData_To_AiTogglePause::msEventType == eventData.getEventType())
	{
		mpAiFactory->isPaused() ? mpAiFactory->resume() : mpAiFactory->pause();
	}

	// Agent AI Goals
	else if (EvtData_To_AgentAiGoals::msEventType == eventData.getEventType())
	{
		const EvtData_To_AgentAiGoals& agentAiGoals = static_cast<const EvtData_To_AgentAiGoals&>(eventData);
		// Only set goals for those we aren't owner of
		if (!agentAiGoals.mKey.isOwner())
		{
			AgentAi* pAgentAi = mpUnitHandler->getAgentAi(agentAiGoals.mKey);

			if (pAgentAi != NULL)
			{
				pAgentAi->setGoals(agentAiGoals.mGoals, static_cast<PathFinder::GoalTypes>(agentAiGoals.mGoalType));
			}
		}
	}

	// Add to conflict map
	else if (EvtData_To_AiAddToConflictMap::msEventType == eventData.getEventType())
	{
		const EvtData_To_AiAddToConflictMap& conflictMapInfo = static_cast<const EvtData_To_AiAddToConflictMap&>(eventData);

		if (!conflictMapInfo.mKey.isOwner())
		{
			mpPathFinder->addToConflictMapFromEvent(conflictMapInfo.mGoalPosition, conflictMapInfo.mKey, static_cast<PathFinder::GoalTypes>(conflictMapInfo.mGoalType), conflictMapInfo.mUnitSize);
		}
	}

	// Remove from conflict map
	else if (EvtData_To_AiRemoveFromConflictMap::msEventType == eventData.getEventType())
	{
		const EvtData_To_AiAddToConflictMap& conflictMapInfo = static_cast<const EvtData_To_AiAddToConflictMap&>(eventData);

		if (!conflictMapInfo.mKey.isOwner())
		{
			mpPathFinder->removeFromConflictMapFromEvent(conflictMapInfo.mGoalPosition, conflictMapInfo.mKey, static_cast<PathFinder::GoalTypes>(conflictMapInfo.mGoalType), conflictMapInfo.mUnitSize);
		}
	}

	return false;
}