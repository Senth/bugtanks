/**
 * @file
 * @author Carl Nordlander <cand05@student.bth.se>
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

#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <d3dx10.h>
#include "CollisionObject.h"
#include "Sphere.h"

namespace gfx
{
	class Frustum : public CollisionObject
	{
		public:

			/**
			 * Constructor.
			 */
			Frustum();

			/**
			 *	Returns true if there is a collision.
			 *  @param pCollisionObject . The CollisionObject that you check for collision against.
			 *  @param calculateNormal . If you want the normal of the collision (not used).
			 */
			bool collision(const CollisionObject * pCollisionObject, bool calculateNormal);

			/**
			 *  Updates the frustum.
			 *  @param view . The view matrix.
			 *  @param projection . The projection matrix.
			 */
			void update(const D3DXMATRIX& view, const D3DXMATRIX& projection);

		private:
			D3DXPLANE mPlanes[6];
	};
}

#endif