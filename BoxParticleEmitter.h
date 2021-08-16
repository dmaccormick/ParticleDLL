#ifndef BOXPARTICLEEMITTER_H
#define BOXPARTICLEEMITTER_H

//Core Libraries
#include <vector>

//Our Headers
#include "Vec3.h"
#include "Particle.h"
#include "BoxDescriptor.h"

class BoxParticleEmitter
{
public:
	//--- Constructors and Destructor ---//
	BoxParticleEmitter();
	BoxParticleEmitter(Vec3* _verts, int _numParticles, float _maximumDeviation, float _averageLifetime, Vec3 _averageVelocity, float _gravityModifier);
	~BoxParticleEmitter();



	//--- Setters and Getters ---//
	void setGravityModifier(float _modifier);



	//--- Methods ---//
	void update(float _dt);
	void updatePositions(Vec3* _positions);
	void applyForce(Vec3 _force);
	void prewarm();



private:
	//--- Data Members ---//
	std::vector<Particle> particles;
	BoxDescriptor spawnBox;
	float maximumDeviation; //% deviation from the average ... creates the range for each of the parameters
	float averageLifetime;
	Vec3 averageVelocity;
	float gravityModifier;



	//--- Utility Functions ---//
	Particle generateParticle();
	float calcRandomFloat(float _min, float _max);
	Vec3 calcRandomVec3(Vec3 _a, Vec3 _b);
};

#endif
