#include<iostream>
#include"headers/generator.h"
#include"headers/server.h"
#include"headers/distribution.h"
#include"headers/job.h"
using namespace std;
int main() {
	cout<<"lambda, theta, mu"<<endl;
	float lambda=0,theta=0,mu=0;
	cin>>lambda>>theta>>mu;
	Generator generator(lambda,theta);
	Server server(mu,12);
	long blocked=0;
	long droped=0;
	long total = 1000*1000;
	for(long i=0;i<total;i++) {
		Job job = generator.generateJob(Distribution::Fixed);
		float interval = generator.generateJobInterval();
		if(!server.addJob(job))	{
			blocked++;
		}
		droped+= server.run(interval);
	
	}
	cout<<"Pb "<<(double)blocked/total<<endl;
	cout<<"Pd "<<(double)droped/total<<endl;
}
