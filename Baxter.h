#ifndef BAXTER_H
#define BAXTER_H

#include <math.h>

class Baxter{
private:
	float x,y,z;  //coordinates in 3d space
	float facing; //angle of facing in radians. could also do degrees if you prefer. 0 is right along the y-axis.

	//obviously more variables later

public:
	Baxter(void);

	// function that moves Baxter with facing. distance should be passed in as a speed variable.
	// Negative value denotes moving backwards.
	void move(float distance);

	void turn(float r);
};

#endif