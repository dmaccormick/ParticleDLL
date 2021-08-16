#ifndef WRAPPER_H
#define WRAPPER_H

#include "LibSettings.h"
#include "Vec3.h"

#ifdef __cplusplus
extern "C"
{
#endif
	
	//Call once at the start of the level
	LIB_API void initSystems();

	//Returns the index to keep track of in Unity
	LIB_API int generateParticleSystem_OOBB(Vec3* verts, int _numParticles, float _maxDeviation, float _avgLifetime, Vec3 _avgVel, float _gravityModifier);

	//Step physics and return the positions
	LIB_API void updateParticleSystem(Vec3* _positions, int _index, float _dt);

	//Call once when the level is done
	LIB_API void destroyAllParticleSystems();

	//Apply a force to the particle system
	LIB_API void applyForce(int _index, Vec3 _force);

	//Prewarm A Given Particle System
	LIB_API void prewarmSystem(int _index);

	//Change the gravity modifier to the requested particle system
	LIB_API void setGravityModifier(int _index, float _modifier);

#ifdef __cplusplus
}
#endif

#endif
