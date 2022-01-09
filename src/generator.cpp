#include"generator.h"
#include"job.h"
#include"job-type.h"
#include"distribution.h"
#include<random>
Generator::Generator(float lambda, float theta){
	this->lambda = lambda;
	this->theta = theta;
	std::random_device rd;
	this->randomNumberGenerator = std::default_random_engine(rd());
}

Job Generator::generateJob(Distribution dueTimeDistribution,Distribution typeDistribution){
	std::exponential_distribution<float> exponentialDistribution(this->lambda);
	JobType type = JobType::Normal;
	float load = 1;

	if(typeDistribution == Distribution::Uniform){
		std::uniform_int_distribution<> uniformDistribution(1,static_cast<int>(JobType::Count)-1);
		type = static_cast<JobType>(uniformDistribution(randomNumberGenerator));
	}

	if(dueTimeDistribution == Distribution::Fixed){
		return Job(load,this->theta,type);
	}
	if(dueTimeDistribution == Distribution::Exponential){
		exponentialDistribution = std::exponential_distribution<float>((double)1/this->theta);
		float due = exponentialDistribution(randomNumberGenerator);
		return Job(load,due,type);
	}
	return   Job(1,1,type);
}
float Generator::generateJobInterval(){
	std::exponential_distribution<float> exponentialDistribution(this->lambda);
	return exponentialDistribution(randomNumberGenerator);	
}
