/**
 * @file
 * @author Jonathan Udd <jonis.x@gmail.com>
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

#ifndef __DYNAMIC_ACTOR_H__
#define __DYNAMIC_ACTOR_H__

#include "../Utilities/Macros.h"
#include "Actor.h"

namespace logic
{

class DynamicActor : public Actor
{
public:
	/**
	* Constructor	
	*/
	DynamicActor(utilities::Position pos, utilities::Direction dir, int networkId, const utilities::MapCoordinate& size = utilities::MapCoordinate(0,0));

	/**
	* Destructor	
	*/
	~DynamicActor();

	/**
	* Moves the actor depending on the direction of the actor.
	* @param deltaTime elapsed time since last frame.
	*/
	virtual void update(float deltaTime);

protected:
	float mOriginalSpeed;
private:
};
}

#endif