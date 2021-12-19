#include<iostream>
#include<fstream>
#include<string>
#include"generator.h"
#include"server.h"
#include"distribution.h"
#include"job.h"
#include"server-runner.h"
#include"fcfs-runner.h"
#include"ps-runner.h"
#define REPEAT 10000000
using namespace std;
int main() {
	cout.precision(20);
	ifstream fin("parameters.conf");
	float lambda=0,theta=0,mu=0;
	string queueStrategy;
	fin>>theta>>mu;
	cin>>queueStrategy;
	cin>>lambda;
	Generator generator(lambda,theta);
	ServerRunner * serverRunner;
	
	if(queueStrategy=="FCFS")
		serverRunner = new FCFSRunner();
	else if(queueStrategy=="PS")
		serverRunner = new PSRunner();
	else
		return 1;
	Server server(mu,12,new FCFSRunner());
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
	cout<<(double)droped/REPEAT<<"\t";

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
