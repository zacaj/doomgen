#include <windows.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "Room.h"
vector<Room*> rooms;
double drand_()   /* uniform distribution, (0..1] */
{
	return (rand()+1.0)/(RAND_MAX+1.0);
}
double random_normal()  /* normal distribution, centered on 0, std dev 1 */
{
	return sqrt(-2*log(drand_())) * cos(2*M_PI*drand_());
}
double drand(double mean,double dev)
{
	return mean + dev*random_normal();
}
void
	init(void)
{
	/* set viewing projection */
	glMatrixMode(GL_PROJECTION);
	glOrtho(-100,100,-100,100, 1.0F, 1000.0F);

	/* position viewer */
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0F, 0.0F, -2.0F);

	glClearColor(0,0,0,1);
	glColor3f(1,1,1);
}

void
	redraw(void)
{
	/* clear color and depth buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto room:rooms)
		(*room).draw();

	SDL_GL_SwapBuffers();
}
#undef main
int main(char argc,char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetVideoMode(1024,768,32,SDL_OPENGL|SDL_DOUBLEBUF);
	init();
	rooms.push_back(new Room());
	rooms.front()->generateRandom(0);
	bool done=0;
	while(!done)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_QUIT:
				done=1;
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					done=1;
					break;
				}
				break;
			}
		}
		redraw();
	}
	SDL_Quit();
	return 0;
}