// -*- mode: c++ -*-

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

#pragma once
#define  _USE_MATH_DEFINES
#include <string>
#include <utilities/GDefinitions.h>
#include <cmath>
#ifndef M_PI
	#define M_PI       3.14159265358979323846
#endif // !M_PI



#define FERROTECH_SUCCESS   0
#define FERROTECH_WARNING   1
#define FERROTECH_ERROR     2
#define FERROTECH_FATAL     3


//typedef long long int int64;

using std::string;
typedef int kf_errorocode_t;
typedef uint32_t session32_t;
typedef uint16_t bool16_t;
typedef uint32_t bool32_t;
typedef int32_t status32_t;
typedef double float64_t; //CRAP PTH, check for 32 bit platform

class GComplexNumber
{
public:
	inline GComplexNumber() { fReal = 0.0; fImag = 0.0; }
	inline GComplexNumber( const GComplexNumber & o ) { fReal = o.fReal; fImag = o.fImag; }
	inline GComplexNumber( float64_t preal, float64_t pimag ) { fReal = preal; fImag = pimag; }
	inline float64_t CalculateTime() { return (20 * log10( sqrt( (fReal * fReal) + (fImag * fImag) ) )); }
	inline float64_t CalculateAmplitude() { return sqrt( (fReal * fReal) + (fImag * fImag) ); }
	inline float64_t CalculatePhaseDeg() { return ((atan2( fImag, fReal ) / M_PI) * 180.0); }
	inline float64_t CalculatePhaseRad() { return atan2( fImag, fReal ); }
	inline void SetData( float64_t preal, float64_t pimag ) { fReal = preal; fImag = pimag; }
	inline float64_t GetReal() { return fReal; }
	inline float64_t GetImag() { return fImag; }
	inline bool IsZero() { if ( (fImag && fReal) == 0.0 ) return true; else return false; }

private:
	float64_t fReal = 0.0;
	float64_t fImag = 0.0;
};

