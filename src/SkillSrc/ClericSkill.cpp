
#include "Skills/ClericSkill.h"

ClericSkill::ClericSkill(sf::Texture * texture, const sf::Vector2f & pos, float cd, int damage, float range, int wantedStat)
	:Skill(texture,pos,cd,damage ,range , wantedStat)
{}
