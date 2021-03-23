#pragma once

#include "Collectable.h"

class Key : public Collectable
{
public:

	using Collectable::Collectable;

protected:

	virtual void OnCollect(Player* aPlayer) override;

};
