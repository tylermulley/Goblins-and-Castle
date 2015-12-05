#include "particleManager.h"
#include <stdlib.h>
#include <time.h>
#include "graphics.h"

ParticleManager::ParticleManager()
{
	srand(time(NULL));
}
ParticleManager::~ParticleManager()
{
}
float ParticleManager::getVariance()
{
	float foo = (rand() );
	foo = ((int)foo	% 100)/100.0f;
	foo += 0.5f;
	return foo;
}
void ParticleManager::setInvisibleAllParticles()
{
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		particles[i].setVisible(false);
		particles[i].setActive(false);
	}
}
void ParticleManager::setVisibleNParticles(int n)
{
	int activatedParticles = 0;
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		if (!particles[i].getActive()) //found an inactive particle
		{
			particles[i].setActive(true);
			particles[i].setMaxTimeAlive(MAX_PARTICLE_LIFETIME*getVariance());
			float newX = velocity.x * getVariance(); 
			float newY = velocity.y  * getVariance();
			VECTOR2 v = VECTOR2(newX,newY);
			particles[i].setX(position.x);
			particles[i].setY(position.y);
			particles[i].setVelocity(v);
			particles[i].setVisible(true);
			activatedParticles++;
			if (activatedParticles == n)
				return;
		}
	}
}

bool ParticleManager::initialize(Graphics *g)
{
	if (!tm.initialize(g, FLAMES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dust texture"));
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		if (!particles[i].initialize(g,0,0,0,&tm))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dust"));
		particles[i].setActive(false);
		particles[i].setVisible(false);
		particles[i].setScale(0.125f);
		//particles[i].setRotationValue(0.05f);
	}
	return true;
}

void ParticleManager::update(float frametime)
{
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++){
		if (particles[i].getActive())
			particles[i].update(frametime);

	}
}

void ParticleManager::draw()
{
	byte fadeAmount;
	COLOR_ARGB color;
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		if (!particles[i].getActive())
			continue;
		float foo = particles[i].getMaxTimeAlive();  //MAX_PARTICLE_LIFETIME;
		float bar = particles[i].getTimeAlive();
		float foobar = (foo-bar)/foo;
		fadeAmount = 255 * foobar;
		color = D3DCOLOR_ARGB(fadeAmount,fadeAmount,150,0);
		particles[i].draw(color);
		if (fadeAmount <= 20)
			particles[i].resetParticle();
	}
}
void ParticleManager::rotateImage(float rads){
	for (int i = 0; i < MAX_NUMBER_PARTICLES; i++)
	{
		particles[i].setRadians(rads);
	}
}