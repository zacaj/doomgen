#pragma once
#include "..\..\enginepp\enginepp\vec2.h"
#include <vector>
class Room
{
public:
	vector<vec2f> pts;
	Room(void);
	virtual ~Room(void);
	virtual void draw();
	void generateRandom(vec2f center);
};

