#pragma once

#ifndef _PSFLOAT_H_
#define _PSFLOAT_H_

#include "PSMath.h"
#include "PSFloat_Util.h"

namespace PSMath
{
	class PSFloat
	{
	public:
		float ALIGN_16 f32;

	public:
		PSFloat();
		explicit PSFloat(const float);
		explicit PSFloat(const float*);
		PSFloat(const PSFloat&);
		~PSFloat();

		PSFloat& operator=(const PSFloat&);
		friend bool operator==(const PSFloat&, const PSFloat&);
	};

	inline PSFloat::PSFloat() : f32(0.0f)
	{
	}

	inline PSFloat::PSFloat(const float a) : f32(a)
	{
	}

	inline PSFloat::PSFloat(const float* a) : f32(*a)
	{
	}

	inline PSFloat::PSFloat(const PSFloat& a) : f32(a.f32)
	{
	}

	inline PSFloat::~PSFloat()
	{
	}

	inline PSFloat& PSFloat::operator=(const PSFloat& a)
	{
		f32 = a.f32;
		return *this;
	}

	inline bool operator==(const PSFloat& a, const PSFloat& b)
	{
		return DE_areEqualAbs(a.f32, b.f32);
	}
}

#endif

