#include "Wrapper.h"
#include "BoxParticleEmitter.h"
#include <vector>
#include <iostream>

//Store a list of the active emitters
std::vector<BoxParticleEmitter> emitters;

void initSystems()
{
	//Init the emitter vector
	emitters = std::vector<BoxParticleEmitter>();
}

int generateParticleSystem_OOBB(Vec3* verts, int _numParticles, float _maxDeviation, float _avgLifetime, Vec3 _avgVel, float _gravityModifier)
{
	//Create a new particle system with the given parameters
	BoxParticleEmitter emitter = BoxParticleEmitter(verts, _numParticles, _maxDeviation, _avgLifetime, _avgVel, _gravityModifier);

	//Add the particle emitter to the list
	emitters.push_back(emitter);

	//Return the index of the emitter
	return (int)emitters.size() - 1;
}

void updateParticleSystem(Vec3* _positions, int _index, float _dt)
{
	//If the index is invalid, output an error and prevent the array access
	if (_index >= emitters.size() || _index < 0)
	{
		//Output the error message
		std::cout << "ERROR: Trying to access a particle system that is out of range! Given index was: " << _index << std::endl;

		//Return to avoid the invalid array access
		return;
	}

	//Update the requested particle system
	emitters[_index].update(_dt);

	//Update the positions
	emitters[_index].updatePositions(_positions);
}

void destroyAllParticleSystems()
{
	//Clear the vector of particle systems
	emitters.clear();
}

void applyForce(int _index, Vec3 _force)
{
	//If the index is invalid, output an error and prevent the array access
	if (_index >= emitters.size() || _index < 0)
	{
		//Output the error message
		std::cout << "ERROR: Trying to access a particle system that is out of range! Given index was: " << _index << std::endl;

		//Return to avoid the invalid array access
		return;
	}

	//Apply the requested force to the requested particle system
	emitters[_index].applyForce(_force);
}

void prewarmSystem(int _index)
{
	//If the index is invalid, output an error and prevent the array access
	if (_index >= emitters.size() || _index < 0)
	{
		//Output the error message
		std::cout << "ERROR: Trying to access a particle system that is out of range! Given index was: " << _index << std::endl;

		//Return to avoid the invalid array access
		return;
	}

	//Prewarm the requested particle system
	emitters[_index].prewarm();
}

void setGravityModifier(int _index, float _modifier)
{
	//If the index is invalid, output an error and prevent the array access
	if (_index >= emitters.size() || _index < 0)
	{
		//Output the error message
		std::cout << "ERROR: Trying to access a particle system that is out of range! Given index was: " << _index << std::endl;

		//Return to avoid the invalid array access
		return;
	}

	//Change the gravity modifier for the given system
	emitters[_index].setGravityModifier(_modifier);
}