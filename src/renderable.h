#pragma once
#include "bbox.h"

class app;

class renderable
{
public:
	virtual void render(app*) = 0;
	virtual bbox get_bbox() = 0;
};