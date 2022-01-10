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
#include"gps-runner.h"
#include"constants.h"
using namespace std;
int main() {
	cout.precision(20);
	ifstream fin(PARAMETERS_FILE);
	float lambda=0,theta=0,mu=0;
	string queueStrategy;
	fin>>theta>>mu;
	cin>>queueStrategy;
	cin>>lambda;
	Generator generator(lambda,theta);
	ServerRunner * serverRunner;
	
	if(queueStrategy==FCFS_NAME)
		serverRunner = new FCFSRunner();
	else if(queueStrategy==PS_NAME)
		serverRunner = new PSRunner();
	else if(queueStrategy==GPS_NAME)
		serverRunner = new GPSRunner();
	else
		return 1;
	Server server(mu,K,new FCFSRunner());
	long blocked=0;
	long droped=0;
	for(long i=0;i<REPEAT;i++) {
		Job job = generator.generateJob(Distribution::Fixed,Distribution::Uniform);
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
		Job job = generator.generateJob(Distribution::Exponential,Distribution::Uniform);
		float interval = generator.generateJobInterval();
		if(!server.addJob(job))	{
			blocked++;
		}
		droped+= server.run(interval);

	}
	cout<<(double)blocked/REPEAT<<"\t";
	cout<<(double)droped/REPEAT<<endl;

}
