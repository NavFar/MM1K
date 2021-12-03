#include"headers/server.h"
#include"headers/job.h"

Server::Server(float mu, int maxSize){
	this->mu = mu;
	this->maxSize = maxSize;
}
bool Server::addJob(Job job){
	if(this->queue.size== this->maxSize)
		return false;
	this->queue.push_back(job);
}
int Server::run(float duration){
	int droped = 0;
	while(duration>0 && this->queue.size()>0){
		float passedTime=duration;
		duration = duration - this->queue.front().getLoad();
		if(duration>0){
			passedTime=this.queue.front().getLoad();
			this->queue.pop_front();
		}
		else {
			this->queue.front().setLoad(-1*duration);
		}
		std::deque<Job>::iterator it = this->queue.begin()+1;
		while(it!= this->queue.end()){
			it->decreaseDue(passedTime);
			if(it->getDue()<0){
				droped++;
				it= this->queue.erase(it);
			}
			else
				it++;
		}

	}
	return droped;
}
