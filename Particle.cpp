#include "Particle.h"

//--- Constructors and Destructor ---//
Particle::Particle()
{
	//Init the data members
	maxLifetime = 0.0f;
	currentLifetime = 0.0f;
	position = Vec3();
	velocity = Vec3();
	forces = Vec3();
	gravityModifier = 1.0f;
}

Particle::Particle(float _maxLifetime, Vec3 _position, Vec3 _startVelocity, float _gravityModifier)
{
	//Init the data members
	maxLifetime = _maxLifetime;
	currentLifetime = 0.0f;
	position = _position;
	velocity = _startVelocity;
	gravityModifier = _gravityModifier;
	forces = Vec3(0.0f, GRAVITY * gravityModifier, 0.0f);
}

Particle::~Particle()
{

}



//--- Getters ---//
Vec3 Particle::getPosition() const
{
	//Return the position of the particle. The only data that really matters externally
	return position;
}

bool Particle::getIfDead() const 
{
	//Check if this particle should be reset or not
	return (currentLifetime >= maxLifetime);
}

float Particle::getMaxLifetime() const
{
	//Return how long this particle will live for
	return maxLifetime;
}

void Particle::setCurrentLifetime(float _currentLifetime)
{
	//Manually set how long the particle has been alive for. Really only for prewarming
	currentLifetime = _currentLifetime;
}

void Particle::setGravityModifier(float _modifier)
{
	//Set how much gravity affects the particles
	gravityModifier = _modifier;
}



//--- Methods ---//
void Particle::update(float _dt)
{
	//Integrate the forces into the velocity, scaled by dt
	Vec3 scaledForces = Vec3::scaleBy(forces, _dt);
	velocity = Vec3::add(velocity, scaledForces);

	//Integrate the velocity into the position, scaled by dt
	Vec3 scaledVelocity = Vec3::scaleBy(velocity, _dt);
	position = Vec3::add(position, scaledVelocity);

	//Wipe the impulse forces down to just gravity to get ready for next frame
	forces = Vec3(0.0f, GRAVITY * gravityModifier, 0.0f);
	
	//Increment how long the particle has been alive for
	currentLifetime += _dt;
}

void Particle::applyForce(Vec3 _force) 
{
	//Add the force on to the impulse for this frame
	forces = Vec3::add(forces, _force);
}