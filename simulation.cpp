#include<iostream>
#include<fstream>
#include"headers/generator.h"
#include"headers/server.h"
#include"headers/distribution.h"
#include"headers/job.h"
#define REPEAT 10000000
using namespace std;
int main() {
	cout.precision(20);
	ifstream fin("parameters.conf");
	float lambda=0,theta=0,mu=0;
	fin>>theta>>mu;
	cin>>lambda;
	Generator generator(lambda,theta);
	Server server(mu,12);
	long blocked=0;
	long droped=0;
	for(long i=0;i<REPEAT;i++) {
		Job job = generator.generateJob(Distribution::Fixed);
		float interval = generator.generateJobInterval();
		if(!server.addJob(job))	{
			blocked++;
		}
		droped+= server.run(interval);

	}
	cout<<(double)blocked/REPEAT<<"\t";
	cout<<(double)droped/REPEAT<<endl;

	blocked=0;
	droped=0;
	for(long i=0;i<REPEAT;i++) {
		Job job = generator.generateJob(Distribution::Exponential);
		float interval = generator.generateJobInterval();
		if(!server.addJob(job))	{
			blocked++;
		}
		droped+= server.run(interval);

	}
	cout<<(double)blocked/REPEAT<<"\t";
	cout<<(double)droped/REPEAT<<endl;

}
