#ifndef GENERATOR_H
#define GENERATOR_H

#include"job.h"
#include"distribution.h"
#include<random>
class Generator{
	private:
		float lambda;
		float theta;
		std::default_random_engine randomNumberGenerator;

	public:
		Generator(float, float);
		Job generateJob(Distribution,Distribution);
		float generateJobInterval();
};
#endif
