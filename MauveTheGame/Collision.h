/*
* File:   collision.h
* Author: Nick Koirala
*
* Collision Detection and handling class
* For SFML.

(c) 2009 - LittleMonkey Ltd

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.

*
* Created on 30 January 2009, 11:02
*/

#ifndef _COLLISION_H
#define _COLLISION_H

#include <SFML/Graphics.hpp>


#ifndef PI
#define PI (3.14159265358979323846)
#endif
#define RADIANS_PER_DEGREE (PI/180.0)


class Collision {
public:

	virtual ~Collision();
	
	static bool AABB( const sf::Sprite& pSprite1, const sf::Sprite& pSprite2, sf::Vector2f moveToExecuteForSprite1);

private:

	Collision();
};

#endif  /* _COLLISION_H */