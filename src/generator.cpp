#include"generator.h"
#include"job.h"
#include"distribution.h"
#include<random>
Generator::Generator(float lambda, float theta){
	this->lambda = lambda;
	this->theta = theta;
	std::random_device rd;
	this->randomNumberGenerator = std::default_random_engine(rd());
}

Job Generator::generateJob(Distribution dueTimeDistribution){
	std::exponential_distribution<float> exponentialDistribution(this->lambda);
	
	float load = exponentialDistribution(randomNumberGenerator);
	load = 1;

	if(dueTimeDistribution == Distribution::Fixed){
		return Job(load,this->theta);
	}
	if(dueTimeDistribution == Distribution::Exponential){
		exponentialDistribution = std::exponential_distribution<float>((double)1/this->theta);
		float due = exponentialDistribution(randomNumberGenerator);
		return Job(load,due);
	}
	return   Job(1,1);
}
float Generator::generateJobInterval(){
	std::exponential_distribution<float> exponentialDistribution(this->lambda);
	return exponentialDistribution(randomNumberGenerator);	
}
