#include "Baxter.h"

Baxter::Baxter(void)
{
	x = 0;
	y = 0;
	z = 0;
	facing = 0;
}

void Baxter::move(float distance)
{
	x = x + distance*sin(facing);
	y = y + distance*cos(facing);
}

void Baxter::turn(float r)
{
	facing += r;
}