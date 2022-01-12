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
#include"dps-runner.h"
#include"constants.h"
using namespace std;
void run(Generator&, Server&, Distribution, Distribution);
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
	else if(queueStrategy==DPS_NAME)
		serverRunner = new DPSRunner();
	else
		return 1;
	Server server(mu,K,serverRunner);
	run(generator, server,Distribution::Fixed,Distribution::Uniform);
	run(generator, server,Distribution::Exponential,Distribution::Uniform);
}
void run(Generator& generator, Server& server, Distribution jobDistribution, Distribution jobTypeDistribution){
	long blocked=0;
	long droped=0;
	for(long i=0;i<REPEAT;i++) {
		Job job = generator.generateJob(jobDistribution, jobTypeDistribution);
		float interval = generator.generateJobInterval();
		if(!server.addJob(job))	{
			blocked++;
		}
		droped+= server.run(interval).size();

	}
	cout<<(double)blocked/REPEAT<<"\t";
	cout<<(double)droped/REPEAT<<"\t";


}
