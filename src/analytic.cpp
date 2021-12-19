#include<iostream>
#include<cmath>
#include<limits>
#include<fstream>
#include"distribution.h"
#include"queue-strategy.h"
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////
int factorial(int n) {
	int response=1;
	for(int i=0;i<n;i++) {
		response*=i+1;
	}
	return response;
}
//////////////////////////////////////////////////////////////////////////////////////////////
long double phi_exponential(int n, double theta, double lambda, double mu){
	long double response = factorial(n);
	for(int i=0;i<=n;i++){
		response/= mu + (double)i/theta;
	}
	return response;
}
//////////////////////////////////////////////////////////////////////////////////////////////
long double phi_fixed(int n, double theta, double lambda, double mu){
	long double response = 0;
	for(int i=0;i<n;i++){
		response+=pow(mu*theta,i)/ factorial(i);
	}
	response *= pow(M_E, -1*mu*theta);
	response = 1-response;
	response *= factorial(n)/pow(mu,n+1);
	return response;

}
//////////////////////////////////////////////////////////////////////////////////////////////
long double p_fcfs(int n, double theta, double lambda, double mu,Distribution distribution ) {
	if(n==1)
		return lambda/mu;
	long double response= pow(lambda,n);
	if(distribution== Distribution::Fixed){
		response *= phi_fixed(n-1,theta,lambda,mu);
	}
	if(distribution== Distribution::Exponential){
		response *= phi_exponential(n-1,theta,lambda,mu);
	}
	response /= factorial(n-1);
	return response;

}
//////////////////////////////////////////////////////////////////////////////////////////////
long double gama(int n , double theta , double lambda, double mu, Distribution distribution){
	if(n==0)
		return 0;
	if(distribution==Distribution::Fixed){
		return mu/(pow(M_E,mu*theta/n)-1);
	}else if (distribution==Distribution::Exponential){
		return (double)n/theta;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
long double p_ps(int n , double theta, double lambda, double mu , Distribution distribution ){
	long double response = 1;
	for(int i=1;i<=n;i++){
		response*= lambda / (mu+gama(i,theta,lambda,mu,distribution));
	}
	return response;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void printPbAndPd(int k,double theta, double lambda, double mu, QueueStrategy queueStrategy){
	if(queueStrategy== QueueStrategy::FCFS){
	long double sum_p_fixed=1, sum_p_exponential=1;
        for(int i=1;i<=k;i++){
                sum_p_fixed+=p_fcfs(i,theta,lambda,mu,Distribution::Fixed);
                sum_p_exponential+=p_fcfs(i,theta,lambda,mu,Distribution::Exponential);
        }

        cout<<p_fcfs(k,theta,lambda,mu,Distribution::Fixed)/sum_p_fixed<<"\t";
        cout<<1-(p_fcfs(k,theta,lambda,mu,Distribution::Fixed)/sum_p_fixed)-(mu/lambda)*((sum_p_fixed-1)/sum_p_fixed)<<"\t";

        cout<<p_fcfs(k,theta,lambda,mu,Distribution::Exponential)/sum_p_exponential<<"\t";
        cout<<1-(p_fcfs(k,theta,lambda,mu,Distribution::Exponential)/sum_p_exponential)-(mu/lambda)*((sum_p_exponential-1)/sum_p_exponential)<<endl;
	}
	else if(queueStrategy== QueueStrategy::PS){
		
	long double p0_fixed = 1;
	long double p0_exponential = 1;

	for(int i=1;i<=k;i++) {
		long double  internal_fixed=pow(lambda,i);
		long double internal_exponential=pow(lambda,i);
		for(int j=1;j<=i;j++){
			internal_fixed/=(mu+gama(j,theta,lambda,mu,Distribution::Fixed));
			internal_exponential/=(mu+gama(j,theta,lambda,mu,Distribution::Exponential));
		}
		p0_fixed+=internal_fixed;
		p0_exponential+= internal_exponential;
	}
	p0_fixed = 1/p0_fixed;
	p0_exponential = 1/p0_exponential;
	
	long double pb_fixed = p_ps(k,theta,lambda,mu,Distribution::Fixed)*p0_fixed;
	long double pb_exponential = p_ps(k,theta,lambda,mu,Distribution::Exponential)*p0_exponential;
	
	cout<<pb_fixed<<"\t"<< 1- (mu*(1-p0_fixed)/lambda)- pb_fixed<<"\t";
	cout<<pb_exponential<<"\t"<< 1- (mu*(1-p0_exponential)/lambda)- pb_exponential<<"\t"<<endl;

	}
	else{
		return;
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	cout.precision(20);
	double theta=0, lambda=0, mu=0;
	ifstream fin("parameters.conf");
	fin>>theta>>mu;
	cin>>lambda;
	printPbAndPd(12,theta, lambda, mu, QueueStrategy::PS);
}


