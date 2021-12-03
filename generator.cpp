#include"headers/generator.h"
#include"headers/job.h"
#include"headers/distribution.h"
#include<random>
Generator::Generator(float lambda, float theta){
	this->lambda = lambda;
	this->theta = theta;
}

Job Generator::generateJob(Distribution dueTimeDistribution){
	std::mt19937_64 randomNumberGenerator;
	std::exponential_distribution<float> exponentialDistribution(this->lambda);
	float load = exponentialDistribution(randomNumberGenerator);
	if(dueTimeDistribution == Distribution::Fixed)
		return Job(load,this->theta);
	if(dueTimeDistribution == Distribution::Exponential){
		exponentialDistribution = std::exponential_distribution<float>((double)1/this->theta);
		float due = exponentialDistribution(randomNumberGenerator);
		return Job(load,due);
	}
	return Job(1,1);
}
float Generator::generateJobInterval(){
	std::mt19937_64 randomNumberGenerator;
	std::exponential_distribution<float> exponentialDistribution(this->lambda);
	return exponentialDistribution(randomNumberGenerator);	
}
