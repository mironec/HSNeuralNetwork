#include "stdafx.h"
#include "Damagable.h"


Damagable::Damagable()
{
}


Damagable::~Damagable()
{
}

int32_t Damagable::getHealth()
{
	return health;
}

int32_t Damagable::getMaxHealth()
{
	return maxHealth;
}
