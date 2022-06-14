
#include "Effects/Fear.h"

#include "Characters/Character.h"

Fear::Fear(AnimationParams animParams)
	: Effect(_heal)
{}

//===================================================================================================

void Fear::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, Character* target, float factor)
{
	target->behaviour()->Flee(target->getLocationsVec(true), target->getMoveStats());
}
