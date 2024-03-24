#pragma once

#include "GameLoop.h"

class FrameGameLoop : public GameLoop
{
public:
	FrameGameLoop();

	void process();
};