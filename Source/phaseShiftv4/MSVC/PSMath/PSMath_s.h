#pragma once

#ifndef _PSMath_s_H_
#define _PSMath_s_H_

#include <emmintrin.h>
#include <xmmintrin.h>

#include "PSMath.h"

#ifdef _MSC_VER
#define ALIGN_16 __declspec(align(16))
#else
#define ALIGN_16 __attribute__((aligned(16)))
#endif

namespace PSMath
{
	template <unsigned i>
	float vectorGetByIndex(__m128 V)
	{
		V = _mm_shuffle_ps(V, V, _MM_SHUFFLE(i, i, i, i));
		return _mm_cvtss_f32(V);
	}

	template <unsigned i>
	double vectorGetByIndex(__m128d V)
	{
		V = _mm_shuffle_pd(V, V, _MM_SHUFFLE(i, i, i, i));
		return _mm_cvtsd_f64(V);
	}
}
#endif

