#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vec3.h"

#define GRAVITY -9.81f

class Particle
{
public:
	//--- Constructors and Destructor ---//
	Particle();
	Particle(float _maxLifetime, Vec3 _position, Vec3 _startVelocity, float _gravityModifier);
	~Particle();



	//--- Setters and Getters ---//
	Vec3 getPosition() const;
	bool getIfDead() const;
	float getMaxLifetime() const;
	void setCurrentLifetime(float _currentLifetime);
	void setGravityModifier(float _modifier);



	//--- Methods ---//
	void update(float _dt);
	void applyForce(Vec3 _force);



private:
	//--- Data Members ---//
	float maxLifetime; //How long the particle will go before it dies
	float currentLifetime; //How long the particle has so far been alive for
	Vec3 position;
	Vec3 velocity;
	Vec3 forces;
	float gravityModifier;
};

#endif
