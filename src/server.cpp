#include"server.h"
#include"job.h"
#include"fcfs-runner.h"
Server::Server(float mu, int maxSize){
	this->mu = mu;
	this->maxSize = maxSize;
	this->runner = new FCFSRunner(); 
}
Server::~Server(){
	delete this->runner;
}
bool Server::addJob(Job job){
	if(this->queue.size()== this->maxSize)
		return false;
	this->queue.push_back(job);
	return true;
}
int Server::run(float duration){
	return	this->runner->run(duration, this->queue);
}
