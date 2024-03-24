#pragma once

#include "GameLoop.h"

class FixedStepGameLoop : public GameLoop
{
public:
	FixedStepGameLoop();

	void process();
};