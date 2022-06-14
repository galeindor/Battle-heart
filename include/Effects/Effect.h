#pragma once
#include "Animation.h"
#include "Resources.h"
#include "Stat.h"
#include "Timer.h"

class Character;

using namespace std;

class Effect
{
public:
	Effect(const int index);
	virtual ~Effect() = default;


	virtual void affect(float baseValue, vector<std::shared_ptr<Stat>> myStats,
		Character* target, float factor) = 0;


};