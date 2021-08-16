#ifndef VEC3_H
#define VEC3_H

#include "LibSettings.h"
#include <cmath>

#ifdef __cplusplus
extern "C"
{
#endif


	LIB_API struct Vec3
	{
		//--- Constructors ---//
		Vec3() 
		{ 
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		Vec3(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}



		//--- Static "Operator" Functions ---//
		static Vec3 add(Vec3 _a, Vec3 _b) {
			return Vec3(_a.x + _b.x, _a.y + _b.y, _a.z + _b.z);
		}

		static Vec3 sub(Vec3 _a, Vec3 _b) {
			return Vec3(_a.x - _b.x, _a.y - _b.y, _a.z - _b.z);
		}

		static Vec3 scaleBy(Vec3 _v, float _scalar) {
			return Vec3 (_v.x * _scalar, _v.y * _scalar, _v.z * _scalar);
		}

		static float mag(Vec3 _v) {
			return sqrt((_v.x * _v.x) + (_v.y * _v.y) + (_v.z + _v.z));
		}

		static Vec3 lerp(Vec3 _a, Vec3 _b, float _t) {
			return Vec3::add(Vec3::scaleBy(_a, 1.0f - _t), Vec3::scaleBy(_b, _t));
		}



		//--- Data members ---//
		float x;
		float y;
		float z;
	};


#ifdef __cplusplus
}
#endif



#endif
