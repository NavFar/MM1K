#include<iostream>
#include<cmath>
#include<limits>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////
enum class Distribution {
	Fixed,
	Exponential
};
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
long double p(int n, double theta, double lambda, double mu,Distribution distribution ) {
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
int main() {
	cout.precision(20);
	double theta=0, lambda=0, mu=0;
	cout<<"Theta-lambda-mu"<<endl;
	cin>>theta>>lambda>>mu;
	long double sum_p_fixed=1, sum_p_exponential=1;
	for(int i=1;i<=12;i++){
		sum_p_fixed+=p(i,theta,lambda,mu,Distribution::Fixed);
		sum_p_exponential+=p(i,theta,lambda,mu,Distribution::Exponential);
	}

	cout<<p(12,theta,lambda,mu,Distribution::Fixed)/sum_p_fixed<<"\t";
	cout<<1-(p(12,theta,lambda,mu,Distribution::Fixed)/sum_p_fixed)-(mu/lambda)*((sum_p_fixed-1)/sum_p_fixed)<<endl;

	cout<<p(12,theta,lambda,mu,Distribution::Exponential)/sum_p_exponential<<"\t";
	cout<<1-(p(12,theta,lambda,mu,Distribution::Exponential)/sum_p_exponential)-(mu/lambda)*((sum_p_exponential-1)/sum_p_exponential)<<endl;
}


