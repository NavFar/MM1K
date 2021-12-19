#include"server.h"
#include"job.h"
#include"server-runner.h"
Server::Server(float mu, int maxSize, ServerRunner * runner){
	this->mu = mu;
	this->maxSize = maxSize;
	this->runner = runner; 
}
Server::~Server(){
}
bool Server::addJob(Job job){
	if(this->queue.size()== this->maxSize)
		return false;
	this->queue.push_back(job);
	return true;
}
int Server::run(float duration){
	return	this->runner->run(duration, this->mu, this->queue);
}
