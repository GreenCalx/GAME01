#pragma once
#include "AnimationManager.h"

class ActorAnimationManager :
	public AnimationManager
{
public:
	ActorAnimationManager(Actor* actor, TextureManager* tm);
	~ActorAnimationManager();

	int splitTexture(TextureManager& tm) override;
    sf::Sprite* ping(Actor::__STATE  pState, TextureManager& tm);

private:
	Actor::__STATE	actorState;
	Actor			*attachedActor;
	int				n_rowSprites;
	int				n_colSprites;
};

