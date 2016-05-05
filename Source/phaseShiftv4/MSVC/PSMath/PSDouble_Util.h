#pragma once

#ifndef _PSDOUBLE_UTIL_H_
#define _PSDOUBLE_UTIL_H_

#include <cmath>
#include <limits>
#include <algorithm>

namespace PSMath
{
	typedef union
	{
		long long i64;
		double d64;
	} dbl_64;

	inline double machine_eps(double value)
	{
		dbl_64 s;
		s.d64 = value;
		s.i64++;
		return (s.i64 < 0 ? value - s.d64 : s.d64 - value);
	}

	inline bool DE_areEqualRel(double a, double b)
	{
		return (fabs(a - b) <= DBL_EPSILON * std::max(fabs(a), fabs(b)));
	}

	inline bool CE_areEqualRel(double a, double b)
	{
		return (fabs(a - b) <= machine_eps((a + b) / 2) * std::max(fabs(a), fabs(b)));
	}

	inline bool SE_areEqualREs(double a, double b, double epsilon = 0.1)
	{
		return (fabs(a - b) <= epsilon * std::max(fabs(a), fabs(b)));
	}

	inline bool DE_areEqual(double a, double b)
	{
		return (fabs(a - b) <= DBL_EPSILON * std::max(1.0, std::max(a, b)));
	}

	inline bool CE_areEqual(double a, double b)
	{
		return (fabs(a - b) <= machine_eps((a + b) / 2) * std::max(1.0, std::max(a, b)));
	}

	inline bool SE_areEqual(double a, double b, double epsilon = 0.1)
	{
		return (fabs(a - b) <= epsilon * std::max(1.0, std::max(a, b)));
	}

	inline bool DE_areEqualAbs(double a, double b)
	{
		return (fabs(a - b) <= DBL_EPSILON);
	}

	inline bool CE_areEqualAbs(double a, double b)
	{
		return (fabs(a - b) <= machine_eps((a + b) / 2));
	}

	inline bool SE_areEqualAbs(double a, double b, double epsilon = 0.1)
	{
		return (fabs(a - b) <= epsilon);
	}
}

#endif

