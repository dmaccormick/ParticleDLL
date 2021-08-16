#include "BoxParticleEmitter.h"

//--- Constructors and Destructor ---//
BoxParticleEmitter::BoxParticleEmitter()
{
	//Init the data members
	spawnBox = BoxDescriptor();
	maximumDeviation = 0.0f;
	averageLifetime = 0.0f;
	averageVelocity = Vec3();
	gravityModifier = 1.0f;
}

BoxParticleEmitter::BoxParticleEmitter(Vec3* verts, int _numParticles, float _maximumDeviation, float _averageLifetime, Vec3 _averageVelocity, float _gravityModifier)
{
	//Init the data members
	particles = std::vector<Particle>();
	spawnBox = BoxDescriptor(verts);
	maximumDeviation = _maximumDeviation;
	averageLifetime = _averageLifetime;
	averageVelocity = _averageVelocity;
	gravityModifier = _gravityModifier;

	//Generate a bunch of particles
	for (int i = 0; i < _numParticles; i++)
		particles.push_back(generateParticle());
}

BoxParticleEmitter::~BoxParticleEmitter()
{
	//Clear the vector for cleanliness
	particles.clear();
}



//--- Setters ---//
void BoxParticleEmitter::setGravityModifier(float _modifier)
{
	//Set the new gravity modifier ... will take effect on each particle when it is regenerated
	gravityModifier = _modifier;
}



//--- Methods ---//
void BoxParticleEmitter::update(float _dt)
{
	//Loop through and update all of the particles. Also, check if they are dead. If so, regenerate them
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		//Update the particle
		particles[i].update(_dt);

		//If the particle is over its lifetime, regenerate it
		if (particles[i].getIfDead())
			particles[i] = generateParticle();
	}
}

void BoxParticleEmitter::updatePositions(Vec3* _positions)
{
	//Loop through the particle and update their positions to be sent back to Unity
	for (int i = 0; i < particles.size(); i++)
		_positions[i] = particles[i].getPosition();
}

void BoxParticleEmitter::applyForce(Vec3 _force)
{
	//Loop through all of the particles and apply the force to them
	for (unsigned int i = 0; i < particles.size(); i++)
		particles[i].applyForce(_force);
}

//Based On:
//https://gamedev.stackexchange.com/questions/79420/how-do-i-implement-prewarming-in-particle-engines
void BoxParticleEmitter::prewarm()
{
	//Loop through all of the particles in the system
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		//Randomly decide how far along this particle will be in its lifetime (0 = birth, 1 = death) ... ie % along lifetime
		float startLifetimePercent = calcRandomFloat(0.0f, 1.0f);

		//Calculate how much time would have passed for them to reach that % of their lifetime ... ie seconds into lifetime
		float startLifetimeSeconds = startLifetimePercent * particles[i].getMaxLifetime();

		//Assign this lifetime to the particle
		particles[i].setCurrentLifetime(startLifetimeSeconds);

		//Manually update the particle, using its new starting lifetime as the delta time value
		particles[i].update(startLifetimeSeconds);
	}
}



//--- Utility Functions ---//
Particle BoxParticleEmitter::generateParticle()
{
	//Randomly generate the particle's lifetime, using a range that is controlled by the maximum deviation
	float particleLifetime = calcRandomFloat(averageLifetime - (averageLifetime * maximumDeviation), averageLifetime + (averageLifetime * maximumDeviation));
	
	//Randomly generate the particle's spawn position to be somewhere in the box
	Vec3 particlePosition = spawnBox.getRandomPoint(calcRandomFloat(0.0f, 1.0f), calcRandomFloat(0.0f, 1.0f), calcRandomFloat(0.0f, 1.0f));

	//Randomly generate the particle's initial velocity
	Vec3 minVelocity = Vec3::sub(averageVelocity, Vec3::scaleBy(averageVelocity, maximumDeviation));
	Vec3 maxVelocity = Vec3::add(averageVelocity, Vec3::scaleBy(averageVelocity, maximumDeviation));
	Vec3 particleVelocity = calcRandomVec3(minVelocity, maxVelocity);

	//Create a new particle and assign it the randomized values
	Particle p = Particle(particleLifetime, particlePosition, particleVelocity, gravityModifier);

	//Return the particle
	return p;
}

//Based on this question: https://stackoverflow.com/questions/686353/c-random-float-number-generation
//Specifically, the response by: Ziezi
float BoxParticleEmitter::calcRandomFloat(float _min, float _max)
{
	//If the min and max are backwards, flip them
	if (_min > _max)
	{
		float temp = _min;
		_min = _max;
		_max = temp;
	}

	//Generate a random value
	float randomValue = float(rand()) / float(RAND_MAX);
	float range = _max - _min;

	//Return the random value
	return (randomValue * range) + _min;
}

Vec3 BoxParticleEmitter::calcRandomVec3(Vec3 _a, Vec3 _b)
{
	//Randomize the individual components
	float x = calcRandomFloat(_a.x, _b.x);
	float y = calcRandomFloat(_a.y, _b.y);
	float z = calcRandomFloat(_a.z, _b.z);

	//Return the values as a vector
	return Vec3(x, y, z);
}