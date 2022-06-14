
#include "Effects/Fear.h"

#include "Characters/Character.h"

Fear::Fear()
{}

//===================================================================================================

void Fear::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, Character* target, float factor)
{
	target->behaviour()->Flee(target->getLocationsVec(false), target->getMoveStats());
}
