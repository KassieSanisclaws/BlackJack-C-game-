#pragma once

#include "GameLoop.h"

class VariableStepGameLoop : public GameLoop
{
public:
	VariableStepGameLoop();

	void process();

private:
	float lag;
};