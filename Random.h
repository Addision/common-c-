#pragma once

#include <random>
#include <stdint.h>

class Random
{
public:
	Random()
	{
		std::random_device rd;
		mGen = std::mt19937(rd());
	}

	static Random& Instance()
	{
		static Random myRand;
		return myRand;
	}

	template<class IntType>
	IntType rand(IntType min, IntType max)
	{
		if(max <= min)
			max = min;
		std::uniform_int_distribution<IntType> dis(min, max);
		return dis(mGen);
	}

	template<class RealType>
	RealType randf(RealType min, RealType max)
	{
		if(max <= min)
			max = min;
		std::uniform_real_distribution<RealType> dis(min, max);
		return dis(mGen);
	}
private:
	std::mt19937 mGen;
};


