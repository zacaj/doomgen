#include "Room.h"
#include <GL\gl.h>
#include "main.h"
#include <stdlib.h>


Room::Room(void)
{
}


Room::~Room(void)
{
}

void Room::draw()
{
	glBegin(GL_LINE_LOOP);
	for(auto p:pts)
		glVertex2f(p.x,p.y);
	glEnd();
}

void Room::generateRandom(vec2f center)
{
	int nSide=drand(5,.8);
	if(nSide<4)
		nSide=4;
	float d=drand(15,3);
	double offsetAngle=.01*(rand()%628);
	double a=0;
	for(int i=0;i<nSide;i++)
	{
		pts.push_back(vec2f(cos(a+offsetAngle)*d,sin(a+offsetAngle)*d));
		d+=drand(0,5);
		if(d<3)
			d+=drand(3,1);
		a+=drand((6.28-a)/(nSide-i),(6.28-a)/(nSide-i)*.3);
	}
	for(auto p:pts)
		p+=center;
}
