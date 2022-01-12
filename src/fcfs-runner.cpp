#include"fcfs-runner.h"
#include"job.h"
#include<deque>

std::deque<Job> FCFSRunner::run(float duration, float mu,std::deque<Job>& queue){
	std::deque<Job> dropped;
	float load = duration * mu;
	while(load>0 && queue.size()>0){
		float passedTime=duration;
		bool frontDone=false;
		load = load - queue.front().getLoad();
		if(load>=0){
			passedTime=queue.front().getLoad()/mu;
			frontDone=true;
		}
		else {
			queue.front().setLoad(-1*load);
		}
		std::deque<Job>::iterator it = queue.begin()+1;
		while(it< queue.end()){
			it->decreaseDue(passedTime/mu);
			if(it->getDue()<=0){
				dropped.push_back(*it);
				it= queue.erase(it);
			}
			else
				it++;
		}
		if(frontDone){

			queue.pop_front();
		}

	}
	return dropped;

}
