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

#ifndef __MAP_H__
#define __MAP_H__

#include "../Utilities/Macros.h"
#include "../Utilities/Vec2Int.h"
#include "../Utilities/VectorList.h"
#include "../Logic/KeyType.h"
#include <map>

#ifdef AI_DRAW_MAP_POTENTIAL_FIELD
#include "../GFX/DX10Module.h"
#endif

namespace ai
{

// Forward declarations
class PotentialUnit;

/**
* Has information about the static objects in on the map that are necessary for the AI components.
* Is a singleton.
*/
class Map
{
public:
	/**
	* Destructor
	*/
	~Map();

	/**
	* Returns an instance of the map
	* @return instance of the map
	*/
	static Map* getInstance();

	/**
	* Clears the map, i.e. removes the potential field and all units.
	*/
	void clear();

	/**
	* Sets a new map size. This takes a long time to calculate when there already
	* are potential units in the map.
	* @param mapSize the size of the map
	*/
	void setMapSize(const utilities::MapCoordinate& mapSize);

	/**
	* Adds a potential unit to the map's potential field
	* @param pPotentialUnit pointer to a static potential unit
	*/
	void addPotentialUnit(const PotentialUnit* pPotentialUnit);

	/**
	* Removes a potential unit from the map's potential field
	* @param keyId the key id of the potential unit to remove
	*/
	void removePotentialUnit(const logic::KeyType& keyId);

	/**
	* Returns a potential value from the specified map position
	* @param mapPosition the position on the map we want to get the value from
	* @return the potential value, always INVALID_POTENTIAL_VALUE if we're out of bounds
	*/
	float getPotentialValue(const utilities::MapCoordinate& mapPosition) const;

	/**
	* Updates the position of a unit in the map's potential field
	* @param keyId the key of the potential unit to update
	*/
	void updatePositionForUnit(const logic::KeyType& keyId);

private:
	/**
	* Constructor, private enforces singleton pattern
	*/
	Map();

	/**
	* Re-adds all the potential units to the map.
	*/
	void readdPotentialUnits();

	/**
	* Removes the unit from the potential field, however you can
	* specify if you want to keep the unit. This is usually done
	* when the unit has moved.
	* @param keyId the key of the unit to remove from the potential field
	* @param keepUnit if we want to keep the unit or not
	*/
	void removePotentialUnit(const logic::KeyType& keyId, bool keepUnit);

	/**
	* Returns false if we're out of bounds
	* @param indexPosition the current
	*/
	inline bool validIndex(const utilities::MapCoordinate indexPosition) const
	{
		return (indexPosition.x >= 0 &&
				indexPosition.x < mMapSize.x &&
				indexPosition.y >= 0 &&
				indexPosition.y < mMapSize.y);
	}

	/**
	* Returns the index depending on the specified map position
	* @param mapPosition the position on the map
	* @return the index in the map's potential field
	*/
	inline utilities::MapCoordinate indexInFieldByPosition(const utilities::MapCoordinate& mapPosition) const
	{
		return (mapPosition + mCenterIndex);
	}

	/**
	* Iterate through all the positions and recalculate it's right value.
	* @param positions a vector list with the position to recalculate
	* @param skipUnitId the id of the unit to skip adding to the position
	*/
	void recalculateValueOnPositions(utilities::VectorList<utilities::MapCoordinate>& positions, const logic::KeyType& skipUnitId);

#ifdef AI_DRAW_MAP_POTENTIAL_FIELD
/**
* Updates the potential value on the specified spot in the gfx
* @param arrayOffset the "position" in the array to update
*/
#define UPDATE_MAP_POTENTIAL_ON_SPOT(arrayOffset) updateMapPotentialOnSpot(arrayOffset)

	/**
	* Updates the potential value on the specified spot in the gfx.
	* This function is only declared when AI_DRAW_MAP_POTENTIAL_FIELD is defined
	* Instead of using this directly use UPDATE_MAP_POTENTIAL_ON_SPOT(arrayOffset)
	* @param arrayOffset the "position" in the array to update
	*/
	void updateMapPotentialOnSpot(int arrayOffset);
#else
#define UPDATE_MAP_POTENTIAL_ON_SPOT(arrayOffset)
#endif

	std::map<logic::KeyType, const PotentialUnit*> mPotentialUnits; /**< Units that should be applied to the potential field */
	float* mpPotentialField;	/**< The map's potential field */
	utilities::MapCoordinate mMapSize;
	utilities::MapCoordinate mCenterIndex;
	int mArraySize;

	static Map* mpsInstance;

#ifdef AI_DRAW_MAP_POTENTIAL_FIELD
	gfx::DX10Module* mpDx10Module;
	gfx::TransformObject** mppGfxPotentialField;
#endif
};
}

#endif