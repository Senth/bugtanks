/**
 * @file
 * @author Dennis Jönsson <zelebsel@gmail.com>
 * @version 1.0
 * Copyright (©) A-Team.
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

#include "PlasmaSpit.h"

using namespace logic;

PlasmaSpit::PlasmaSpit(float damage, float weaponCooldown, float range):
		EnemyWeapon(damage, weaponCooldown, range)
{
		mBulletKey = INVALID_KEY;
}

PlasmaSpit::~PlasmaSpit()
{
	if(mBulletKey != INVALID_KEY)
	{
		Munitions *pMunition = dynamic_cast<Munitions*>(mpActorHandler->getActor(mBulletKey));
		if(pMunition != NULL)
		{
			pMunition->startDestroyTimer();
		}
	}
}

void PlasmaSpit::fireWeapon(KeyType ownerId)
{
	mCooldownCounter = mpGlobalTimer->getTime(utilities::Timer::ReturnType_Seconds) - mCooldownStartTime;
	//check if cooldownCounter is higher than weaponCooldown
    if(mCooldownCounter > EnemyWeapon::getCooldown())
    {
		safeQueueEvent(EventDataPtr(myNew EvtData_From_EnemyWeaponFired(ownerId)));
		Actor *pActor;
		mBulletCounter++;
		mCooldownStartTime = mpGlobalTimer->getTime(utilities::Timer::ReturnType_Seconds);
		pActor = mpActorHandler->getActor(ownerId);
		utilities::Position position = pActor->getPosition();
		utilities::Direction direction = pActor->getDirection();
		utilities::Direction aimDir = mpActorHandler->getActor(mpPlayerInfo->getPlayerId())->getPosition() - position;
		aimDir.normalize();

	   if(mBullets <= 0)
	   {      
		   safeQueueEvent(EventDataPtr(myNew EvtData_To_ActorCreateMunition(Munitions::MunitionType_Plasma, position, direction, ownerId)));
	   }

	   if(mBulletKey != INVALID_KEY)
	   {
		   Actor *pActor = mpActorHandler->getActor(mBulletKey);
		   pActor->setDirection(aimDir.x,aimDir.y,aimDir.z);
		   pActor->setPosition(position.x + aimDir.x * 35.0f,position.y + 5.0f,position.z + aimDir.z * 35.0f);
		   dynamic_cast<Munitions*>(pActor)->setVisible(true);
	   }

		if(mBulletCounter == 0)
			mBulletCounter = -1;
	}

}

void PlasmaSpit::addBullet(KeyType bulletId)
{
	mBulletKey = bulletId;
	mBullets++;
}