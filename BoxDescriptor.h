#ifndef BOXDESCRIPTOR_H
#define BOXDESCRIPTOR_H

#include "Vec3.h"

class BoxDescriptor
{
public:

	Vec3 minPos;
	Vec3 vertA, vertB, vertC;

	BoxDescriptor()
	{
		minPos = Vec3();
		vertA = Vec3();
		vertB = Vec3();
		vertC = Vec3();
	}

	BoxDescriptor(Vec3* _points)
	{
		//The 4 verts create a sort of coordinate frame in the corner of the box
		//The min vertex is the one in the bottom corner of the bounding box
		//Verts ABC are the adjacent vertices
		//Together, they create the coordinate frame shape representing the box
		
		//The min position is the first one
		minPos = _points[0];

		//The remaining verts are in order ABC
		vertA = _points[1];
		vertB = _points[2];
		vertC = _points[3];
	}

	Vec3 getRandomPoint(float _x, float _y, float _z)
	{
		//Create vectors from the min points to the adjacent verts
		//Lerp along each of the three vectors a random % (from 0 - 1) 
		//The sum of these three lerp'd vectors will always be a point somewhere in the box, no matter the orientation
		//Important for being able to use OBB instead of just AABB

		//Lerp a position randomly along the a vector, X%
		Vec3 posX = Vec3::lerp(minPos, vertA, _x);
		Vec3 vecA = Vec3::sub(posX, minPos);
		
		//Lerp a position randomly along the b vector, Y%
		Vec3 posY = Vec3::lerp(minPos, vertB, _y);
		Vec3 vecB = Vec3::sub(posY, minPos);

		//Lerp a position randomly along the c vector, Z%
		Vec3 posZ = Vec3::lerp(minPos, vertC, _z);
		Vec3 vecC = Vec3::sub(posZ, minPos);

		//The three vectors that when added together, result in a position somewhere in the box
		Vec3 vec1 = Vec3::add(minPos, vecA);
		Vec3 vec2 = Vec3::add(vec1, vecB);
		Vec3 vecFinal = Vec3::add(vec2, vecC);
		return vecFinal;
	}
};

#endif
